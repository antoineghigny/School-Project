/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.luckynumbers.model;

import java.util.ArrayList;
import java.util.List;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author g56359
 */
public class DeckTest {

    private List<Integer> faceUpTiles;
    private List<Integer> faceDownTiles;

    public DeckTest() {
    }

    /**
     * Test of faceDownCount method, of class Deck.
     */
    @Test
    public void testFaceDownCount_20x2() {
        System.out.println("faceDownCount");
        Deck deck = new Deck(2);
        int size = deck.faceDownCount();
        assertEquals(size, 40);
    }

    /**
     * Test of faceDownCount method, of class Deck.
     */
    @Test
    public void testFaceDownCount_20x4() {
        System.out.println("faceDownCount");
        Deck deck = new Deck(4);
        int size = deck.faceDownCount();
        assertEquals(size, 80);
    }

    /**
     * Test of pickFaceDown method, of class Deck.
     */
    @Test
    public void testPickFaceDown() {
        System.out.println("pickFaceDown_normal");
        Deck deck = new Deck(2);
        Tile lastTile = deck.lastTile();
        Tile result = deck.pickFaceDown();
        assertEquals(result, lastTile);
    }

    /**
     * Test of faceUpCount method, of class Deck.
     */
    @Test
    public void testFaceUpCount() {
        System.out.println("faceUpCount");
        Deck deck = new Deck(2);
        Tile actuelTile = deck.pickFaceDown();
        deck.putBack(actuelTile);
        Tile otherTile = deck.pickFaceDown();
        deck.putBack(otherTile);
        int result = deck.faceUpCount();
        assertEquals(result, deck.countFaceUpForTest());
    }

    /**
     * Test of getAllFaceUp method, of class Deck.
     */
    @Test
    public void testGetAllFaceUp() {
        System.out.println("getAllFaceUp");
        Deck deck = new Deck(2);
        Tile actuelTile = deck.pickFaceDown();
        deck.putBack(actuelTile);
        Tile otherTile = deck.pickFaceDown();
        deck.putBack(otherTile);
        List<Tile> result = deck.getAllFaceUp();
        List<Tile> expResult = deck.getAllFaceUp_for_test();
        assertEquals(result, expResult);
    }

    /**
     * Test of hasFaceUp method, of class Deck.
     */
    @Test
    public void testHasFaceUp() {
        System.out.println("hasFaceUp");

        Deck deck = new Deck(2);
        Tile actuelTile = new Tile(2);
        deck.hasFaceUp(actuelTile);
        assertEquals(actuelTile, new Tile(2));
    }

    /**
     * Test of pickFaceUp method, of class Deck.
     */
    @Test
    public void testPickFaceUp() {
        System.out.println("pickFaceUp");
        Deck deck = new Deck(2);
        Tile actuelTile = deck.pickFaceDown();
        deck.putBack(actuelTile);
        Tile otherTile = deck.pickFaceDown();
        deck.putBack(otherTile);
        deck.pickFaceUp(otherTile);
        assertEquals(deck.faceUpCount(), 1);
    }

    /**
     * Test of putBack method, of class Deck.
     */
    @Test
    public void testPutBack() {
        System.out.println("putBack");
        Deck deck = new Deck(2);

        Tile actuelTile = deck.pickFaceDown();
        deck.putBack(actuelTile);
        Tile otherTile = deck.pickFaceDown();
        deck.putBack(otherTile);

        assertEquals(deck.faceUpCount(), 2);
    }

}
