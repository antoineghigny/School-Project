package view;

import controller.ControllerFX;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.effect.ColorAdjust;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import model.Game;
import model.Point;
import model.Tile;

public class ButtonTable {
    private final ControllerFX controller;

    private final GridPane centerBoard = new GridPane();
    private Button[][] buttonBoard;
    private boolean[][] verification;

    /**
     * The constructor of ButtonTable
     *
     * @param controller
     * @param game
     */
    public ButtonTable(ControllerFX controller, Game game) {
        centerBoard.setAlignment(Pos.CENTER);
        centerBoard.setMaxSize(3000, 3000);
        this.controller = controller;
    }

    /**
     * Allows to create a 2D button array
     */
    public void createButtonBoard() {
        this.buttonBoard = new Button[controller.getBoard().getHeight()][controller.getBoard().getWidth()];
        for (int lg = 0; lg < controller.getBoard().getHeight(); lg++) {
            for (int col = 0; col < controller.getBoard().getWidth(); col++) {
                Tile tile = controller.getBoard().getTileAt(new Point(lg, col));
                ButtonFX button = new ButtonFX(lg, col);
                int[] color = {0, 0, 0};
                if (tile == null) {
                    button.setBackground(new Background(new BackgroundFill(Color.web("#232322"), CornerRadii.EMPTY, Insets.EMPTY)));
                    button.setPrefSize(35, 35);
                    button.setBorder(new Border(new BorderStroke(Color.rgb(255, 255, 255, 0.04), BorderStrokeStyle.SOLID, CornerRadii.EMPTY, new BorderWidths(4))));
                } else {
                    button.setBackground(new Background(new BackgroundFill(Color.web(tile.getColor().getColorString()), CornerRadii.EMPTY, Insets.EMPTY)));
                    button.setBorder(new Border(new BorderStroke(Color.rgb(color[0], color[1], color[2], 0.15), BorderStrokeStyle.SOLID, CornerRadii.EMPTY, new BorderWidths(4))));
                    button.setPrefSize(35, 35);
                }
                buttonBoard[lg][col] = button;
            }
        }
    }

    /**
     * Allows to illuminate the spot in which the user is located.
     *
     * @param row    the row of the tile.
     * @param column the column of the tile.
     */
    public void illuminateButton(int row, int column) {
        if (controller.isTile(row, column)) {
            this.verification = controller.selectGroup(row, column);
            for (int i = 0; i < verification.length; i++) {
                for (int j = 0; j < verification[0].length; j++) {
                    if (verification[i][j]) {
                        ColorAdjust colorAdjust = new ColorAdjust();
                        colorAdjust.setSaturation(0.2);
                        buttonBoard[i][j].setEffect(colorAdjust);
                        buttonBoard[i][j].setOpacity(0.8);
                    }
                }
            }
        }
    }

    /**
     * Allows the illumination of the buttons to be removed.
     */
    public void unIlluminateButton() {
        for (int i = 0; i < verification.length; i++) {
            for (int j = 0; j < verification[0].length; j++) {
                if (verification[i][j]) {
                    ColorAdjust colorAdjust = new ColorAdjust();
                    colorAdjust.setSaturation(0);
                    buttonBoard[i][j].setEffect(colorAdjust);
                    buttonBoard[i][j].setOpacity(1);
                }
            }
        }
    }

    /**
     * A method of placing buttons in the gridpane, which when passed over a tile,
     * illuminates the spot but also removes the spot when the tile is clicked on.
     */
    public void ActionButtonBoard() {
        centerBoard.getChildren().clear();
        for (int lg = 0; lg < buttonBoard.length; lg++) {
            for (int col = 0; col < buttonBoard[0].length; col++) {
                centerBoard.add(buttonBoard[lg][col], col, lg);
                buttonBoard[lg][col].setOnAction(e -> {
                    ButtonFX buttonFx;
                    buttonFx = (ButtonFX) e.getSource();
                    controller.askDelete(buttonFx.getRow(), buttonFx.getColumn());
                });
                int finalLg = lg;
                int finalCol = col;
                buttonBoard[lg][col].setOnMouseEntered(e -> {
                    illuminateButton(finalLg, finalCol);
                });
                buttonBoard[lg][col].setOnMouseExited(e -> {
                    unIlluminateButton();
                });
            }
        }
    }

    /**
     * If the state is set to lost, changes the opacity of all buttons.
     */
    public void isLost() {
        for (int lg = 0; lg < buttonBoard.length; lg++) {
            for (int col = 0; col < buttonBoard[0].length; col++) {
                buttonBoard[lg][col].setOpacity(0.35);
            }
        }
        centerBoard.setDisable(true);
    }

    /**
     * Getter of the gridpane
     *
     * @return the gridpane
     */
    public GridPane getCenterBoard() {
        return centerBoard;
    }
}