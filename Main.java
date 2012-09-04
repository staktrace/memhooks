import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
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

        File folder = new File( args[0] );

        HookOutputParser hop = new HookOutputParser();
        BufferedReader br = new BufferedReader( new FileReader( new File( folder, "log" ) ) );
        hop.parse( br );
        br.close();

        HeapAnalyzer ha = new HeapAnalyzer( hop.getHeapObjects() );

        List<MemoryRange> ranges = hop.calculateMemoryRanges();
        List<File> files = new ArrayList<File>();

        boolean fail = false;
        for (int i = 0; i < ranges.size(); i++) {
            File f = new File( folder, "heapdump-" + i + ".bin" );
            if (! f.exists()) {
                files.add( null );
                fail = true;
                System.out.println( "dump binary memory heapdump-" + i + ".bin " + ranges.get( i ).toString() );
            } else if (f.length() < ranges.get( i ).size()) {
                files.add( null );
                fail = true;
                System.out.println( "Error: " + f + " is too short; expected at least " + ranges.get( i ).size() + " bytes" );
            } else {
                files.add( f );
            }
        }
        if (fail) {
            return;
        }

        System.err.println( "Scanning heap..." );
        ha.scanHeap( files, ranges );

        List<Component> components = ha.computeComponents();
        Component biggest = null;
        for (Component component : components) {
            if (biggest == null || component.size() > biggest.size()) {
                biggest = component;
            }
        }

        biggest.dumpHtml( folder );

        //ha.dumpDotGraph( System.out );
    }
}
