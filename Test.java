import java.util.Map;

public class Test {
    private void check( Map<HeapObject, HeapObject> dominators, HeapObject node, HeapObject expected ) {
        try {
            HeapObject actual = dominators.get( node );
            String actualData = (actual == null ? "null" : actual.data());
            String expData = (expected == null ? "null" : expected.data());
            if (actualData.equals( expData )) {
                System.out.print( '.' );
                return;
            }
            System.out.println( "F Expected " + expData + "; actual " + actualData );
        } catch (Exception e) {
            System.out.print( 'E' );
        }
    }

    private void testComponent() {
        // this is the flowgraph from the original paper by Lengauer and Tarjan
        // numbers are thrown in so that the DFS comes out the same way it does in the paper
        HeapObject r = new HeapObject( 2, 2 ); r.setData( "r" );
        HeapObject a = new HeapObject( 3, 3 ); a.setData( "a" );
        HeapObject b = new HeapObject( 4, 4 ); b.setData( "b" );
        HeapObject c = new HeapObject( 5, 5 ); c.setData( "c" );
        HeapObject d = new HeapObject( 1, 1 ); d.setData( "d" );
        HeapObject e = new HeapObject( 6, 6 ); e.setData( "e" );
        HeapObject f = new HeapObject( 8, 8 ); f.setData( "f" );
        HeapObject g = new HeapObject( 7, 7 ); g.setData( "g" );
        HeapObject h = new HeapObject( 9, 9 ); h.setData( "h" );
        HeapObject i = new HeapObject( 10, 10 ); i.setData( "i" );
        HeapObject j = new HeapObject( 11, 11 ); j.setData( "j" );
        HeapObject k = new HeapObject( 12, 12 ); k.setData( "k" );
        HeapObject l = new HeapObject( 13, 13 ); l.setData( "l" );

        a.addReference( d );
        b.addReference( a );
        b.addReference( d );
        b.addReference( e );
        c.addReference( f );
        c.addReference( g );
        d.addReference( l );
        d.addReference( l );
        e.addReference( h );
        f.addReference( i );
        g.addReference( i );
        g.addReference( j );
        h.addReference( e );
        h.addReference( k );
        i.addReference( k );
        j.addReference( i );
        k.addReference( i );
        //k.addReference( r );  // keep r as a root node
        l.addReference( h );
        r.addReference( a );
        r.addReference( b );
        r.addReference( c );

        Component component = new Component( a );
        Map<HeapObject, HeapObject> dominators = component.getDominators();
        check( dominators, a, r );
        check( dominators, b, r );
        check( dominators, c, r );
        check( dominators, d, r );
        check( dominators, e, r );
        check( dominators, f, c );
        check( dominators, g, c );
        check( dominators, h, r );
        check( dominators, i, r );
        check( dominators, j, g );
        check( dominators, k, r );
        check( dominators, l, d );
        System.out.println();
    }

    public static void main( String[] args ) {
        Test t = new Test();
        t.testComponent();
    }
}
