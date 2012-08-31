class Position {
    final int _x;
    final int _y;

    Position( int x, int y ) {
        _x = x;
        _y = y;
    }

    @Override public boolean equals( Object o ) {
        if (o instanceof Position) {
            Position p = (Position)o;
            return p._x == _x && p._y == _y;
        }
        return false;
    }

    @Override public String toString() {
        return _x + ", " + _y;
    }
}
