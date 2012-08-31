import java.io.PrintWriter;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

class DominatorTree {
    private final HeapObject _root;

    DominatorTree( HeapObject root ) {
        _root = root;
    }

    Map<HeapObject, Position> drawGraph() {
        Map<HeapObject, Position> positions = new HashMap<HeapObject, Position>();
        if (_root.isDominator()) {
            positionNodes( positions, _root, 0, 0 );
        }
        return positions;
    }

    private int positionNodes( Map<HeapObject, Position> positions, HeapObject obj, int x, int y ) {
        int width = 0;
        for (Iterator<HeapObject> i = obj.dominatedChildren(); i.hasNext();) {
            HeapObject child = i.next();
            if (child.isDominator()) {
                width += positionNodes( positions, child, x + width, y + 1 );
            }
        }
        positions.put( obj, new Position( x + ((width - 1) / 2), y ) );
        return Math.max( 1, width );
    }

    void dumpHtml( PrintWriter out ) {
        Map<HeapObject, Position> positions = drawGraph();
        for (HeapObject obj : positions.keySet()) {
            Position p = positions.get( obj );
            out.println( "<div style='position: absolute; left: " + (p._x * 5) + "px; top: " + (p._y * 5) + "px; width: 2px; height: 2px; border: solid 1px black; margin: 2px'></div>" );
        }
    }
}
