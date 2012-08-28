import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

class Subgraph {
    private final Set<HeapObject> _roots;
    private final Set<HeapObject> _nodes;

    public Subgraph( HeapObject start ) {
        _roots = new HashSet<HeapObject>();
        _nodes = new HashSet<HeapObject>();

        Queue<HeapObject> bfsQueue = new LinkedList<HeapObject>();
        if (add( start )) {
            bfsQueue.add( start );
        }
        for (HeapObject obj = bfsQueue.poll(); obj != null; obj = bfsQueue.poll()) {
            for (Iterator<HeapObject> i = obj.backReferences(); i.hasNext();) {
                HeapObject parent = i.next();
                if (add( parent )) {
                    bfsQueue.add( parent );
                }
            }
            for (Iterator<HeapObject> i = obj.references(); i.hasNext();) {
                HeapObject child = i.next();
                if (add( child )) {
                    bfsQueue.add( child );
                }
            }
        }
    }

    private boolean add( HeapObject object ) {
        if (_nodes.add( object )) {
            if (object.isRoot()) {
                _roots.add( object );
            }
            return true;
        }
        return false;
    }

    boolean contains( HeapObject obj ) {
        return _nodes.contains( obj );
    }

    public long size() {
        long size = 0;
        for (HeapObject node : _nodes) {
            size += node.size();
        }
        return size;
    }

    @Override public String toString() {
        return "Subgraph with " + _nodes.size() + " nodes, " + _roots.size() + " roots, and " + size() + " bytes";
    }
}
