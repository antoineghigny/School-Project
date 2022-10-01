package model;

public class GameState {
    private final Board board;
    private final int score;
    private final int remainingTiles;
    private final int previousScore;
    private final int deleteColumn;

    /**
     *
     * @param board
     * @param score
     * @param remainingTiles
     * @param previousScore
     * @param deleteColumn
     */
    public GameState(Board board, int score, int remainingTiles, int previousScore, int deleteColumn) {
        this.board = new Board(board);
        this.score = score;
        this.remainingTiles = remainingTiles;
        this.previousScore = previousScore;
        this.deleteColumn = deleteColumn;
    }

    /**
     * Getter of the board
     * @return the current Board
     */
    public Board getBoard() {
        return board;
    }
    /**
     * Getter of the score
     * @return the current score
     */
    public int getScore() {
        return score;
    }
    /**
     * Getter of the remaining tiles
     * @return the current remaining tiles
     */
    public int getRemainingTiles() {
        return remainingTiles;
    }
    /**
     * Getter of the previousScore
     * @return the current previousScore
     */
    public int getPreviousScore() {
        return previousScore;
    }
    /**
     * Getter of the deleteColumn
     * @return the current deleteColumn
     */
    public int getDeleteColumn() {
        return deleteColumn;
    }
}
