package g56359.luckynumbers.model;

import static g56359.luckynumbers.model.State.PICK_TILE;
import java.util.List;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;

/**
 *
 * @author MCD <mcodutti@he2b.be>
 */
public class GameTest {

    private Tile pickedTile;

    private Game game;

    @BeforeEach
    public void setUp() {
        game = new Game();
    }

    /* =====================
         Tests for start()
       ===================== */

 /* --- test related to the state --- */
    @Test
    public void start_when_game_not_started_ok() {
        game.start(4);
    }

    @Test
    public void start_when_game_over_ok() {
        fullPlay();
        game.start(2);
    }

    /* Play a game till the end */
    private void fullPlay() {
        game.start(2);
        int value = 1;
        int line = 0;
        int col = 0;
        for (int turn = 1; turn < game.getBoardSize() * game.getBoardSize(); turn++) {
            for (int player = 0; player < game.getPlayerCount(); player++) {
                game.pickFaceDownTile();
                game.putTile(new Position(line, col));
                game.nextPlayer();
            }
            value++;
            col++;
            if (col == game.getBoardSize()) {
                col = 0;
                line++;
            }
        }
        game.pickFaceDownTile();
        game.putTile(new Position(line, col));
    }

    @Test
    public void start_when_game_in_progress_ISE() {
        game.start(4);
        assertThrows(IllegalStateException.class,
                () -> game.start(1));
    }

    @Test
    public void start_state_changed_to_PICK_TILE() {
        game.start(3);
        assertEquals(State.PICK_TILE, game.getState());
    }

    /* --- tests related to the parameter --- */
    @Test
    public void start_playerCount_too_small_Exception() {
        assertThrows(IllegalArgumentException.class,
                () -> game.start(1));
    }

    @Test
    public void start_playerCount_minimum_accepted() {
        game.start(2);
    }

    @Test
    public void start_playerCount_maximum_accepted() {
        game.start(4);
    }

    @Test
    public void start_playerCount_too_big_Exception() {
        assertThrows(IllegalArgumentException.class,
                () -> game.start(5));
    }

    /* -- tests related to fields initialization --- */
    @Test
    public void start_playerCount_initialized() {
        game.start(4);
        assertEquals(4, game.getPlayerCount());
    }

    @Test
    public void start_current_player_is_player_0() {
        game.start(4);
        assertEquals(0, game.getCurrentPlayerNumber());
    }

    /* === Ã€ vous de complÃ©ter... === */
    @Test
    public void putTile_normal_position() {
        game.start(2);
        int value = 1;
        int line = 3;
        int col = 3;
        game.pickFaceDownTile();
        game.putTile(new Position(line, col));
        assertEquals(0, game.getCurrentPlayerNumber());
    }

    @Test
    public void putTile_pos_is_not_inside_exception() {
        assertThrows(IllegalArgumentException.class, () -> {
            game.start(2);
            int value = 1;
            int line = 3;
            int col = 5;
            game.pickFaceDownTile();
            game.putTile(new Position(line, col));
        });
    }

    @Test
    public void putTile_pos_is_inside_not_be_put() {
        assertThrows(IllegalArgumentException.class, () -> {
            game.start(2);
            int value = 23;
            int line = 3;
            int col = 4;
            game.pickFaceDownTile();
            game.putTile(new Position(line, col));
        });
    }

    @Test
    public void putTile_sur_les_bords() {
        game.start(2);
        int value = 19;
        int line = 3;
        int col = 3;
        game.pickFaceDownTile();
        game.putTile(new Position(line, col));
    }

    @Test
    public void putTile_0() {
        game.start(2);
        int value = 19;
        int line = 0;
        int col = 0;
        game.pickFaceDownTile();
        game.putTile(new Position(line, col));
    }

    @Test
    public void nextPlayer_normal() {
        game.start(2);
        int value = 19;
        int line = 3;
        int col = 3;
        int currentPlayerNumber = 0;
        int playerCount = 3;
        game.pickFaceDownTile();
        game.putTile(new Position(line, col));
        game.nextPlayer();
    }

    @Test
    public void nextPlayer_state_exception() {
        assertThrows(IllegalStateException.class, () -> {

            game.start(2);
            int value = 19;
            game.pickFaceDownTile();
            game.nextPlayer();
        });
    }

    @Test
    public void isInside_normal() {
        game.start(2);
        int line = 3;
        int col = 3;
        game.isInside(new Position(line, col));
    }

    @Test
    public void is_not_Inside_normal() {

        game.start(2);
        int line = 3;
        int col = 3;
        game.isInside(new Position(line, col));

    }

    @Test
    public void canTileBePut_normal() {
        game.start(2);
        int value = 19;
        int line = 3;
        int col = 3;
        game.pickFaceDownTile();
        game.canTileBePut(new Position(line, col));
    }

    @Test
    public void testStart_normal_2_players() {
        System.out.println("start 2 players");
        int playerCount = 2;
        Game instance = new Game();
        instance.start(playerCount);
    }

    @Test
    public void testStart_0_players() {
        assertThrows(IllegalArgumentException.class, () -> {

            System.out.println("start 0 players");
            int playerCount = 0;
            Game instance = new Game();
            instance.start(playerCount);
        });

    }

    @Test
    public void testStart_5_players() {
        assertThrows(IllegalArgumentException.class, () -> {

            System.out.println("start 5 players");
            int playerCount = 5;
            Game instance = new Game();
            instance.start(playerCount);
        });

    }

    /**
     * Test of getBoardSize method, of class Game.
     */
    @Test
    public void testGetBoardSize() {
        System.out.println("getBoardSize_normal");
        Game instance = new Game();
        instance.start(2);

        int expResult = 4;
        int result = instance.getBoardSize();
        assertEquals(expResult, result);
    }

