/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author antoi
 */
public interface FacadeInterface {

    /**
     * Method to start a game by giving the height and width
     * of the board and the difficulty (number of colours)
     * @param width
     * @param height The height of the board
     * @param difficulty
     */
    void startGame(int width, int height, int difficulty);

    /**
     * Method that passes the state to print and notifies observers.
     */
    void printBoard();

    /**
     * Method that allows to play a move
     * from the x and y position and the tile to be deleted
     * @param x the row of the tile to be removed
     * @param y the column of the tile to be removed
     */
    void play(int x, int y);

    /**
     * Recursively selects the spot in which the tile to be deleted is located.
     * @param x the row of the tile to be removed
     * @param y the column of the tile to be removed
     * @return a 2D array of boolean
     */
    boolean[][]  selectGroup(int x, int y);

    /**
     * Determines whether the state of the part is WIN, PLAY or LOST
     */
    void isWin();

    /**
     * Method that determines if the game is blocked.
     * @return true if there is no way to play.
     */
    boolean isBlocked();

    /**
     * Method for updating the score
     */
    void updateScore(); // observer observable

    /**
     * Méthode qui permet d'actualiser le score.
     */
    void play();

    /**
     * Allows the game state to be changed to LOST if the user makes a mistake.
     */
    void giveUp();

    /**
     * Method that determines if the user can no longer play a song
     */
    void isLost();

    /**
     * Method that determines whether the row and column of the tile are in the same row and column.
     * @param row the row of a tile
     * @param column the column of a tile
     * @return true if the row and column are in the table
     */
    boolean isInArray(int row, int column);

    /**
     * Method that determines if there is a tile at the indicated point.
     * @param point true if there is a tile at the indicated point.
     * @return true if the row and column are in the table
     */
    boolean isATile(Point point);

    /**
     * Check that a tile is located in a spot.
     * @return true if the tile is well situated in a spot.
     */
    boolean isNotNull();

    /**
     * getter of Board
     * @return the current Board
     */
    Board getBoard();

    /**
     * Getter of score
     * @return the current Score
     */
    int getScore();

    /**
     * Getter of maxScore
     * @return the current maxScore
     */
    int getMaxScore();

    /**
     * getter of remainTiles
     * @return the current number of tiles
     */
    int getRemainTiles();

    /**
     * to switch the state to START
     */
    void start();

    /**
     * Getter of the precedent score
     * @return the precedent score
     */
    int getPrevious();

    /**
     * Change the state of the game
     * @param state the state to change
     */
    void setState(GameState state);

    /**
     * Method that verifies the data entered by the user.
     * @return an array of strings
     */
    String[] askTask();

    /**
     * Method that verifies the data entered by the user.
     * @return an array of Board.
     */
    String[] askBoard();
    /*
    * Method that returns the number of delete columns
    * (each time you moveLeft)
     */
    int getDeletedColumn();
}
