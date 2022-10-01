package view;

import javafx.scene.control.Button;
import javafx.scene.layout.HBox;

public class CommandFX {

    private final HBox bottomLabel = new HBox(40);

    private final Button exit = new Button("EXIT");
    private final Button undo = new Button("UNDO");
    private final Button redo = new Button("REDO");

    /**
     * Constructor of CommandFX
     */
    public CommandFX() {
        bottomLabel.setStyle("-fx-alignment: center; -fx-background-color: #232322; -fx-border-radius: 15px; -fx-padding: 0 180 21 0;");
        bottomLabel.setMinHeight(140);
        bottomLabel.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);

        redo.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; "
                + "-fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; "
                + "-fx-font-family: \"Lucida Sans Unicode\"; ");

        exit.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; "
                + "-fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; "
                + "-fx-font-family: \"Lucida Sans Unicode\"; ");

        undo.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; "
                + "-fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; "
                + "-fx-font-family: \"Lucida Sans Unicode\"; ");

        bottomLabel.getChildren().addAll(undo, exit, redo);

    }

    /**
     * Getter of bottomLabel
     * @return the bottom label
     */
    public HBox getBottomLabel() {
        return bottomLabel;
    }

    /**
     * Getter of exit button
     * @return the exit button
     */
    public Button getExit() {
        return exit;
    }

    /**
     * Getter of undo button
     * @return the undo button
     */
    public Button getUndo() {
        return undo;
    }

    /**
     * Getter of redo button
     * @return the redo button
     */
    public Button getRedo() {
        return redo;
    }


}
