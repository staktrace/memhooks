import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
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

    public HeapAnalyzer( Map<Long, HeapObject> heapObjects ) {
        _heapObjects = heapObjects;
    }

    private long align( long value, boolean roundUp ) {
        long aligned = (value & ~(ALIGNMENT - 1));
        if (roundUp && (value & (ALIGNMENT - 1)) != 0) {
            aligned += ALIGNMENT;
        }
        return aligned;
    }

    public void scanHeap( File dumpFile, MemoryRange range ) throws IOException {
        FileInputStream fis = new FileInputStream( dumpFile );
        FileChannel fc = fis.getChannel();
        MappedByteBuffer buf = fc.map( FileChannel.MapMode.READ_ONLY, 0, dumpFile.length() );
        buf.order( MEMORY );
        for (HeapObject obj : _heapObjects.values()) {
            if (! range.contains( obj )) {
                continue;
            }
            int start = range.toOffset( align( obj._startAddr, true ) );
            int end = range.toOffset( align( obj._endAddr, false ) );
            while (start < end) {
                long pointer = (buf.getInt( start ) & 0xFFFFFFFFL);
                obj.addReference( _heapObjects.get( pointer ) );
                start += ALIGNMENT;
            }
        }
        fis.close();
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

    public void dumpDotGraph() {
        System.out.println( "digraph heap {" );
        for (HeapObject obj : _heapObjects.values()) {
            obj.dumpDot();
        }
        System.out.println( "}" );
    }
}
