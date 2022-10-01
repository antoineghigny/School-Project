package model;

import java.util.Arrays;

/**
 * The board class contains the methods which make it possible
 * to interact with the 2D board, methods which make it possible
 * to check that a tile exists...
 */
public class Board {
    private final int height;
    private final int width;
    private final Tile[][] tile;

    /**
     * Constructor of the board class which initializes
     * the attributes and the 2D array of Tile.
     * @param height The height of the board
     * @param width The width of the board
     */
    public Board(int height, int width) {
        this.width = width;
        this.height = height;
        tile = new Tile[height][width];
    }

    public Board(Board board){
        this.width = board.width;
        this.height = board.height;
        this.tile = Arrays.stream(board.getTile())
                .map(a ->  Arrays.copyOf(a, a.length))
                .toArray(Tile[][]::new);
    }

    /**
     * A method that places a tile at a certain point.
     * @param tile The tile to place
     * @param point A point that has a certain position in x and y.
     */
    public void put(Tile tile, Point point) {
        this.tile[point.getX()][point.getY()] = tile;
    }

    /**
     * Method that removes a tile at a certain position.
     * @param point A point that has a certain position in x and y.
     */
    public void delete(Point point) {
        tile[point.getX()][point.getY()] = null;
    }

    /**
     * Method that returns the height attribute (getter)
     * @return The height of the board
     */
    public int getHeight() {
        return height;
    }

    /**
     * Method that returns the width attribute (getter)
     * @return The width of the board
     */
    public int getWidth() {
        return width;
    }

    /**
     * A method that returns a tile to a specified position.
     * @param point A point that has a certain position in x and y.
     * @return A tile
     */
    public Tile getTileAt(Point point) {
        return tile[point.getX()][point.getY()];
    }

    /**
     * Method that returns true if there is a tile at a position indicates
     * false otherwise.
     * @param point A point that has a certain position in x and y.
     * @return true (if there is a tile at a given position), false (if there is not)
     */
    public boolean isTile(Point point) {
        return tile[point.getX()][point.getY()] != null;
    }

    /**
     * A method of moving a tile from one point to another
     * (places the tile from point 1 to point 2 and
     * then removes the tile at point 1).
     * @param point1 A first point that has a certain position in x and y.
     * @param point2 A second point that has a certain position in x and y.
     */
    public void moveTile(Point point1, Point point2) {
        put(tile[point1.getX()][point1.getY()], point2);
        delete(point1);
    }

    public Tile[][] getTile() {
        return tile;
    }
}