package view;

import javafx.collections.FXCollections;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;

public class resizeBoardFX {
    private final Label height = new Label("Height");
    private final VBox heightVBox = new VBox();
    private final Spinner<Integer> spinnerHeight = new Spinner<>(6, 14, 10);

    private final Label width = new Label("Width");
    private final VBox widthVBox = new VBox();
    private final Spinner<Integer> spinnerWidth = new Spinner<>(6, 20, 10);

    private final Label difficulty = new Label("Difficulty");
    private final VBox difficultyVBox = new VBox();
    private final Spinner<Integer> spinnerDifficulty = new Spinner<>(3, 5, 4);

    private final Button start = new Button("START");

    private final ChoiceBox cb = new ChoiceBox();

    private final VBox vbox = new VBox(35);

    /**
     * Constructor of resizeBoardFX
     */
    public resizeBoardFX() {
        cb.setItems(FXCollections.observableArrayList(
                "Default size",
                new Separator(), "Custom size")
        );
        spinnerHeight.setDisable(true);
        spinnerWidth.setDisable(true);
        spinnerDifficulty.setDisable(true);
        spinnerHeight.getEditor().setText("10");
        spinnerWidth.getEditor().setText("14");
        spinnerDifficulty.getEditor().setText("5");

        cb.getSelectionModel().selectFirst();
        cb.setOnAction((event) -> {
            int selectedIndex = cb.getSelectionModel().getSelectedIndex();
            System.out.println(selectedIndex);
            if (selectedIndex == 0) {
                spinnerHeight.setDisable(true);
                spinnerWidth.setDisable(true);
                spinnerDifficulty.setDisable(true);

                spinnerHeight.getEditor().setText("10");
                spinnerWidth.getEditor().setText("14");
                spinnerDifficulty.getEditor().setText("5");

            } else {
                spinnerHeight.setDisable(false);
                spinnerWidth.setDisable(false);
                spinnerDifficulty.setDisable(false);

                spinnerHeight.getEditor().setText("10");
                spinnerWidth.getEditor().setText("10");
                spinnerDifficulty.getEditor().setText("4");
            }
        });

        heightVBox.getChildren().addAll(height, spinnerHeight);
        height.setStyle("-fx-font-weight: bold; -fx-padding: 0 0 0 6; ");
        heightVBox.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 0 0 0;");

        widthVBox.getChildren().addAll(width, spinnerWidth);
        width.setStyle("-fx-font-weight: bold; -fx-padding: 0 0 0 6;");
        widthVBox.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 0 0 0; ");

        difficultyVBox.getChildren().addAll(difficulty, spinnerDifficulty);
        difficulty.setStyle("-fx-font-weight: bold; -fx-padding: 0 0 0 6;");
        difficultyVBox.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 0 0 0; ");

        start.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; -"
                + "fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; "
                + "-fx-font-family: \"Lucida Sans Unicode\"; ");
        vbox.setAlignment(Pos.CENTER);

        vbox.getChildren().addAll(cb, heightVBox, widthVBox, difficultyVBox, start);
    }

    /**
     * Getter of spinnerHeight
     * @return the spinner of the height
     */
    public Spinner<Integer> getSpinnerHeight() {
        return spinnerHeight;
    }
    /**
     * Getter of spinnerWidth
     * @return the spinner of the width
     */
    public Spinner<Integer> getSpinnerWidth() {
        return spinnerWidth;
    }
    /**
     * Getter of spinnerDifficulty
     * @return the spinner of the difficulty
     */
    public Spinner<Integer> getSpinnerDifficulty() {
        return spinnerDifficulty;
    }
    /**
     * Getter of start
     * @return the Button of start
     */
    public Button getStart() {
        return start;
    }
    /**
     * Getter of Cb
     * @return the ChoiceBox of cb
     */
    public ChoiceBox getCb() {
        return cb;
    }
    /**
     * Getter of vbox
     * @return the VBox of vbox
     */
    public VBox getVbox() {
        return vbox;
    }
}
