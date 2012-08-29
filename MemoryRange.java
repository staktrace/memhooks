class MemoryRange {
    private static final long MAX_GAP = 1024 * 1024;

    private long _startAddr;
    private long _endAddr;

    MemoryRange( HeapObject obj ) {
        _startAddr = obj._startAddr;
        _endAddr = obj._endAddr;
    }

    private boolean merge( long otherStart, long otherEnd ) {
        if (_startAddr - otherEnd >= MAX_GAP) {
            return false;
        } else if (otherStart - _endAddr >= MAX_GAP) {
            return false;
        }
        if (otherStart < _startAddr) {
            _startAddr = otherStart;
        }
        if (otherEnd > _endAddr) {
            _endAddr = otherEnd;
        }
        return true;
    }

    boolean merge( HeapObject obj ) {
        return merge( obj._startAddr, obj._endAddr );
    }

    boolean merge( MemoryRange range ) {
        return merge( range._startAddr, range._endAddr );
    }

    boolean contains( HeapObject obj ) {
        return (_startAddr <= obj._startAddr) && (_endAddr >= obj._endAddr);
    }

    int toOffset( long addr ) {
        if (addr < _startAddr || addr > _endAddr) {
            throw new IllegalArgumentException( "Address 0x" + Long.toHexString( addr ) + " not contained in range " + this.toString() );
        }
        return (int)(addr - _startAddr);
    }

    long size() {
        return _endAddr - _startAddr;
    }

    @Override public String toString() {
        return "0x" + Long.toHexString( _startAddr ) + " 0x" + Long.toHexString( _endAddr );
    }
}
