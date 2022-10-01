package model;

import observer.Observable;
import observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Game implements FacadeInterface, Observable {
    private static final Scanner keyboard = new Scanner(System.in);
    private final List<Observer> observers;
    private State state;
    private Board board;

    public boolean[][] verification;
    private int deleted;
    private int score;
    private int maxScore;
    private int remainTiles;
    private int deletedColumn = 0;
    private int previous;

    /**
     * The constructor of Game
     */
    public Game() {
        this.observers = new ArrayList<>();
    }

    /**
     * The Game constructor overloard which takes a Board
     * as parameter (used for junit tests)
     *
     * @param board the given board
     */
    Game(Board board) {
        this();
        this.board = board;
    }

    /**
     * Constructor overload useful for testing
     * @param board the given board
     * @param verification 2D array of boolean
     */
    Game(Board board, boolean[][] verification) {
        this();
        this.board = board;
        this.verification = verification;
    }

    /**
     * The getter of the score
     * @return the current score
     */
    public int getScore() {
        return score;
    }

    /**
     * The getter of the max score
     * @return the current max score
     */
    public int getMaxScore() {
        return maxScore;
    }

    @Override
    public void play(int x, int y) {
        this.verification = new boolean[board.getHeight()][board.getWidth()];
        selectGroup(x, y);
        deleteGroup(this.verification);
        refreshPosition();
            moveLeft();

        updateScore();
        updateRemainTiles();
        printBoard();
        isWin();
    }

    @Override
    public boolean[][] selectGroup(int x, int y) {
        if(isInArray(x, y)){
            this.verification = new boolean[board.getHeight()][board.getWidth()];
            colorGroup(new Point(x, y), board.getTileAt(new Point(x, y)).getColor(), this.verification);
        }
        return verification;
    }

    @Override
    public void startGame(int height, int width, int difficulty) {
        this.score = 0;
        this.deleted = 0;
        this.deletedColumn = 0;
        this.remainTiles = height * width;
        this.board = new Board(height, width);
        this.verification = new boolean[board.getHeight()][board.getWidth()];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {

                int randomColor = new Random().nextInt(Color.values().length - (Color.values().length - difficulty));
                board.put(new Tile(Color.values()[randomColor]), new Point(i, j));
            }
        }
        printBoard();
        state = State.PLAY;
        notifyObservers();
    }

    /**
     * Method for selecting a spot
     * This is a recursive method that first selects the 4 neighbours
     * and then compares each neighbour 1 by 1 to determine if it is in the array,
     * if they have the same colour and if it has not already been checked,
     * if so, we pass this neighbour to true in the boolean array and then recursively
     * rerun the method on this same neighbour to select the whole task.
     * @param currentPosition the currentPosition
     * @param color the color to compare
     * @param verification 2D array of boolean
     */
    public void colorGroup(Point currentPosition, Color color, boolean[][] verification) {
        List<Point> neighbors;
        neighbors = List.of(
                new Point(currentPosition.getX() + 1, currentPosition.getY()),
                new Point(currentPosition.getX() - 1, currentPosition.getY()),
                new Point(currentPosition.getX(), currentPosition.getY() + 1),
                new Point(currentPosition.getX(), currentPosition.getY() - 1)
        );
        for (var neighbor : neighbors) {
            if (isPosAdj(neighbor, color, verification)) {
                verification[neighbor.getX()][neighbor.getY()] = true;
                colorGroup(neighbor, color, verification);
            }
            this.verification = verification;
        }
    }

    /**
     * Method that returns true if the number of selected tiles
     * is greater than 1 (so as not to illuminate when the user
     * is on a tile that does not have a spot.
     * @return true if number is greater than 0,
     * false otherwise
     */
    public boolean isNotNull() {
        int number = 0;
        for (boolean[] booleans : verification) {
            for (int j = 0; j < verification[0].length; j++) {
                if (booleans[j]) {
                    number++;
                }
            }
        }
        return number > 0;
    }

    /**
     * Method that determines whether the row and column are in the table.
     * @param row the actual row
     * @param column the actual column
     * @return true if the row and column is located in the table.
     * False otherwise
     */
    public boolean isInArray(int row, int column) {
        return row >= 0 && row < board.getHeight() && column >= 0 && column < board.getWidth();
    }

    /**
     * Determines if a tile is in the array,
     * if this tile has a certain colour
     * and if it has not already been set to true in the boolean array
     * @param currentPosition the current position
     * @param color the color to compare
     * @param verification 2D array of boolean
     * @return true if the tile respect all conditions
     */
    public boolean isPosAdj(Point currentPosition, Color color, boolean[][] verification) {
        int row = currentPosition.getX();
        int column = currentPosition.getY();
        return (isInArray(row, column) && isSameColor(row, column, color) && isNotVerify(row, column, verification));
    }

    /**
     * Method that checks if a tile has not already been checked.
     * @param row the current row
     * @param column the current column
     * @param verification 2D array of boolean
     * @return true if there is false at the row column position
     * of the verification table.
     */
    public boolean isNotVerify(int row, int column, boolean[][] verification) {
        return (!verification[row][column]);
    }

    /**
     * A method of determining whether the colour
     * of the tile matches the colour to be compared.
     * @param row the current row
     * @param column the current column
     * @param color the color to compare
     * @return false if the tile is null but also
     * if the colour of the tile is not the same as
     * the colour to be compared. True otherwise.
     */
    public boolean isSameColor(int row, int column, Color color) {
        if (board.getTileAt(new Point(row, column)) == null) {
            return false;
        } else {
            return (board.getTileAt(new Point(row, column)).getColor() == color);
        }
    }

    /**
     * Method that removes tiles from places in the boolean array where it is true.
     * @param verification 2D array of boolean
     */
    public void deleteGroup(boolean[][] verification) {
        this.deleted = 0;
        for (int row = 0; row < verification.length; row++) {
            for (int column = 0; column < verification[0].length; column++) {
                if (verification[row][column]) {
                    board.delete(new Point(row, column));
                    deleted++;
                }
            }
        }
    }

    /**
     * Method that refreshes the position downwards
     * when there are no more tiles present below
     * Counts the number of void tiles per column,
     * and when it finds a tile, moves it down by adding the counter.
     */
    public void refreshPosition() {
        for (int column = 0; column < board.getWidth(); column++) {
            int counter = 0;
            for (int row = board.getHeight() - 1; row >= 0; row--) {
                if (board.getTileAt(new Point(row, column)) == null) {
                    counter++;
                } else if (board.isTile(new Point(row, column)) && counter >= 1) {
                    board.moveTile(new Point(row, column), new Point(row + counter, column));
                }
            }
        }
    }

    @Override
    public void printBoard() {
        state = State.PRINT;
        notifyObservers();
    }

    /**
     * A method that determines the state of the game at the end of each move.
     * The state of the game changes to WON if there are no more tiles in the bottom left corner,
     * LOST if the user is blocked and play if none of these are present.
     */
    public void isWin() {
        if (!board.isTile(new Point(board.getHeight() - 1, 0))) {
            state = State.WON;
        } else if (isBlocked()) {
            state = State.LOST;
        } else {
            state = State.PLAY;
        }
        notifyObservers();
    }

    @Override
    public boolean isBlocked() {
        for (int column = 0; column < board.getWidth(); column++) {
            for (int row = board.getHeight() - 1; row >= 0; row--) {
                if (isNoSameColor(new Point(row, column))) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Determines if there are no neighbours of the same
     * colour at the top and bottom
     * @param currentPosition the current position
     * @return true if all the neighbours are different colours.
     */
    public boolean isNoSameColor(Point currentPosition) {
        List<Point> neighbors;
        neighbors = List.of(
                new Point(currentPosition.getX() - 1, currentPosition.getY()),
                new Point(currentPosition.getX(), currentPosition.getY() + 1)
        );
        for (var neighbor : neighbors) {
            if (allVerification(neighbor.getX(), neighbor.getY()) && allVerification(currentPosition.getX(), currentPosition.getY())) {
                if (!isDifferentColor(neighbor, board.getTileAt(new Point(currentPosition.getX(), currentPosition.getY())).getColor())) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Returns true if a tile is in the same colour
     * and meets all the checks (in the table...)
     * @param newPosition the current position
     * @param color the color to compare
     * @return true if a tile is in the same colour
     * and meets all the checks (in the table...)
     */
    public boolean isDifferentColor(Point newPosition, Color color) {
        int row = newPosition.getX();
        int column = newPosition.getY();
        return (allVerification(row, column) && notSameColor(newPosition, color));
    }

    /**
     * returns false if the colour of the tile is
     * the same as the colour to be compared but also if this tile is void. True in all other cases.
     * @param newPosition the position
     * @param color the color to compare
     * @return false if the colour of the tile is the same
     * as the colour to be compared but also if this tile is void. True in all other cases.
     */
    public boolean notSameColor(Point newPosition, Color color) {
        if (board.getTileAt(new Point(newPosition.getX(), newPosition.getY())) == null) {
            return false;
        } else {
            return (board.getTileAt(newPosition).getColor() != color);
        }
    }

    @Override
    public void updateScore() {
        score += deleted * (deleted - 1);
        if (maxScore < score) {
            maxScore = score;
        }
    }

    /**
     * Method that updates the remaining tiles
     */
    public void updateRemainTiles(){
        remainTiles -= deleted;
    }

    @Override
    public void registerObserver(Observer obs) {
        if (!observers.contains(obs)) {
            observers.add(obs);
        }
    }

    @Override
    public void removeObserver(Observer obs) {
        observers.remove(obs);
    }

    @Override
    public void notifyObservers() {
        for (Observer obs : observers) {
            obs.update(state);
        }
    }

    /**
     * Calls the board method that indicates whether
     * there is a tile at a specified position
     * @param point the point to observe
     * @return true if there is a tile at a point
     */
    public boolean isATile(Point point) {
        return board.isTile(point);
    }

    /**
     * Method that checks if a certain row and column
     * are located in the table and that there is a tile.
     * @param row the current row
     * @param column the current column
     * @return true if the row and column are included
     * in the table and if there is a tile at the position
     */
    public boolean allVerification(int row, int column){
        return isInArray(row, column) && isATile(new Point(row, column))  && isNotNull();
    }

    /**
     * Method that returns true if there is a null tile in the bottom row
     * @return Method that returns true if there is a null tile in the bottom row
     */
    public boolean noNullColumn() {
        for (int column = 0; column < board.getWidth() - deletedColumn; column++) {
            if (!board.isTile(new Point(board.getHeight() - 1, column))) {
                deletedColumn++;
                return true;
            }
        }
        return false;
    }

    /**
     * Moves columns to the left when there are empty columns.
     */
    public void moveLeft() {
        while(noNullColumn()) {
            for (int column = 0; column < board.getWidth() - deletedColumn; column++) {
                if (!board.isTile(new Point(board.getHeight() - 1, column))) {
                    for (int columnY = column; columnY < board.getWidth(); columnY++) {
                        for (int rowX = board.getHeight() - 1; rowX >= 0; rowX--) {
                            if (board.isTile(new Point(rowX, columnY))) {
                                board.moveTile(new Point(rowX, columnY), new Point(rowX, columnY - 1));
                            }

                        }
                    }

                }
            }
        }
    }


    /**
     * When this method is called,
     * it retrieves the previous elements present in the constructor by copy.
     * @param game The previous GameState that saved the different elements.
     */
    public void setState(GameState game) {
        this.board = game.getBoard();
        this.score = game.getScore();
        this.previous = game.getPreviousScore();
        this.remainTiles = game.getRemainingTiles();
        this.deletedColumn = game.getDeleteColumn();
        printBoard();
        play();
    }

    /**
     * Method that asks the user to enter a command,
     * it must respect all the constraints of the patter.
     * @return a string table
     */
    public String[] askTask() {
        String symbol = "(([0-9A-Za-z]|[?./+&'(§è!çà)]/*){1})";
        String twoParam = "(\\d{1,3}\\s)?" + symbol;
        String pattern = "(delete " + twoParam + "\\s*)"
                + "|(undo\\s*)"
                + "|(redo\\s*)"
                + "|(stop\\s*)";

        keyboard.useDelimiter("\n");
        while (!keyboard.hasNext(pattern)) {
            System.err.println("Your command (" + keyboard.next() + ") does not correspond to what is requested, please try again");
        }
        return keyboard.next().split(" ");
    }

    /**
     *  Method that asks the user to enter a command,
     *  it must respect all the constraints of the patter.
     * @return a string table
     */
    public String[] askBoard() {
        String symbol = "(([0-9A-Za-z]|[?./+&'(§è!çà)]/*){1})";
        String pattern = "(\\d{1,3}\\s){2}" + symbol;
        keyboard.useDelimiter("\n");
        while (!keyboard.hasNext(pattern)) {
            System.err.println("Your command (" + keyboard.next() + ") does not correspond to what is requested, please try again");
        }
        return keyboard.next().split(" ");
    }

    public Board getBoard() {
        return board;
    }

    public State getState() {
        return state;
    }

    public int getRemainTiles() {
        return remainTiles;
    }

    public int getPrevious() {
        return previous;
    }

    public int getDeletedColumn() {
        return deletedColumn;
    }

    @Override
    public void play() {
        state = State.PLAY;
        notifyObservers();
    }
    /**
     * When this method is called, the status will change to START and notify all observers.
     */
    public void start() {
        state = State.START;
        notifyObservers();
    }

    @Override
    public void giveUp() {
        state = State.ABANDONED;
        notifyObservers();
    }

    /**
     * When this method is called, the status will change to LOST and notify all observers.
     */
    public void isLost(){
        state = State.LOST;
        notifyObservers();
    }
}
