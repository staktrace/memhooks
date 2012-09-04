import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

public class HookOutputParser {
    private final Map<Long, HeapObject> _heapObjects;

    public HookOutputParser() {
        _heapObjects = new HashMap<Long, HeapObject>();
    }

    private long parseAddr( String pointer ) {
        return Long.parseLong( pointer.substring( 2 ), 16 );
    }

    public void parse( BufferedReader br ) throws IOException {
        int count = 0;
        for (String s = br.readLine(); s != null; s = br.readLine()) {
            if (s.indexOf( "memhook" ) < 0) {
                continue;
            }
            int ixAlloc = s.indexOf( "memhook-alloc" );
            int ixFree = s.indexOf( "memhook-free" );
            if (ixAlloc < 0 && ixFree < 0) {
                continue;
            }
            if ((ixAlloc >= 0) && (ixFree >= 0)) {
                System.out.println( "Error parsing output line: " + s );
                continue;
            }
            count++;
            StringTokenizer st = new StringTokenizer( s.substring( ixAlloc < 0 ? ixFree : ixAlloc ) );
            st.nextToken();
            long addr = parseAddr( st.nextToken() );
            if (ixFree >= 0) {
                _heapObjects.remove( addr );
            } else {
                if (_heapObjects.get( addr ) != null) {
                    System.out.println( "Error: reallocating block at 0x" + Long.toHexString( addr ) );
                }
                _heapObjects.put( addr, new HeapObject( addr, parseAddr( st.nextToken() ) ) );
            }
        }
        long memUsed = 0;
        for (HeapObject obj : _heapObjects.values()) {
            memUsed += obj.size();
        }
        System.err.println( "HookOutputParser: completed parsing " + count + " hook output lines; " + _heapObjects.size() + " heap objects remaining using " + memUsed + " bytes" );
    }

    public Map<Long, HeapObject> getHeapObjects() {
        return _heapObjects;
    }

    public List<MemoryRange> calculateMemoryRanges() {
        List<MemoryRange> ranges = new ArrayList<MemoryRange>();
        for (HeapObject obj : _heapObjects.values()) {
            boolean merged = false;
            for (MemoryRange range : ranges) {
                if (range.merge( obj )) {
                    merged = true;
                    break;
                }
            }
            if (! merged) {
                ranges.add( new MemoryRange( obj ) );
            }
        }

        boolean modified = true;
        while (modified) {
            modified = false;
            for (int i = ranges.size() - 1; i >= 0; i--) {
                MemoryRange toMerge = ranges.get( i );
                for (int j = i - 1; i >= 0; i--) {
                    if (i == j) {
                        continue;
                    }
                    if (ranges.get( j ).merge( toMerge )) {
                        modified = true;
                        ranges.remove( i );
                        break;
                    }
                }
            }
        }

        return ranges;
    }
}
