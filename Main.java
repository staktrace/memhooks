import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Main {
    public static void main( String[] args ) throws IOException {
        if (args.length == 0) {
            System.err.println( "Usage: java Main <folder>" );
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

        List<Component> components = ha.computeComponents();
        Component biggest = null;
        for (Component component : components) {
            if (biggest == null || component.size() > biggest.size()) {
                biggest = component;
            }
        }

        Map<HeapObject, HeapObject> dominators = biggest.calculateDominators();
        Set<HeapObject> dominatorNodes = new HashSet<HeapObject>();
        for (HeapObject dom : dominators.values()) {
            dominatorNodes.add( dom );
        }
        System.out.println( biggest.toString() + " has " + dominatorNodes.size() + " dominator nodes" );

        //ha.dumpDotGraph();
    }
}
