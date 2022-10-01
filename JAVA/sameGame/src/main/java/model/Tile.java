package model;

public class Tile {

    private final Color color;

    /**
     * The constructor of the tile with a Color as parameter.
     * @param color the color of the tile
     */
    public Tile(Color color) {
        this.color = color;
    }

    /**
     * Getter of Color
     * @return the Color of the Tile
     */
    public Color getColor() {
        return color;
    }
}
