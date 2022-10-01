package model;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertFalse;

class GameTest {
    private Board board;
    private Game game;
    public boolean[][] verification;

    @Test
    void play() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        boolean[][] verification = game.selectGroup(5, 1);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.moveLeft();
        game.updateScore();
        assertSame(6, game.getScore());
        assertSame(6, game.getMaxScore());
        assertTrue(game.isATile(new Point(5, 0)));
        assertFalse(game.isATile(new Point(5, 3)));
        assertFalse(game.isATile(new Point(5, 2)));
        assertFalse(game.isATile(new Point(5, 1)));
    }

    @Test
    void selectGroup_NormalUtilisation() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();

        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));

        board.put(new Tile(Color.GREEN), new Point(4, 1));
        boolean[][] verification = game.selectGroup(5, 1);
        boolean[][] expectedVerification = new boolean[6][6];
        expectedVerification[5][1] = true;
        expectedVerification[5][2] = true;
        expectedVerification[5][3] = true;
        expectedVerification[4][1] = true;
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_OneTileOnly() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.GREEN), new Point(4, 1));
        boolean[][] verification = game.selectGroup(5, 0);
        boolean[][] expectedVerification = new boolean[6][6];
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_NullAsNeighbors() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(3, 3));
        board.put(null, new Point(3, 4));
        board.put(null, new Point(3, 2));
        board.put(null, new Point(2, 3));
        board.put(null, new Point(4, 3));

        board.put(new Tile(Color.RED), new Point(4, 4));
        board.put(new Tile(Color.RED), new Point(2, 2));
        board.put(new Tile(Color.RED), new Point(4, 2));
        board.put(new Tile(Color.RED), new Point(2, 4));
        board.put(new Tile(Color.RED), new Point(3, 5));
        board.put(new Tile(Color.RED), new Point(3, 1));
        board.put(new Tile(Color.RED), new Point(1, 3));
        board.put(new Tile(Color.RED), new Point(5, 3));

        boolean[][] verification = game.selectGroup(3, 3);
        boolean[][] expectedVerification = new boolean[6][6];
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_TilesOnTheEdge() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.RED), new Point(0, 1));
        board.put(new Tile(Color.RED), new Point(0, 2));

        board.put(new Tile(Color.RED), new Point(1, 2));
        board.put(new Tile(Color.RED), new Point(2, 2));

        board.put(new Tile(Color.RED), new Point(2, 1));
        board.put(new Tile(Color.RED), new Point(2, 0));

        board.put(new Tile(Color.RED), new Point(1, 0));

        boolean[][] verification = game.selectGroup(0, 0);
        boolean[][] expectedVerification = new boolean[][]{
                {true, true, true},
                {true, false, true},
                {true, true, true},
        };
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_Diagonal() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.RED), new Point(0, 2));
        board.put(new Tile(Color.RED), new Point(1, 1));
        board.put(new Tile(Color.RED), new Point(2, 0));
        board.put(new Tile(Color.RED), new Point(2, 2));

        boolean[][] verification = game.selectGroup(0, 0);
        boolean[][] expectedVerification = new boolean[][]{
                {false, false, false},
                {false, false, false},
                {false, false, false},
        };
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_selectRandomForm() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.RED), new Point(0, 1));
        board.put(new Tile(Color.RED), new Point(0, 2));

        board.put(new Tile(Color.RED), new Point(1, 2));
        board.put(new Tile(Color.RED), new Point(2, 2));

        board.put(new Tile(Color.RED), new Point(1, 1));

        boolean[][] verification = game.selectGroup(0, 0);
        boolean[][] expectedVerification = new boolean[][]{
                {true, true, true},
                {false, true, true},
                {false, false, true},
        };
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void selectGroup_randomOtherForm() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.RED), new Point(0, 1));
        board.put(new Tile(Color.RED), new Point(0, 2));

        board.put(new Tile(Color.RED), new Point(2, 2));

        board.put(new Tile(Color.RED), new Point(2, 1));
        board.put(new Tile(Color.RED), new Point(2, 0));
        board.put(new Tile(Color.GREEN), new Point(1, 1));
        board.put(new Tile(Color.YELLOW), new Point(1, 2));

        board.put(new Tile(Color.RED), new Point(1, 0));

        boolean[][] verification = game.selectGroup(0, 2);
        boolean[][] expectedVerification = new boolean[][]{
                {true, true, true},
                {true, false, false},
                {true, true, true},
        };
        // no tiles selected
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void startGame() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        game.startGame(2, 2, 2);
        assertTrue(game.isATile(new Point(0, 0)));
        assertTrue(game.isATile(new Point(1, 0)));
        assertTrue(game.isATile(new Point(0, 1)));
        assertTrue(game.isATile(new Point(1, 1)));
    }

    @Test
    void isNotNull_OneTile_False() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.RED), new Point(4, 0));
        boolean valid = game.isNotNull();
        assertFalse(valid);
    }

    @Test
    void isNotNull_NormalUtilisation_True() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.GREEN), new Point(4, 1));
        game.selectGroup(5, 1);
        boolean valid = game.isNotNull();
        assertTrue(valid);
    }

    @Test
    void isInArray_TileOutOfBound() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        boolean verif = game.isInArray(6, 0);
        assertFalse(verif);
    }

    @Test
    void isInArray_TileInBound() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        boolean verif = game.isInArray(4, 0);
        assertTrue(verif);
    }

    @Test
    void isPosAdj_SameColor() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.RED), new Point(5, 1));
        boolean verif = game.isPosAdj(new Point(5, 1), Color.RED, verification);
        assertTrue(verif);
    }

    @Test
    void isPosAdj_NotSameColor() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.BLUE), new Point(5, 1));
        boolean verif = game.isPosAdj(new Point(5, 1), Color.RED, verification);
        assertFalse(verif);
    }

    @Test
    void isPosAdj_NotSameColoBecauseNull() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(null, new Point(5, 1));
        boolean verif = game.isPosAdj(new Point(5, 1), Color.RED, verification);
        assertFalse(verif);
    }

    @Test
    void isPosAdj_AlwaysVerify() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.RED), new Point(5, 1));
        board.put(new Tile(Color.RED), new Point(4, 2));
        board.put(new Tile(Color.RED), new Point(4, 3));
        verification[5][0]= true;
        verification[5][1]= true;
        verification[5][2]= true;
        boolean verif = game.isPosAdj(new Point(5, 2), Color.RED, verification);
        assertFalse(verif);
    }

    @Test
    void isSameColor_SameColor() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        boolean verif = game.isSameColor(5, 0, Color.RED);
        assertTrue(verif);
    }

    @Test
    void isSameColor_NotSameColor() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        boolean verif = game.isSameColor(5, 0, Color.GREEN);
        assertFalse(verif);
    }

    @Test
    void deleteGroup() {
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.RED), new Point(0, 1));
        board.put(new Tile(Color.RED), new Point(0, 2));

        board.put(new Tile(Color.RED), new Point(2, 2));

        board.put(new Tile(Color.RED), new Point(2, 1));
        board.put(new Tile(Color.RED), new Point(2, 0));
        board.put(new Tile(Color.GREEN), new Point(1, 1));
        board.put(new Tile(Color.YELLOW), new Point(1, 2));

        board.put(new Tile(Color.RED), new Point(1, 0));

        boolean[][] verification = game.selectGroup(0, 2);
        game.deleteGroup(verification);
        for(int i = 0; i < board.getWidth(); i++){
            for(int j = 0; j < board.getHeight(); j++){
            }
        }
        boolean[][] expectedVerification = new boolean[][]{
                {true, true, true},
                {true, false, false},
                {true, true, true},
        };
        assertArrayEquals(expectedVerification, verification);
    }

    @Test
    void deleteGroup_NormalUtilisation() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.RED), new Point(4, 3));
        board.put(new Tile(Color.GREEN), new Point(4, 1));
        verification = game.selectGroup(5, 2);
        game.deleteGroup(verification);
        boolean[][] isTile = new boolean[boardGame.getHeight()][boardGame.getWidth()];
        for(int i = 0; i < boardGame.getHeight(); i++){
            for(int j = 0; j < boardGame.getWidth(); j++){
                if(game.isATile(new Point(i, j))){
                    isTile[i][j] = true;
                }
            }
        }
        boolean[][] expectedTile = new boolean[boardGame.getHeight()][boardGame.getWidth()];
        expectedTile[5][0] = true;
        expectedTile[4][3] = true;
        assertArrayEquals(expectedTile,isTile);
    }

    @Test
    void refreshPosition_NormalUtilisation() {
        Board boardGame = new Board(6, 10);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.RED), new Point(4, 3));
        board.put(new Tile(Color.GREEN), new Point(4, 1));

        boolean[][] verification = game.selectGroup(5, 2);
        game.deleteGroup(verification);
        game.refreshPosition();

        boolean[][] isTile = new boolean[boardGame.getHeight()][boardGame.getWidth()];
        for(int i = 0; i < boardGame.getHeight(); i++){
            for(int j = 0; j < boardGame.getWidth(); j++){
                if(game.isATile(new Point(i, j))){
                    isTile[i][j] = true;
                }
            }
        }
        boolean[][] expectedTile = new boolean[boardGame.getHeight()][boardGame.getWidth()];
        expectedTile[5][0] = true;
        expectedTile[5][3] = true;
        assertArrayEquals(expectedTile, isTile);
    }

    @Test
    void isWin_LOST() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        game.isWin();
        assertSame(game.getState(), State.LOST);
    }

    @Test
    void isWin_WIN(){
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        game.isWin();
        assertSame(State.WON, game.getState());
    }

    @Test
    void isWin_PLAY(){
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.RED), new Point(4, 0));
        board.put(new Tile(Color.RED), new Point(5, 1));
        board.put(new Tile(Color.YELLOW), new Point(5, 2));
        game.selectGroup(5, 0);
        game.isWin();
        assertSame(State.PLAY, game.getState());
    }

    @Test
    void isBlocked_GameOver() {
        Board boardGame = new Board(6, 6);
        this.game = new Game(boardGame);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        assertTrue(game.isBlocked());
    }

    @Test
    void isBlocked_NotGameOver() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);;
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.RED), new Point(4, 0));
        board.put(new Tile(Color.RED), new Point(5, 1));
        board.put(new Tile(Color.YELLOW), new Point(5, 2));
        game.selectGroup(5, 0);
        assertFalse(game.isBlocked());
    }

    @Test
    void updateScore_NormalUtilisation() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(5, 0));
        board.put(new Tile(Color.GREEN), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.GREEN), new Point(5, 4));
        board.put(new Tile(Color.GREEN), new Point(4, 3));
        board.put(new Tile(Color.GREEN), new Point(3, 3));
        board.put(new Tile(Color.GREEN), new Point(3, 2));
        board.put(new Tile(Color.GREEN), new Point(3, 4));
        verification = game.selectGroup(5, 1);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.updateScore();
        // 9 delete
        int expectedScore = 56;
        assertSame(expectedScore, game.getScore());
    }

    @Test
    void updateScore_NoTileDeleted() {
        Board boardGame = new Board(6, 6);
        boolean[][]verification = new boolean[6][6];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.BLUE), new Point(5, 1));
        board.put(new Tile(Color.GREEN), new Point(5, 2));
        board.put(new Tile(Color.GREEN), new Point(5, 3));
        board.put(new Tile(Color.GREEN), new Point(5, 4));
        board.put(new Tile(Color.GREEN), new Point(4, 3));
        board.put(new Tile(Color.GREEN), new Point(3, 3));
        board.put(new Tile(Color.GREEN), new Point(3, 2));
        board.put(new Tile(Color.GREEN), new Point(3, 4));
        verification = game.selectGroup(5, 1);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.updateScore();
        // 9 delete
        int expectedScore = 0;
        assertSame(expectedScore, game.getScore());
    }

    @Test
    void updateScore_AllTileDeleted() {
        Board boardGame = new Board(2, 2);
        boolean[][]verification = new boolean[2][2];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.GREEN), new Point(0, 0));
        board.put(new Tile(Color.GREEN), new Point(0, 1));
        board.put(new Tile(Color.GREEN), new Point(1, 0));
        board.put(new Tile(Color.GREEN), new Point(1, 1));
        verification = game.selectGroup(1, 1);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.updateScore();
        // 9 delete
        int expectedScore = 12;
        assertSame(expectedScore, game.getScore());
    }

    @Test
    void updateScore_MultipleDelete() {
        Board boardGame = new Board(2, 2);
        boolean[][]verification = new boolean[2][2];
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.GREEN), new Point(0, 0));
        board.put(new Tile(Color.GREEN), new Point(0, 1));
        board.put(new Tile(Color.BLUE), new Point(1, 0));
        board.put(new Tile(Color.BLUE), new Point(1, 1));
        verification = game.selectGroup(0, 0);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.moveLeft();
        game.updateScore();
        verification = game.selectGroup(1, 1);
        game.deleteGroup(verification);
        game.refreshPosition();
        game.moveLeft();

        game.updateScore();
        // 9 delete
        int expectedScore = 4;
        assertSame(expectedScore, game.getScore());
    }

    @Test
    void moveLeft_true(){
        Board boardGame = new Board(2, 2);
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(1, 1));
        game.refreshPosition();
        game.moveLeft();
        assertTrue(game.isATile(new Point(1, 0)));
    }

    @Test
    void moveLeft(){
        Board boardGame = new Board(2, 2);
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(1, 1));
        game.refreshPosition();
        game.moveLeft();
        assertFalse(game.isATile(new Point(1, 1)));
    }
    @Test
    void moveLeft_otherExample(){
        Board boardGame = new Board(3, 3);
        this.game = new Game(boardGame, verification);
        this.board = game.getBoard();
        board.put(new Tile(Color.RED), new Point(0, 0));
        board.put(new Tile(Color.BLUE), new Point(0, 1));
        board.put(new Tile(Color.YELLOW), new Point(1, 2));
        board.put(new Tile(Color.PURPLE), new Point(1, 1));
        game.refreshPosition();
        game.moveLeft();
        assertSame(Color.RED, board.getTileAt(new Point(2, 0)).getColor());
        assertSame(Color.PURPLE, board.getTileAt(new Point(2, 1)).getColor());
        assertSame(Color.BLUE, board.getTileAt(new Point(1, 1)).getColor());
        assertSame(Color.YELLOW, board.getTileAt(new Point(2, 2)).getColor());
    }

}
