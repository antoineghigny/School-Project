/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.luckynumbers.model;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author antoi
 */
public class TileTest {

    private Tile tile;
    private boolean faceUp;

    public TileTest() {
    }

    /**
     * Test of flipFaceUp method, of class Tile.
     */
    @Test
    public void testFlipFaceUp_true() {
        System.out.println("flipFaceUp-false");
        faceUp = false;
        Tile tile = new Tile(1);
        tile.flipFaceUp();
        assertTrue(tile.isFaceUp());
    }

    /**
     * Test of flipFaceUp method, of class Tile.
     */
    @Test
    public void testFlipFaceUp_false() {
        System.out.println("flipFaceUp");
        faceUp = true;
        Tile tile = new Tile(1);
        tile.flipFaceUp();
        assertTrue(tile.isFaceUp());
    }

}
