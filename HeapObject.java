import java.util.Set;
import java.util.TreeSet;

class HeapObject implements Comparable<HeapObject> {
    final long _startAddr;
    final long _endAddr;

    private final Set<HeapObject> _pointers;

    HeapObject( long startAddr, long endAddr ) {
        _startAddr = startAddr;
        _endAddr = endAddr;
        _pointers = new TreeSet<HeapObject>();
    }

    void addPointer( HeapObject target ) {
        if (target != null) {
            _pointers.add( target );
        }
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

    void dump() {
        System.out.println( "Block 0x" + Long.toHexString( _startAddr ) + " size " + (_endAddr - _startAddr) );
        for (HeapObject target : _pointers) {
            System.out.println( "    references block at 0x" + Long.toHexString( target._startAddr ) );
        }
        System.out.println();
    }
}
