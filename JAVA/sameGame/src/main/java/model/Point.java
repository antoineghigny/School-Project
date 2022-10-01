package model;

public class Point {
    private final int x;
    private final int y;
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Getter of the X position
     * @return the X
     */
    public int getX() {
        return x;
    }
    /**
     * Getter of the Y position
     * @return the Y
     */
    public int getY() {
        return y;
    }
}
