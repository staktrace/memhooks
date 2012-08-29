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

    @Override public String toString() {
        return "0x" + Long.toHexString( _startAddr );
    }

    void dump( PrintStream out ) {
        out.println( "Block " + toString() + " size " + (_endAddr - _startAddr) );
        for (HeapObject reference : _references) {
            out.println( "    references block at " + reference.toString() );
        }
        out.println();
    }

    void dumpDot( PrintStream out ) {
        out.println( "    n" + toString() + ";" );
        for (HeapObject reference : _references) {
            out.println( "    n" + toString() + " -> n" + reference.toString() + ";" );
        }
    }
}
