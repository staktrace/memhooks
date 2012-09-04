class AddressTreeNode {
    private final HeapObject _heapObject;
    private AddressTreeNode _left;
    private AddressTreeNode _right;

    AddressTreeNode( HeapObject obj ) {
        _heapObject = obj;
    }

    void insert( HeapObject obj ) {
        int comp = obj.compareTo( _heapObject );
        if (comp < 0) {
            if (_left == null) {
                _left = new AddressTreeNode( obj );
            } else {
                _left.insert( obj );
            }
        } else if (comp > 0) {
            if (_right == null) {
                _right = new AddressTreeNode( obj );
            } else {
                _right.insert( obj );
            }
        }
    }

    HeapObject find( long address ) {
        if (address < _heapObject.startAddr()) {
            return (_left == null ? null : _left.find( address ));
        } else if (address >= _heapObject.endAddr()) {
            return (_right == null ? null : _right.find( address ));
        } else {
            return _heapObject;
        }
    }
}
