import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.PrintStream;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

class HeapObject implements Comparable<HeapObject> {
    final long _startAddr;
    final long _endAddr;

    private final Set<HeapObject> _references;
    private final Set<HeapObject> _backRefs;

    private String _data;

    HeapObject( long startAddr, long endAddr ) {
        _startAddr = startAddr;
        _endAddr = endAddr;
        _references = new TreeSet<HeapObject>();
        _backRefs = new TreeSet<HeapObject>();
    }

    void setData( String data ) {
        _data = data;
    }

    String data() {
        return _data;
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

    long size() {
        return _endAddr - _startAddr;
    }

    Iterator<HeapObject> references() {
        return _references.iterator();
    }

    Iterator<HeapObject> backReferences() {
        return _backRefs.iterator();
    }

    @Override public int compareTo( HeapObject other ) {
        if (_startAddr == other._startAddr) {
            return (int)(_endAddr - other._endAddr);
        } else {
            return (int)(_startAddr - other._startAddr);
        }
    }

    @Override public int hashCode() {
        return (int)_startAddr;
    }

    @Override public boolean equals( Object other ) {
        return this == other;
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

    void dumpHtml( File folder ) throws IOException {
        PrintWriter pw = new PrintWriter( new File( folder, name() + ".html" ) );
        pw.println( "<h1>Heap object " + toString() + "</h1>" );
        pw.println( "<p>Start address: 0x" + Long.toHexString( _startAddr ) + "<br>End address: 0x" + Long.toHexString( _endAddr ) + "<br>Size: " + size() + " bytes</p>" );
        pw.println( "<ul>References:<br>" );
        for (Iterator<HeapObject> i = references(); i.hasNext();) {
            HeapObject n = i.next();
            pw.println( "<li><a href='" + n.name() + ".html'>" + n.toString() + "</a>" );
        }
        pw.println( "</ul><ul>Referenced by:<br>" );
        for (Iterator<HeapObject> i = backReferences(); i.hasNext();) {
            HeapObject n = i.next();
            pw.println( "<li><a href='" + n.name() + ".html'>" + n.toString() + "</a>" );
        }
        pw.println( "</ul>" );
        pw.close();
    }

    void dumpDot( PrintStream out ) {
        out.println( "    n" + toString() + ";" );
        for (HeapObject reference : _references) {
            out.println( "    n" + toString() + " -> n" + reference.toString() + ";" );
        }
    }
}
