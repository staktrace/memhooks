import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.ByteOrder;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class HeapAnalyzer {
    private static final ByteOrder MEMORY = ByteOrder.LITTLE_ENDIAN;
    private static final int ALIGNMENT = 4;

    private final Map<Long, HeapObject> _heapObjects;
    private final AddressTreeNode _addressTreeRoot;

    public HeapAnalyzer( Map<Long, HeapObject> heapObjects ) {
        _heapObjects = heapObjects;
        AddressTreeNode root = null;
        for (HeapObject obj : heapObjects.values()) {
            if (root == null) {
                root = new AddressTreeNode( obj );
            } else {
                root.insert( obj );
            }
        }
        _addressTreeRoot = root;
    }

    private long align( long value, boolean roundUp ) {
        long aligned = (value & ~(ALIGNMENT - 1));
        if (roundUp && (value & (ALIGNMENT - 1)) != 0) {
            aligned += ALIGNMENT;
        }
        return aligned;
    }

    private void visitDumpFiles( List<File> dumpFiles, List<MemoryRange> ranges, PointerVisitor visitor ) throws IOException {
        for (int i = 0; i < dumpFiles.size(); i++) {
            File dumpFile = dumpFiles.get( i );
            MemoryRange range = ranges.get( i );

            FileInputStream fis = new FileInputStream( dumpFile );
            FileChannel fc = fis.getChannel();
            MappedByteBuffer buf = fc.map( FileChannel.MapMode.READ_ONLY, 0, dumpFile.length() );
            buf.order( MEMORY );
            for (HeapObject obj : _heapObjects.values()) {
                if (! range.contains( obj )) {
                    continue;
                }
                int start = range.toOffset( align( obj.startAddr(), true ) );
                int end = range.toOffset( align( obj.endAddr(), false ) );
                while (start < end) {
                    long pointer = (buf.getInt( start ) & 0xFFFFFFFFL);
                    visitor.pointer( obj, pointer );
                    start += ALIGNMENT;
                }
            }
            fis.close();
        }
    }

    private static interface PointerVisitor {
        public void pointer( HeapObject obj, long pointer );
    }

    public void scanHeap( List<File> dumpFiles, List<MemoryRange> ranges ) throws IOException {
        // first pass: split heap objects based on pointers that to middle of them
        final List<HeapObject> subItems = new ArrayList<HeapObject>();
        visitDumpFiles( dumpFiles, ranges, new PointerVisitor() {
            @Override public void pointer( HeapObject obj, long pointer ) {
                HeapObject target = _addressTreeRoot.find( pointer );
                if (target != null) {
                    HeapObject subItem = target.split( pointer );
                    if (subItem != null) {
                        subItems.add( subItem );
                        _addressTreeRoot.insert( subItem );
                    }
                }
            }
        } );
        System.err.println( "Split " + subItems.size() + " heap objects during scanning" );
        for (HeapObject subItem : subItems) {
            _heapObjects.put( subItem.startAddr(), subItem );
        }

        // second pass: build reference graph
        visitDumpFiles( dumpFiles, ranges, new PointerVisitor() {
            @Override public void pointer( HeapObject obj, long pointer ) {
                obj.addReference( _heapObjects.get( pointer ) );
            }
        } );
    }

    public List<Component> computeComponents() {
        List<Component> components = new ArrayList<Component>();
        for (HeapObject obj : _heapObjects.values()) {
            if (obj.isRoot()) {
                boolean found = false;
                for (Component component : components) {
                    if (component.contains( obj )) {
                        found = true;
                        break;
                    }
                }
                if (! found) {
                    components.add( new Component( obj ) );
                }
            }
        }
        return components;
    }

    public void dumpDotGraph( PrintStream out ) {
        out.println( "digraph heap {" );
        for (HeapObject obj : _heapObjects.values()) {
            obj.dumpDot( out );
        }
        out.println( "}" );
    }
}
