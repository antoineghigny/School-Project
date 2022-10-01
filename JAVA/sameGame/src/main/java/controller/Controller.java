package controller;

import command.CommandInterface;
import command.CommandManager;
import command.DeleteCommand;
import console.ConsoleView;
import model.Board;
import model.FacadeInterface;
import model.Game;

public class Controller {
    private final CommandManager command;
    private final FacadeInterface game;

    /**
     * Controller constructor
     * @param game the current game
     */
    public Controller(Game game) {
        this.game = game;
        ConsoleView view = new ConsoleView(this, game);
        command = new CommandManager();
        game.start();
    }

    /**
     * Method that allows to launch a method with a height, width and difficulty.
     * @param width the width of the board.
     * @param height the height of the board.
     * @param difficulty the difficulty of the game.
     */
    public void startGame(int width, int height, int difficulty) {
        command.clear();
        if (difficulty <= 5 && difficulty >= 3) { //
            game.startGame(width, height, difficulty);
        } else{
            System.out.println("The difficulty must be between 3 and 5");
            game.start();
        }
    }

    /**
     * Getter of the array of string
     * @return un array of string
     */
    public String[] askTask() {
        return game.askTask();
    }

    /**
     * allows to ask the user for a command, he can delete a tile, undo or redo or abandon.
     */
    public void askDelete() {
        String[] deleteUser = askTask();

        switch (deleteUser[0]) {
            case "delete":
                int row = Integer.parseInt(deleteUser[1]) - 1;
                int column = Integer.parseInt(deleteUser[2]) - 1;
                CommandInterface delete = new DeleteCommand(this.game, row, column);
                command.executeCommand(delete);
                game.printBoard();
                game.play();
                break;
            case "undo":
                command.undoCommand();
                game.printBoard();
                game.play();
                break;
            case "redo":
                command.redoCommand();
                game.printBoard();
                game.play();
                break;
            case "stop":
                game.giveUp();
                break;
        }
    }

    /**
     * Getter of score
     * @return the current score
     */
    public int getScore() {
        return game.getScore();
    }

    /**
     * Getter of the current board
     * @return the current board
     */
    public Board getBoard(){
        return game.getBoard();
    }

    /**
     * Getter of remain tiles
     * @return the number of remaining tiles
     */
    public int getRemainTile() {
        return game.getRemainTiles();
    }

    /**
     * Allows you to call the giveUp method of the game to pass the state to LOSE.
     */
    public void giveUp(){
        game.giveUp();
    }

    /**
     * Allows to check that what the user has entered corresponds to a certain pattern.
     * @return an array of string
     */
    public String[] askBoard() {
        return game.askBoard();
    }
}
