package g56359.luckynumbers.model;

import java.util.ArrayList;
import java.util.List;
import g56359.luckynumbers.model.Game;
import java.util.Collections;

public class Deck {

    private List<Tile> faceUpTiles;
    private List<Tile> faceDownTiles;

    /**
     * Create 2 ArrayList, for faceUpTiles, create an empty list, it will be
     * enlarged later, for faceDownTiles, create a card size 20 x the number of
     * players in the game.
     *
     * @param playerCount
     */
    public Deck(int playerCount) {

        faceUpTiles = new ArrayList<>();
        faceDownTiles = new ArrayList<>();
        for (int j = 0; j < playerCount; j++) {
            for (int i = 1; i <= 20; i++) {
                faceDownTiles.add(new Tile(i));
            }
        }
        Collections.shuffle(faceDownTiles);
    }

    /**
     * @return the number of cards face down
     */
    public int faceDownCount() {
        return faceDownTiles.size();
    }

    /**
     * choose the last tile in the game and remove the faceDownTiles tile
     *
     * @return the last tile in the game that was shuffled in the deck method
     */
    public Tile pickFaceDown() {
        Tile actualTile = faceDownTiles.get(faceDownTiles.size() - 1);
        faceDownTiles.remove(faceDownTiles.size() - 1);
        return actualTile;
    }

    /**
     * @return the number of cards face up
     */
    public int faceUpCount() {
        return faceUpTiles.size();

    }

    /**
     * @return the list of visible cards
     */
    public List<Tile> getAllFaceUp() {
        return faceUpTiles;
    }

    /**
     * @param tile the tile chosen by the user
     * @return true if the map is contained in faceUpTiles
     */
    public boolean hasFaceUp(Tile tile) {
        return faceUpTiles.contains(tile);
    }

    /**
     * remove the tile chosen by the user
     *
     * @param tile the tile chosen by the user
     */
    public void pickFaceUp(Tile tile) {
        faceUpTiles.remove(tile);
    }

    /**
     * add the current tile in faceUpTiles.
     *
     * @param tile the current tile
     */
    public void putBack(Tile tile) {
        faceUpTiles.add(tile);
    }

    List<Tile> getAllFaceDown() {
        return faceDownTiles;
    }

    Tile lastTile() {
        return faceDownTiles.get(faceDownTiles.size() - 1);
    }

    int countFaceUpForTest() {
        return faceUpTiles.size();

    }

    List<Tile> getAllFaceUp_for_test() {
        return faceUpTiles;
    }
}
