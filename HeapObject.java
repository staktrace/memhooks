import java.util.Set;
import java.util.TreeSet;

class HeapObject {
    final long _startAddr;
    final long _endAddr;

    private final Set<HeapObject> _pointers;

    HeapObject( long startAddr, long endAddr ) {
        _startAddr = startAddr;
        _endAddr = endAddr;
        _pointers = new TreeSet<HeapObject>();
    }

    void addPointer( HeapObject target ) {
        _pointers.add( target );
    }

    @Override public int hashCode() {
        return (int)_startAddr;
    }

    @Override public boolean equals( Object other ) {
        return this == other;
    }
}
