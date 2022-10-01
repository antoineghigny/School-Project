package view;

import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class ScoreFX {
    private final Label remainTiles = new Label("REMAIN TILES : ");

    private final Label score = new Label("ACTUAL SCORE : 0");
    private final Label maxScore = new Label("HIGH SCORE : 0");

    private final HBox topLabel = new HBox(40);

    /**
     * Constructor of scoreFX
     */
    public ScoreFX() {
            topLabel.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
            topLabel.setMinHeight(140);
            topLabel.setStyle("-fx-alignment: center; -fx-background-color: #232322; -fx-text-fill: white; -fx-font-size: 20px; -fx-padding: 0 200 0 0;");
            String family = "Helvetica";
            remainTiles.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 6 3 6;");
            score.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 6 3 6;");
            maxScore.setStyle("-fx-background-color: white; -fx-background-radius: 6; -fx-padding: 3 6 3 6;");

            remainTiles.setFont(Font.font(family, FontWeight.BOLD, 20));
            score.setFont(Font.font(family, FontWeight.BOLD, 20));
            maxScore.setFont(Font.font(family, FontWeight.BOLD, 20));

            topLabel.getChildren().addAll(score, remainTiles, maxScore);
    }

    /**
     * Getter of topLabel
     * @return a HBox
     */
    public HBox getTopLabel() {
        return topLabel;
    }

    /**
     * Getter of remainTiles
     * @return a Label of remainTiles
     */
    public Label getRemainTiles() {
        return remainTiles;
    }

    /**
     * Getter of score
     * @return the Label of the score
     */
    public Label getScore() {
        return score;
    }

    /**
     * Getter of maxScore
     * @return the Label of maxScore
     */
    public Label getMaxScore() {
        return maxScore;
    }
}
