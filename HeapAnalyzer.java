import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
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

    public List<Subgraph> computeSubgraphs() {
        List<Subgraph> subgraphs = new ArrayList<Subgraph>();
        for (HeapObject obj : _heapObjects.values()) {
            if (obj.isRoot()) {
                boolean found = false;
                for (Subgraph subgraph : subgraphs) {
                    if (subgraph.contains( obj )) {
                        found = true;
                        break;
                    }
                }
                if (! found) {
                    subgraphs.add( new Subgraph( obj ) );
                }
            }
        }
        return subgraphs;
    }

    public void dumpDotGraph() {
        System.out.println( "digraph heap {" );
        for (HeapObject obj : _heapObjects.values()) {
            obj.dumpDot();
        }
        System.out.println( "}" );
    }

    public static void main( String[] args ) throws IOException {
        if (args.length == 0) {
            System.err.println( "Usage: java HeapAnalyzer <folder>" );
            System.err.println( "   <folder>/log should contain the memhooks log output" );
            System.err.println( "   <folder>/heapdump-*.bin files should contain the heap dumps" );
            return;
        }

        HookOutputParser hop = new HookOutputParser();
        BufferedReader br = new BufferedReader( new FileReader( args[0] + File.separator + "log" ) );
        hop.parse( br );
        br.close();

        HeapAnalyzer ha = new HeapAnalyzer( hop.getHeapObjects() );

        List<MemoryRange> ranges = hop.calculateMemoryRanges();
        boolean fail = false;
        for (int i = 0; i < ranges.size(); i++) {
            File f = new File( args[0] + File.separator + "heapdump-" + i + ".bin" );
            if (! f.exists()) {
                fail = true;
                System.out.println( "dump binary memory heapdump-" + i + ".bin " + ranges.get( i ).toString() );
            } else if (f.length() < ranges.get( i ).size()) {
                fail = true;
                System.out.println( "Error: " + f + " is too short; expected at least " + ranges.get( i ).size() + " bytes" );
            } else {
                System.err.println( "Scanning " + ranges.get( i ).toString() + " from file heapdump-" + i + ".bin" );
                ha.scanHeap( f, ranges.get( i ) );
            }
        }

        if (fail) {
            return;
        }

        List<Subgraph> subgraphs = ha.computeSubgraphs();
        for (Subgraph subgraph : subgraphs) {
            System.out.println( subgraph );
        }

        //ha.dumpDotGraph();
    }
}
