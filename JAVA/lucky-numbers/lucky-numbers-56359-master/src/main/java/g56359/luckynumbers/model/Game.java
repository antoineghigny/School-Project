package g56359.luckynumbers.model;

import static g56359.luckynumbers.model.State.GAME_OVER;
import static g56359.luckynumbers.model.State.NOT_STARTED;
import static g56359.luckynumbers.model.State.PICK_TILE;
import static g56359.luckynumbers.model.State.PLACE_OR_DROP_TILE;
import static g56359.luckynumbers.model.State.PLACE_TILE;
import static g56359.luckynumbers.model.State.TURN_END;
import java.awt.DisplayMode;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 *
 *
 * @author antoi
 */
public class Game implements Model {

    private State state;
    private int playerCount;
    private int currentPlayerNumber;
    private Board[] boards;
    private Tile pickedTile;
    private Deck deck;

    public Game() {
        state = NOT_STARTED;
    }

    @Override
    public void start(int playerCount) {
        this.deck = new Deck(playerCount);
        if (state != NOT_STARTED && state != GAME_OVER) {
            throw new IllegalStateException("L'état du jeu n'est pas à NOT_STARTED ou GAME_OVER");
        }
        if (playerCount > 4 || playerCount < 2) {
            throw new IllegalArgumentException("Le nombre de joueurs est plus petit que 2 ou plus grand que 4");
        }
        this.currentPlayerNumber = 0;
        boards = new Board[playerCount];
        for (int i = 0; i < playerCount; i++) {
            boards[i] = new Board();
        }
        this.playerCount = playerCount;
        for (int i = 0; i < playerCount; i++) {
            placeDiagonale(i);
            System.out.println();
        }

        state = PICK_TILE;
    }

    private void placeDiagonale(int currentPlayerNumber) {

        ArrayList<Tile> tuilesRestantes = new ArrayList<Tile>();
        for (int k = 0; k < boards[currentPlayerNumber].getSize(); k++) {
            tuilesRestantes.add(pickFaceDownTile());
        }

        Collections.sort(tuilesRestantes, new Comparator<Tile>() {
            @Override
            public int compare(Tile o1, Tile o2) {
                return o1.getValue() - o2.getValue();
            }
        }
        );

        for (int i = 0; i < getBoardSize(); i++) {
            boards[currentPlayerNumber].put(tuilesRestantes.get(i), new Position(i, i));
        }
    }

//    private boolean estCroissant() {
//        int compteur = 0;
//        Tile lastTuile = new Tile(0);
//
//        for (int i = 0; i < getBoardSize(); i++) {
//            for (int j = 0; j < getBoardSize(); j++) {
//                if (i == j) {
//                    for (int k = 0; k < playerCount; k++) {
//                        Tile tuile = boards[k].getTile(new Position(i, j));
//                        if (tuile.getValue() > lastTuile.getValue()) {
//                            lastTuile = boards[k].getTile(new Position(i, j));
//                            compteur++;
//                        }
//                    }
//                }
//            }
//        }
//        return compteur == playerCount*4;
//    }
    @Override
    public int getBoardSize() {

        return boards[currentPlayerNumber].getSize();
    }

    private int random(int max, int min) {
        return (int) (Math.random() * (max - min + 1) + min);
    }

    @Override
    public void putTile(Position pos) {
        if (!boards[currentPlayerNumber].isInside(pos) || !boards[currentPlayerNumber].canBePut(pickedTile, pos)) {
            throw new IllegalArgumentException("Impossible de placer une tuile à la position indiquée");
        }
        if (state != PLACE_TILE && state != PLACE_OR_DROP_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à la position PLACE_TILE");
        }
        if (boards[currentPlayerNumber].getTile(pos) != null) {
            deck.putBack(boards[currentPlayerNumber].getTile(pos));
        }
        boards[currentPlayerNumber].put(pickedTile, pos);

        if (boards[currentPlayerNumber].isFull() || faceDownTileCount() == 0) {
            state = GAME_OVER;
        } else {
            state = TURN_END;
        }
    }

    @Override
    public void nextPlayer() {
        if (state != TURN_END) {
            throw new IllegalStateException("L'état du jeu n'est pas à la position TURN_END");
        }
        if (currentPlayerNumber < playerCount - 1) {
            currentPlayerNumber++;
        } else {
            currentPlayerNumber = 0;
        }
        state = PICK_TILE;
    }

    @Override
    public int getPlayerCount() {
        if (state == NOT_STARTED) {
            throw new IllegalArgumentException("L'état du jeu est à NOT_STARTED");
        }
        return playerCount;
    }

