package controller;

import command.CommandInterface;
import command.CommandManager;
import command.DeleteCommand;
import javafx.stage.Stage;
import model.Board;
import model.FacadeInterface;
import model.Game;
import model.Point;
import view.View;

public class ControllerFX {
    private final CommandManager command;
    private final FacadeInterface game;

    /**
     * Constructor of ControllerFX which allows to initialize CommandManager but also to launch the start method of the fx view.
     * @param game the current game
     * @param stage the current stage
     */
    public ControllerFX(Game game, Stage stage) {
        this.game = game;
        command = new CommandManager();

        View view = new View(this, game);
        view.start(stage);
    }

    /**
     * Allows to clear the stack containing the history
     * of commands and to launch a method startGame a width, height and difficulty by default.
     */
    public void startGame() {
        command.clear();
        game.startGame(10, 14, 5);
    }

    /**
     * Allows to clear the stack containing the history
     * of commands and to launch a method startGame a width, height and difficulty chosen by the user.
     * @param width The width of the board
     * @param height The height of the board
     * @param difficulty The height of the game
     */
    public void startGame(int width, int height, int difficulty) {
        command.clear();
        game.startGame(width, height, difficulty);
    }

    /**
     * Method that will call the isLost method of the model that will pass the state to LOST.
     */
    public void isLost(){
        game.isLost();
    }

    /**
     * Method to delete the spot in which the tile the user wants to delete is located.
     * @param row the row of the tile chosen by the user.
     * @param column the column of the tile chosen by the user.
     */
    public void askDelete(int row, int column) {
        if (game.isInArray(row, column) && game.isATile(new Point(row, column))  && game.isNotNull()) {
            CommandInterface delete = new DeleteCommand(this.game, row, column);
            command.executeCommand(delete);
        }
    }

    /**
     * Method that will call the selectGroup method of the game,
     * which will return a 2D array of boolean corresponding to the spot
     * in which the tile on which the user is located is located
     * @param row the row of the tile chosen by the user.
     * @param column the column of the tile chosen by the user.
     * @return
     */
    public boolean[][] selectGroup(int row, int column) {
        return game.selectGroup(row, column);
    }

    /**
     * Getter of the board
     * @return the current board
     */
    public Board getBoard() {
        return game.getBoard();
    }

    /**
     * Getter of the score
     * @return the current score
     */
    public int getScore() {
        return game.getScore();
    }

    /**
     * Getter of the maxScore
     * @return the current max score
     */
    public int getMaxScore() {
        return game.getMaxScore();
    }

    /**
     * Getter of remainTiles
     * @return the number of remaining tiles
     */
    public int getRemainTile() {
        return game.getRemainTiles();
    }

    /**
     * Determines if there is a tile in a row and column
     * @param row the row of the tile chosen by the user.
     * @param column the column of the tile chosen by the user.
     * @return
     */
    public boolean isTile(int row, int column){
        return game.isATile(new Point(row, column));
    }

    /**
     * Allows you to cancel a command.
     */
    public void undoCommand() {
        command.undoCommand();
    }

    /**
     * Allows you to replay a command.
     */
    public void redoCommand() {
        command.redoCommand();
    }

    /**
     * Allows to call the start method of the game to pass the state to START.
     */
    public void start() {
        game.start();
    }

    /**
     * Allows you to call the giveUp method of the game to pass the state to LOSE.
     */
    public void giveUp() {
        game.giveUp();
    }
}