    /**
     * Test of putTile method, of class Game.
     */
    @Test
    public void testPutTile() {
        System.out.println("putTile");
        Game game = new Game();
        game.start(2);
        Position pos = new Position(2, 1);

        game.pickFaceDownTile();

        game.putTile(pos);
        Tile tileGet = game.getTile(0, pos);

        assertEquals(game.getPickedTile(), tileGet);
    }

    /**
     * Test of nextPlayer method, of class Game.
     */
    @Test
    public void testNextPlayer() {
        System.out.println("nextPlayer");
        System.out.println("nextPlayer : ");
        Game instance = new Game();
        Position pos = new Position(2, 1);
        instance.start(2);
        System.out.println("game start");
        instance.pickFaceDownTile();
        System.out.println("pickfacedown");
        instance.putTile(pos);
        System.out.println("puttile");
        System.out.println(instance.getPlayerCount());
        instance.nextPlayer();
        assertEquals(instance.getCurrentPlayerNumber(), 1);
    }

    /**
     * Test of getPlayerCount method, of class Game.
     */
    @Test
    public void testGetPlayerCount() {
        System.out.println("getPlayerCount");
        Game game = new Game();
        game.start(2);
        System.out.println(game.getPlayerCount());

        assertEquals(game.getPlayerCount(), 2);
    }

    /**
     * Test of getCurrentPlayerNumber method, of class Game.
     */
    @Test
    public void testGetCurrentPlayerNumber() {
        System.out.println("getCurrentPlayerNumber");
        Game game = new Game();
        game.start(2);
        assertEquals(game.getCurrentPlayerNumber(), 0);
    }

    /**
     * Test of getPickedTile method, of class Game.
     */
    @Test
    public void testGetPickedTile() {
        System.out.println("getPickedTile");
        Game game = new Game();
        game.start(2);
        game.pickFaceDownTile();
        assertEquals(game.getPickedTile(), game.getPickedTile());
    }

    /**
     * Test of isInside method, of class Game.
     */
    @Test
    public void testIsInside() {
        System.out.println("isInside");
        game.start(2);
        Position pos = new Position(2, 1);
        assertTrue(game.isInside(pos));
    }

    /**
     * Test of canTileBePut method, of class Game.
     */
    @Test
    public void testCanTileBePut() {
        System.out.println("canTileBePut");
        Game game = new Game();
        game.start(2);
        Position pos = new Position(3, 3);
        game.pickFaceDownTile();
        game.canTileBePut(pos);
        assertTrue(game.canTileBePut(pos));
    }

    /**
     * Test of getTile method, of class Game.
     */
    @Test
    public void testGetTile() {
        System.out.println("getTile");
        Game game = new Game();
        game.start(2);
        Position pos = new Position(3, 3);
        game.pickFaceDownTile();
        game.getTile(0, pos);
        assertEquals(game.getTile(0, pos), game.getTile_forTest(0, pos));
    }

    /**
     * Test of getWinner method, of class Game.
     */
    @Test
    public void testGetWinner() {
        System.out.println("getWinner");
        Game instance = new Game();
        int expResult = 0;
        //    int result = instance.getWinners();
        //  assertEquals(expResult, result);
    }

    /**
     * Test of getState method, of class Game.
     */
    @Test
    public void testGetState() {
        System.out.println("getState");
        Game game = new Game();
        game.start(2);
        State result = game.getState();
        assertEquals(result, PICK_TILE);
    }

    /**
     * Test of pickFaceDownTile method, of class Game.
     */
    @Test
    public void testPickFaceDownTile() {
        System.out.println("pickFaceDownTile");
        Game game = new Game();
        game.start(2);
        assertEquals(game.pickFaceDownTile(), game.getPickedTile());
    }

    /**
     * Test of pickFaceUpTile method, of class Game.
     */
    @Test
    public void testPickFaceUpTile() {
        System.out.println("pickFaceUpTile");
        System.out.println("pickFaceUpTile : ");
        Game game = new Game();
        game.start(2);

        game.pickFaceUpTile(new Tile(2));
        System.out.println(game.getPickedTile());
        assertEquals(new Tile(2), game.getPickedTile()); //pas ça à vérifier car passe pas à pickedtile
    }

    /**
     * Test of dropTile method, of class Game.
     */
    @Test
    public void testDropTile() {
        System.out.println("dropTile");
        Game instance = new Game();
        instance.dropTile();
    }

    /**
     * Test of faceDownTileCount method, of class Game.
     */
    @Test
    public void testFaceDownTileCount() {
        System.out.println("faceDownTileCount");
        Game instance = new Game();
        int expResult = 0;
        int result = instance.faceDownTileCount();
        assertEquals(expResult, result);
    }

    /**
     * Test of faceUpTileCount method, of class Game.
     */
    @Test
    public void testFaceUpTileCount() {
        System.out.println("faceUpTileCount");
        Game game = new Game();
        game.start(2);
        game.pickFaceDownTile();
        game.dropTile();
        game.pickFaceDownTile();
        game.dropTile();
        game.pickFaceDownTile();
        game.dropTile();
        int expResult = 3;
        int result = game.faceUpTileCount();
        assertEquals(3, game.faceUpTileCount());
    }

    /**
     * Test of getAllfaceUpTiles method, of class Game.
     */
    @Test
    public void testGetAllfaceUpTiles() {
        System.out.println("getAllfaceUpTiles");
        Game game = new Game();

        List<Tile> expResult = null;
        List<Tile> result = game.getAllfaceUpTiles();
        assertEquals(expResult, result);
    }
}
