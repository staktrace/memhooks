import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.PrintStream;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

class HeapObject implements Comparable<HeapObject> {
    private final long _startAddr;
    private long _endAddr;

    private final Set<HeapObject> _references;
    private final Set<HeapObject> _backRefs;
    private final Set<HeapObject> _dominatedChildren;

    private HeapObject _immediateDominator;
    private String _data;

    HeapObject( long startAddr, long endAddr ) {
        _startAddr = startAddr;
        _endAddr = endAddr;
        _references = new TreeSet<HeapObject>();
        _backRefs = new TreeSet<HeapObject>();
        _dominatedChildren = new TreeSet<HeapObject>();
    }

    long startAddr() {
        return _startAddr;
    }

    long endAddr() {
        return _endAddr;
    }

    void setData( String data ) {
        _data = data;
    }

    String data() {
        return _data;
    }

    void setImmediateDominator( HeapObject dom ) {
        _immediateDominator = dom;
        _immediateDominator._dominatedChildren.add( this );
    }

    void addReference( HeapObject reference ) {
        if (reference != null) {
            _references.add( reference );
            reference._backRefs.add( this );
        }
    }

    boolean isRoot() {
        return _backRefs.isEmpty();
    }

    boolean isDominator() {
        return ! _dominatedChildren.isEmpty();
    }

    long size() {
        return _endAddr - _startAddr;
    }

    long deepSize() {
        long total = size();
        for (HeapObject dominated : _dominatedChildren) {
            total += dominated.deepSize();
        }
        return total;
    }

    Iterator<HeapObject> references() {
        return _references.iterator();
    }

    Iterator<HeapObject> backReferences() {
        return _backRefs.iterator();
    }

    Iterator<HeapObject> dominatedChildren() {
        return _dominatedChildren.iterator();
    }

    Iterator<HeapObject> dominatorChain() {
        return new DominatorChain( this );
    }

    @Override public int compareTo( HeapObject other ) {
        if (_startAddr < other._startAddr) {
            if (_endAddr > other._startAddr) {
                System.err.println( "Error; overlapping objects found: " + this + " and " + other );
            }
            return -1;
        } else if (_startAddr > other._startAddr) {
            if (other._endAddr > _startAddr) {
                System.err.println( "Error; overlapping objects found: " + this + " and " + other );
            }
            return 1;
        } else {
            if (other._endAddr != _endAddr) {
                System.err.println( "Error: two objects with same start but different ends found: " + this + " and " + other );
            }
            return 0;
        }
    }

    @Override public int hashCode() {
        return (int)_startAddr;
    }

    @Override public boolean equals( Object other ) {
        if (other instanceof HeapObject) {
            return compareTo( (HeapObject)other ) == 0;
        }
        return false;
    }

    String name() {
        return "0x" + Long.toHexString( _startAddr );
    }

    @Override public String toString() {
        return name();
    }

    void dump( PrintStream out ) {
        out.println( "Block " + name() + " size " + (_endAddr - _startAddr) );
        for (HeapObject reference : _references) {
            out.println( "    references block at " + reference.name() );
        }
        out.println();
    }

    static void dumpHtmlTable( PrintWriter out, String title, Iterator<HeapObject> items ) {
        out.println( "<h2>" + title + "</h2><table border=1 width=100%><tr><th>Object</th><th>Size</th><th>Deep size</th></tr>" );
        while (items.hasNext()) {
            HeapObject item = items.next();
            out.println( "<tr><td><a href='" + item.name() + ".html'>" + item.toString() + "</a></td><td>" + item.size() + "</td><td>" + item.deepSize() + "</td></tr>" );
        }
        out.println( "</table>" );
    }

    void dumpHtml( File folder ) throws IOException {
        PrintWriter pw = new PrintWriter( new File( folder, name() + ".html" ) );
        pw.println( "<h1>Heap object " + toString() + "</h1>" );
        pw.println( "<p>Start address: 0x" + Long.toHexString( _startAddr ) + "<br>End address: 0x" + Long.toHexString( _endAddr ) + "<br>Size: " + size() + " bytes</p>" );
        dumpHtmlTable( pw, "References", references() );
        dumpHtmlTable( pw, "Referenced by", backReferences() );
        dumpHtmlTable( pw, "Dominates", dominatedChildren() );
        dumpHtmlTable( pw, "Dominated by", dominatorChain() );
        pw.close();
    }

    void dumpDot( PrintStream out ) {
        out.println( "    n" + toString() + ";" );
        for (HeapObject reference : _references) {
            out.println( "    n" + toString() + " -> n" + reference.toString() + ";" );
        }
    }

    static class DominatorChain implements Iterator<HeapObject> {
        private HeapObject _current;

        DominatorChain( HeapObject start ) {
            _current = start;
        }

        @Override public boolean hasNext() {
            return _current._immediateDominator != null;
        }

        @Override public HeapObject next() {
            _current = _current._immediateDominator;
            return _current;
        }

        @Override public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}
