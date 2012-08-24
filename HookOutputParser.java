import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
                System.err.println( "Error parsing output line: " + s );
                continue;
            }
            count++;
            StringTokenizer st = new StringTokenizer( s.substring( ixAlloc < 0 ? ixFree : ixAlloc ) );
            st.nextToken();
            long addr = parseAddr( st.nextToken() );
            if (ixFree >= 0) {
                _heapObjects.remove( addr );
            } else {
                _heapObjects.put( addr, new HeapObject( addr, parseAddr( st.nextToken() ) ) );
            }
        }
        System.err.println( "HookOutputParser: completed parsing " + count + " hook output lines; " + _heapObjects.size() + " heap objects remaining" );
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
                for (int j = ranges.size() - 1; i >= 0; i--) {
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

    private class HeapObject {
        final long _startAddr;
        final long _endAddr;

        HeapObject( long startAddr, long endAddr ) {
            _startAddr = startAddr;
            _endAddr = endAddr;
        }
    }

    private class MemoryRange {
        private static final long MAX_GAP = 1024 * 1024;

        private long _startAddr;
        private long _endAddr;

        MemoryRange( HeapObject obj ) {
            _startAddr = obj._startAddr;
            _endAddr = obj._endAddr;
        }

        private boolean merge( long otherStart, long otherEnd ) {
            if (_startAddr - otherEnd >= MAX_GAP) {
                return false;
            } else if (otherStart - _endAddr >= MAX_GAP) {
                return false;
            }
            if (otherStart < _startAddr) {
                _startAddr = otherStart;
            }
            if (otherEnd > _endAddr) {
                _endAddr = otherEnd;
            }
            return true;
        }

        boolean merge( HeapObject obj ) {
            return merge( obj._startAddr, obj._endAddr );
        }

        boolean merge( MemoryRange range ) {
            return merge( range._startAddr, range._endAddr );
        }

        @Override public String toString() {
            return "MemoryRange: 0x" + Long.toHexString( _startAddr ) + " 0x" + Long.toHexString( _endAddr );
        }
    }

    public static void main( String[] args ) throws IOException {
        HookOutputParser hop = new HookOutputParser();
        if (args.length > 0) {
            for (String arg : args) {
                BufferedReader br = new BufferedReader( new FileReader( arg ) );
                hop.parse( br );
                br.close();
            }
        } else {
            BufferedReader br = new BufferedReader( new InputStreamReader( System.in ) );
            hop.parse( br );
            br.close();
        }

        List<MemoryRange> ranges = hop.calculateMemoryRanges();
        for (MemoryRange range : ranges) {
            System.out.println( range );
        }
    }
}
