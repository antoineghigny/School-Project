package model;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;

class BoardTest {

    @Test
    void put() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertNotNull(board.getTileAt(new Point(5, 0)));
    }

    @Test
    void delete() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        board.put(new Tile(Color.BLUE), new Point(4, 0));
        board.put(new Tile(Color.YELLOW), new Point(3, 0));
        board.delete(new Point(3, 0));
        board.delete(new Point(4, 0));

        assertNull(board.getTileAt(new Point(3, 0)));
        assertNull(board.getTileAt(new Point(4, 0)));
    }


    @Test
    void getTile() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertSame(board.getTileAt(new Point(5, 0)).getColor(), Color.GREEN);
    }

    @Test
    void getTileAt_false() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertNotSame(board.getTileAt(new Point(5, 0)).getColor(), Color.RED);
    }

    @Test
    void getTileAt_true() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertSame(board.getTileAt(new Point(5, 0)).getColor(), Color.GREEN);
    }

    @Test
    void isTile_true() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertTrue(board.isTile(new Point(5, 0)));
    }

    @Test
    void isTile_false() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        assertFalse(board.isTile(new Point(4, 0)));
    }

    @Test
    void moveTile_true() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        board.moveTile(new Point(5, 0), new Point(3, 0));
        assertTrue(board.isTile(new Point(3, 0)));
    }

    @Test
    void moveTile_false() {
        Board board = new Board(6, 10);
        board.put(new Tile(Color.GREEN), new Point(5, 0));
        board.moveTile(new Point(5, 0), new Point(3, 0));
        assertFalse(board.isTile(new Point(5, 0)));
    }
}