import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

class Subgraph {
    private final HeapObject _dummyRoot;
    private final Set<HeapObject> _roots;
    private final Set<HeapObject> _nodes;
    private final Map<HeapObject, HeapObject> _dominators;

    public Subgraph( HeapObject start ) {
        _dummyRoot = new HeapObject( 0, 0 );
        _roots = new HashSet<HeapObject>();
        _nodes = new HashSet<HeapObject>();
        _dominators = new HashMap<HeapObject, HeapObject>();

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

    private HeapObject eval( Set<HeapObject> forest, Map<HeapObject, HeapObject> parents, Map<HeapObject, Integer> semis, HeapObject obj ) {
        if (! forest.contains( obj )) {
            // obj is the root of a tree in the forest
            return obj;
        }

        HeapObject best = obj;
        int bestSemi = semis.get( obj );

        while (true) {
            HeapObject parent = parents.get( obj );
            if (! forest.contains( parent )) {
                break;
            }

            obj = parent;
            if (semis.get( obj ) < bestSemi) {
                best = obj;
                bestSemi = semis.get( obj );
            }
        }
        return best;
    }

    public Map<HeapObject, HeapObject> calculateDominators() {
        Map<HeapObject, HeapObject> dominators = new HashMap<HeapObject, HeapObject>();
        Map<HeapObject, Integer> semiDominators = new HashMap<HeapObject, Integer>();
        List<HeapObject> numbered = new ArrayList<HeapObject>( _nodes.size() );
        Map<HeapObject, HeapObject> parents = new HashMap<HeapObject, HeapObject>();

        semiDominators.put( _dummyRoot, numbered.size() );
        numbered.add( _dummyRoot );

        {   // step 1, DFS simulating "normal stack recursion" DFS from the paper
            // (that's why I keep the parentStack)
            Stack<HeapObject> dfsStack = new Stack<HeapObject>();
            Stack<HeapObject> parentStack = new Stack<HeapObject>();
            for (HeapObject root : _roots) {
                dfsStack.push( root );
                parentStack.push( _dummyRoot );
            }
            while (! dfsStack.empty()) {
                HeapObject obj = dfsStack.pop();
                HeapObject parent = parentStack.pop();
                if (semiDominators.containsKey( obj )) {
                    continue;
                }

                semiDominators.put( obj, numbered.size() );
                numbered.add( obj );
                parents.put( obj, parent );
                for (Iterator<HeapObject> i = obj.references(); i.hasNext();) {
                    HeapObject child = i.next();
                    if (parents.containsKey( child )) {
                        continue;
                    }
                    dfsStack.push( child );
                    parentStack.push( obj );
                }
            }
        }

        {   // steps 2 and 3
            Set<HeapObject> forest = new HashSet<HeapObject>(); // forest.contains(x) means the edge (parents.get(x), x) is in the forest
            Map<HeapObject, Set<HeapObject>> buckets = new HashMap<HeapObject, Set<HeapObject>>();

            for (int i = numbered.size() - 1; i > 0; i--) {
                HeapObject obj = numbered.get( i );

                // step 2
                for (Iterator<HeapObject> it = obj.backReferences(); it.hasNext();) {
                    HeapObject u = eval( forest, parents, semiDominators, it.next() );
                    if (semiDominators.get( u ) < semiDominators.get( obj )) {
                        semiDominators.put( obj, semiDominators.get( u ) );
                    }
                }
                if (obj.isRoot()) {
                    HeapObject u = eval( forest, parents, semiDominators, _dummyRoot );
                    if (semiDominators.get( u ) < semiDominators.get( obj )) {
                        semiDominators.put( obj, semiDominators.get( u ) );
                    }
                }

                HeapObject semiDom = numbered.get( semiDominators.get( obj ) );
                Set<HeapObject> bucket = buckets.get( semiDom );
                if (bucket == null) {
                    bucket = new HashSet<HeapObject>();
                    buckets.put( semiDom, bucket );
                }
                bucket.add( obj );
                forest.add( obj );  // LINK

                // step 3
                bucket = buckets.get( parents.get( obj ) );
                if (bucket != null) {
                    for (HeapObject dominated : bucket) {
                        HeapObject u = eval( forest, parents, semiDominators, dominated );
                        dominators.put( dominated, (semiDominators.get( u ) < semiDominators.get( dominated )) ? u : parents.get( obj ));
                    }
                    bucket.clear();
                }
            }
        }

        {   // step 4
            for (int i = 1; i < numbered.size(); i++) {
                HeapObject obj = numbered.get( i );
                if (dominators.get( obj ) != numbered.get( semiDominators.get( obj ) )) {
                    dominators.put( obj, dominators.get( dominators.get( obj ) ) );
                }
            }
        }

        return dominators;
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
