/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view;

import controller.ControllerFX;
import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import model.Game;
import model.State;
import observer.Observer;

/**
 * @author antoi
 */
public class View extends Application implements Observer {

    private final ButtonTable buttonTable;
    private final ScoreFX scoreFx;
    private final CommandFX commandFx;
    private final ControllerFX controller;
    private final resizeBoardFX resizeBoardFx;

    private final StackPane stackPane = new StackPane();
    private final StackPane stackGameOver = new StackPane();

    private final Label gameOver = new Label("GAME OVER");
    private final VBox gameOverPanel = new VBox(5);

    private final HBox midLabel = new HBox();

    private final HBox mid = new HBox(40);
    private final BorderPane root = new BorderPane();

    private int nbrGames;

    /**
     * Controller of the View, this view becomes an observer
     * @param controller the controller
     * @param game the game
     */
    public View(ControllerFX controller, Game game) {
        this.controller = controller;
        this.buttonTable = new ButtonTable(controller, game);
        this.scoreFx = new ScoreFX();
        this.commandFx = new CommandFX();
        this.resizeBoardFx = new resizeBoardFX();
        game.registerObserver(this);
    }

    @Override
    public void start(Stage primaryStage) {
        controller.start();

        String family = "Helvetica";

        midLabel.setStyle("-fx-alignment: center; -fx-background-color: #232322; -fx-border-radius: 15px; ");
        midLabel.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);

        gameOver.setStyle("-fx-background-color: white; -fx-background-radius: 9; -fx-padding: 10 20 10 20; -fx-border-width: 4px;  -fx-border-color: #232322; -fx-border-radius: 6");
        gameOver.setFont(Font.font(family, FontWeight.BOLD, 30));
        gameOver.setAlignment(Pos.CENTER);

        root.setTop(scoreFx.getTopLabel());
        root.setBottom(commandFx.getBottomLabel());
        root.setCenter(stackPane);

        final Scene scene = new Scene(root, 350, 300);

        mid.setAlignment(Pos.CENTER);
        stackGameOver.getChildren().addAll(buttonTable.getCenterBoard(), gameOver);

        mid.getChildren().addAll(stackGameOver, resizeBoardFx.getVbox());
        stackPane.getChildren().addAll(midLabel, gameOverPanel, mid);

        resizeBoardFx.getStart().setOnAction(e -> {
            controller.start();
        });

        commandFx.getUndo().setOnAction(e -> {
            controller.undoCommand();
        });

        commandFx.getRedo().setOnAction(e -> {
            controller.redoCommand();
        });

        commandFx.getExit().setOnAction(e -> {
            controller.giveUp();
        });

        primaryStage.setTitle("Simon Game");
        primaryStage.getIcons().add(new Image("https://store-images.microsoft.com/image/apps.27008.9007199266291634.9fba633b-41b2-4a2e-a25e-7079ff93027c.5ab04cdc-a91a-4ef9-bc55-08337543f03a?mode=scale&q=90&h=200&w=200&background=%23464646"));
        primaryStage.setScene(scene);
        primaryStage.setMinHeight(750);
        primaryStage.setMinWidth(1000);
        primaryStage.show();
    }

    @Override
    public void update(State state) {
        switch (state) {
            case START:
                disableCommand();
                int selectedIndex = resizeBoardFx.getCb().getSelectionModel().getSelectedIndex();
                if (selectedIndex == 0 || nbrGames == 0) {
                    controller.startGame();
                } else {
                    controller.startGame(resizeBoardFx.getSpinnerHeight().getValue(), resizeBoardFx.getSpinnerWidth().getValue(), resizeBoardFx.getSpinnerDifficulty().getValue());
                }
                nbrGames++;
                buttonTable.getCenterBoard().setDisable(false);
                gameOverEnable();
                resizeBoardFx.getStart().setText("RESTART");
                break;
            case WON:
                gameOverDisable();
                enableCommand();
                break;
            case LOST:
                buttonTable.isLost();
                enableCommand();
                gameOverDisable();
                break;
            case ABANDONED:
                controller.isLost();
                break;
            case PRINT:
                buttonTable.createButtonBoard();
                buttonTable.ActionButtonBoard();
                int score = controller.getScore();
                int maxScore = controller.getMaxScore();
                scoreFx.getScore().setText("ACTUAL SCORE : " + score);
                scoreFx.getRemainTiles().setText("REMAIN TILES : "+controller.getRemainTile());
                scoreFx.getMaxScore().setText("  HIGH SCORE : " + maxScore + "  ");
                break;
            default:
                break;
        }
    }

    /**
     * Method to disable commands (undo, redo, exit)
     */
    private void disableCommand(){
        commandFx.getUndo().setDisable(false);
        commandFx.getRedo().setDisable(false);
        commandFx.getExit().setDisable(false);

    }

    /**
     * Method that enables commands (undo, redo, exit)
     */
    private void enableCommand(){
        commandFx.getUndo().setDisable(true);
        commandFx.getRedo().setDisable(true);
        commandFx.getExit().setDisable(true);
    }

    /**
     * Method that allows you to deactivate Game Over and change its text to game over
     */
    private void gameOverDisable(){
        gameOver.setDisable(false);
        gameOver.setOpacity(1);

        gameOver.setText("GAME OVER !");
    }

    /**
     * Method which allows to activate game over and to pass the text to win
     */
    private void gameOverEnable(){
        gameOver.setDisable(true);
        gameOver.setOpacity(0);
        gameOver.setText("YOU WIN !");
    }
}