    @Override
    public int getCurrentPlayerNumber() {
        if (state == NOT_STARTED || state == GAME_OVER) {
            throw new IllegalArgumentException("L'état du jeu est à NOT_STARTED ou GAME_OVER");
        }
        return currentPlayerNumber;
    }

    @Override
    public Tile getPickedTile() {
        if (state != PLACE_TILE && state != PLACE_OR_DROP_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à PLACE_TILE");
        }
        return pickedTile;
    }

    @Override

    public boolean isInside(Position pos
    ) {
        return boards[currentPlayerNumber].isInside(pos);
    }

    @Override
    public boolean canTileBePut(Position pos) {
        if (!boards[currentPlayerNumber].isInside(pos) || !boards[currentPlayerNumber].canBePut(pickedTile, pos)) {
            throw new IllegalArgumentException("Impossible de placer une tuile à la position indiquée");
        }
        if (state != PLACE_TILE && state != PLACE_OR_DROP_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à PLACE_TILE or PLACE_OR_DROP_TILE");
        }
        return boards[currentPlayerNumber].canBePut(pickedTile, pos);
    }

    @Override
    public Tile getTile(int playerNumber, Position pos) {
        if (!boards[currentPlayerNumber].isInside(pos) && !boards[currentPlayerNumber].canBePut(pickedTile, pos)) {
            throw new IllegalArgumentException("Impossible de placer une tuile à la position indiquée");
        }
        if (state == NOT_STARTED) {
            throw new IllegalStateException("L'état doit être différent de NOT_STARTED");
        }
        return boards[playerNumber].getTile(pos);
    }

    @Override
    public ArrayList<Integer> getWinners() {
        if (state != GAME_OVER) {
            throw new IllegalStateException("L'état du jeu n'est pas à GAME_OVER");
        }

        ArrayList<Integer> tuilesRestantes = new ArrayList<Integer>();
        for (int i = 0; i < playerCount; i++) {
            tuilesRestantes.add(countTiles(i));
        }
        ArrayList<Integer> numWinners = new ArrayList<Integer>();
        int nbrMax = tuilesRestantes.get(0);

        for (int i = 0; i < tuilesRestantes.size(); i++) {
            if (tuilesRestantes.get(i) > nbrMax) {
                nbrMax = tuilesRestantes.get(i);
                numWinners.clear();
                numWinners.add(i);
            } else if (tuilesRestantes.get(i) == nbrMax) {
                numWinners.add(i);
            }
        }
        return numWinners;
    }

    //ctrl r -> renommer tous les appels correspondants
    private int countTiles(int nbrPlayer) {
        int nbrTiles = 0;
        if (faceDownTileCount() == 0) {
            for (int j = 0; j < getBoardSize(); j++) {
                for (int k = 0; k < getBoardSize(); k++) {
                    if (boards[nbrPlayer].getTile(new Position(j, k)) != null) {
                        nbrTiles++;
                    }
                }
            }
        }
        return nbrTiles;
    }

    @Override
    public State getState() {
        return state;
    }

    @Override
    public Tile pickFaceDownTile() {

        this.pickedTile = deck.pickFaceDown();
        state = PLACE_OR_DROP_TILE;

        return pickedTile;
    }

    @Override
    public void pickFaceUpTile(Tile tile) {
        if (state != PICK_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à PICK_TILE");
        }

        state = PLACE_TILE;
        deck.pickFaceUp(tile);
    }

    @Override
    public void dropTile() {
        if (state != PLACE_OR_DROP_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à PLACE_OR_DROP_TILE");
        }

        if (faceDownTileCount() == 0) {
            state = GAME_OVER;
        } else {
            state = TURN_END;
        }

        deck.putBack(pickedTile);
    }

    @Override
    public int faceDownTileCount() {
        if (state == NOT_STARTED) {
            throw new IllegalStateException("L'état du jeu est différent de PICK8_ILE et différent de PLACE_OR_DROP_TILE");
        }
        return deck.faceDownCount();
    }

    @Override
    public int faceUpTileCount() {
        if (state != PICK_TILE && state != PLACE_OR_DROP_TILE) {
            throw new IllegalStateException("L'état du jeu n'est pas à PICK_TILE ni PLACE_OR_DROP_TILE");
        }
        return deck.faceUpCount();
    }

    @Override
    public List<Tile> getAllfaceUpTiles() {
        final List<Tile> allFaceUp = deck.getAllFaceUp();
        return Collections.unmodifiableList(allFaceUp);
    }

    Tile getTile_forTest(int playerNumber, Position pos) {
        return boards[playerNumber].getTile(pos);
    }
}
