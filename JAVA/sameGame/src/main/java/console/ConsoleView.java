/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package console;

import controller.Controller;
import model.*;
import observer.Observer;

import java.util.Locale;
import java.util.Scanner;

/**
 * @author antoine
 */
public class ConsoleView implements Observer {
    private final Controller controller;
    private Board boardView;

    /**
     * Defensive copy that allows to save all the information.
     *
     * @param controller the controller
     * @param game       the current game
     */
    public ConsoleView(Controller controller, Game game) {
        this.controller = controller;
        game.registerObserver(this);
    }

    /**
     * Allows you to display the table in console format.
     */
    public void printBoardView() {
        StringBuilder draw = new StringBuilder("  |");
        draw.append("-".repeat(boardView.getWidth() * 2 + 1));
        draw.append("|\n");
        for (int lg = 0; lg < boardView.getHeight(); lg++) {
            draw.append(String.format("%02d", lg + 1)).append("|");
            for (int col = 0; col < boardView.getWidth(); col++) {
                Tile tile = boardView.getTileAt(new Point(lg, col));
                String reset = "\u001B[0m";
                String[] colorList = {"\u001B[31m", "\u001B[32m", "\u001B[34m", "\u001B[33m", "\u001B[35m"};
                if (tile == null) {
                    draw.append("  ");
                } else {
                    switch (tile.getColor()) {
                        case RED:
                            draw.append(colorList[0]).append("\uD83D\uDFE5").append(reset);
                            break;
                        case GREEN:
                            draw.append(colorList[1]).append("\uD83D\uDFE5").append(reset);
                            break;
                        case BLUE:
                            draw.append(colorList[2]).append("\uD83D\uDFE5").append(reset);
                            break;
                        case YELLOW:
                            draw.append(colorList[3]).append("\uD83D\uDFE5").append(reset);
                            break;
                        case PURPLE:
                            draw.append(colorList[4]).append("■ ").append(reset);
                            break;
                        default:
                    }
                }
            }
            draw.append("|\n");
        }
        draw.append("  |");
        draw.append("-".repeat(boardView.getWidth() * 2 + 1));
        draw.append("|");

        System.out.println(draw);
    }

    /**
     * Allows to ask the user if he wants to play again or not.
     * @return true if the user wants to replay
     */
    private boolean askReplay() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("You have lost! Do you want to play again? Y/N");
        String userRemain = scanner.nextLine();
        if (userRemain.toLowerCase(Locale.ROOT).equalsIgnoreCase("Y")) {
            return true;
        } else if (userRemain.toLowerCase(Locale.ROOT).equalsIgnoreCase("N")) {
            return false;
        }
        return false;
    }

    /**
     * Allows the user to choose the height, width and difficulty
     */
    public void askGame() {
        System.out.println("Choose board size and difficulty -> <height> <width> <difficulty>:");
        String[] askedBoard = controller.askBoard();
        controller.startGame(Integer.parseInt(askedBoard[0]), Integer.parseInt(askedBoard[1]), Integer.parseInt(askedBoard[2]));
    }

    @Override
    public void update(State state) {
        switch (state) {
            case START:
                askGame();
                break;
            case WON:
                System.out.println("You have won ! Do you want to replay? O/N");
                if (askReplay()) {
                    askGame();
                }
                break;
            case LOST:
                if (askReplay()) {
                    askGame();
                } else {
                    controller.giveUp();
                }
                break;
            case PLAY:
                System.out.println("Enter a command to perform: (delete x y | undo | redo | stop) :");
                controller.askDelete();
                break;
            case ABANDONED:
                System.out.println("You have given up");
                break;
            case PRINT:
                boardView = controller.getBoard();
                printBoardView();
                System.out.println("Score : " + controller.getScore());
                System.out.println("Remaining tiles: " + controller.getRemainTile());
                break;
            default:
                break;
        }
    }
}
