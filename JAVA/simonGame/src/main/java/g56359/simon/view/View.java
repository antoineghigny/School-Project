package g56359.simon.view;

import animatefx.animation.*;
import g56359.simon.controller.Controller;
import g56359.simon.model.Color;
import g56359.simon.model.Model;
import g56359.simon.model.State;
import g56359.simon.observer.Observer;
import javafx.animation.KeyFrame;
import javafx.animation.PauseTransition;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import javafx.util.Duration;

import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author Antoine Ghigny - g56359
 */
public class View extends Application implements Observer {

    private final StackPane stackPane = new StackPane();

    private final HBox button = new HBox(9);
    private final VBox layout = new VBox(20);
    private final VBox gameOver = new VBox(10);

    private final GridPane color = new GridPane();

    private final Button green = new Button();
    private final Button red = new Button();
    private final Button yellow = new Button();
    private final Button blue = new Button();

    private final Label simonText = new Label("Simon");

    private final Slider slider = new Slider(0.1, 1.9, 1);
    private final Button longest = new Button("longest");
    private final Button start = new Button("   start   ");
    private final Button last = new Button("  last   ");
    private final Label info = new Label("Record : 0");
    private final CheckBox checkBox = new CheckBox("Silent mode");
    private final Controller controller;
    private final Model model;

    private boolean sequence;
    Scene root;
    private int increase;
    private int nbrTimes;

    private State stateView;
    /**
     * @param controller the project controller
     * @param model      the project model
     */
    public View(Controller controller, Model model) {
        this.controller = controller;
        this.model = model;
        model.registerObserver(this);
    }

    /**
     * Method used to create all the elements of the view. The whole user interface.
     * @param primaryStage The game window
     */
    @Override
    public void start(Stage primaryStage) {
        int max = 500;
        /*
         * This had to be added to avoid having sound problems.
         * Otherwise, the first note may not play where there may be sound offset problems
         * if placed elsewhere (as in attribute + constructor).
         */
        Synthesizer synth = null;
        try {
            synth = MidiSystem.getSynthesizer();
            MidiChannel channel = synth.getChannels()[0];
            synth.open();
        } catch (MidiUnavailableException e) {
            e.printStackTrace();
        }


        slider.setPadding(new Insets(0, 40, 0, 40));
        slider.showTickLabelsProperty();

        green.setStyle("-fx-background-color: green; ");
        green.setPrefSize(2000, 2000);
        color.add(green, 0, 0);

        red.setStyle("-fx-background-color: #EE1111;");
        red.setPrefSize(2000, 2000);
        color.add(red, 1, 0);

        yellow.setStyle("-fx-background-color: #E2D600;");
        yellow.setPrefSize(2000, 2000);
        color.add(yellow, 0, 1);

        blue.setStyle("-fx-background-color: #02377F;");
        blue.setPrefSize(2000, 2000);
        color.add(blue, 1, 1);

        longest.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; " +
                "-fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; " +
                "-fx-font-family: \"Lucida Sans Unicode\"; ");

        start.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; -" +
                "fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; " +
                "-fx-font-family: \"Lucida Sans Unicode\"; ");

        last.setStyle("-fx-background-radius: 7; -fx-font-size: 13px; " +
                "-fx-text-fill: #2a2a33; -fx-background-insets: 0; -fx-font-weight: bold; " +
                "-fx-font-family: \"Lucida Sans Unicode\"; ");

        simonText.setFont(Font.font("-fx-font-family: \"Lucida Sans Unicode\";", FontWeight.BOLD, 20));
        simonText.setAlignment(Pos.TOP_CENTER);

        info.setFont(Font.font("-fx-font-family: \"Lucida Sans Unicode\"", FontWeight.BOLD, 15));

        button.getChildren().addAll(longest, start, last);
        button.setAlignment(Pos.CENTER);
        layout.getChildren().addAll(simonText, slider, button, info, checkBox);
        layout.setAlignment(Pos.CENTER);

        checkBox.setStyle("-fx-font-family: \"Lucida Sans Unicode\"; -fx-font-weight: bold");

        layout.setStyle("-fx-background-radius: 17; -fx-background-color: white");
        layout.setMaxWidth(250);
        layout.setMaxHeight(250);

        stackPane.getChildren().addAll(color, layout);
        root = new Scene(stackPane, max, max);

        gameOver.setStyle("-fx-background-radius: 15; -fx-background-color: WHITE");
        gameOver.setMaxWidth(250);
        gameOver.setMaxHeight(250);

        start.setOnAction((e) -> controller.sequence());
        longest.setOnAction((e) -> model.longestMethod());
        last.setOnAction((e) -> model.lastMethod());

        green.setOnAction((e) -> animate(Color.GREEN));
        red.setOnAction((e) -> animate(Color.RED));
        yellow.setOnAction((e) -> animate(Color.YELLOW));
        blue.setOnAction((e) -> animate(Color.BLUE));

        disableLongestLast();
        disableColors();
        primaryStage.setTitle("Simon Game");
        primaryStage.setScene(root);
        primaryStage.setMinHeight(400);
        primaryStage.setMinWidth(400);
        primaryStage.getIcons().add(new Image("https://iconape.com/wp-content/png_logo_vector/simon-game-logo.png"));
        primaryStage.show();
    }

    /**
     * A method that allows you to play a sound at the click of a button using a Color enumeration.
     * Different sound is played depending on the button pressed.
     *
     * @param color an enumeration (in this case, one of the colors of the game)
     */
    void sound(Color color) throws MidiUnavailableException {
        Synthesizer synth = MidiSystem.getSynthesizer();
        MidiChannel channel;
        channel = synth.getChannels()[0];
        synth.open();

        if (!checkBox.isSelected()) {
            int noteNumber;
            switch (color) {
                case RED:
                    noteNumber = 71;
                    break;
                case YELLOW:
                    noteNumber = 72;
                    break;
                case BLUE:
                    noteNumber = 74;
                    break;
                default:
                    noteNumber = 69;
            }
            channel.noteOn(noteNumber, 80);
            PauseTransition pause = new PauseTransition(Duration.seconds(1));
            pause.setOnFinished(event -> channel.noteOff(noteNumber));
            pause.play();
        }
    }

    /**
     * Method used to illuminate a button using an enumeration.
     *
     * @param color an enumeration (in this case, one of the colors of the game)
     */
    private void illuminate(Color color) {
        switch (color) {
            case GREEN:
                green.setOpacity(0.8);
                PauseTransition pause = new PauseTransition(Duration.seconds((1 / slider.getValue()) / 3));
                pause.setOnFinished(event -> green.setOpacity(1.0));
                pause.play();
                break;
            case RED:
                red.setOpacity(0.8);
                pause = new PauseTransition(Duration.seconds((1 / slider.getValue()) / 3));
                pause.setOnFinished(event -> red.setOpacity(1.0));
                pause.play();
                break;
            case YELLOW:
                yellow.setOpacity(0.7);
                pause = new PauseTransition(Duration.seconds((1 / slider.getValue()) / 3));
                pause.setOnFinished(event -> yellow.setOpacity(1.0));
                pause.play();
                break;
            case BLUE:
                blue.setOpacity(0.8);
                pause = new PauseTransition(Duration.seconds((1 / slider.getValue()) / 3));
                pause.setOnFinished(event -> blue.setOpacity(1.0));
                pause.play();
                break;
            default:
                green.setOpacity(0.7);
                pause = new PauseTransition(Duration.seconds((1 / slider.getValue()) / 2));
                pause.setOnFinished(event -> green.setOpacity(1.0));
                pause.play();
                break;
        }
    }

    /**
     * Method that allows you to play a sequence of colors.
     *
     * @param color a color list
     */
    public void playSequence(List<Color> color) {
        disableColors();
        disableButtons();
        sequence = true;
        increase = 0;

        double inverted = 1 / slider.getValue();
        Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(inverted), e -> {
            animate(color.get(increase));
            increase++;
            if (increase == nbrTimes) {
                sequence = false;
                if(stateView != State.LAST && stateView != State.LONGEST){
                    activateColors();
                    disableButtons();
                }else{
                    activateButtons();
                }
            }
        }
        ));
        timeline.setCycleCount(nbrTimes);
        timeline.play();
    }

    /**
     * Method that is triggered when the user has the wrong colors.
     */
    public void fail() {
        activateButtons();
        disableColors();

        sequence = true;
        start.setText("replay");
        simonText.setText("Game Over");
        simonText.setStyle("-fx-text-fill: red;");
        new Tada(start).play();
    }
    /**
     * Method which makes it possible to illuminate the color, to play the corresponding sound and to compare the color with that on which the user should have pressed.
     * @param color The button the user clicked.
     */
    public void animate(Color color) {
        illuminate(color);
        try {
            sound(color);
        } catch (MidiUnavailableException ex) {
            Logger.getLogger(View.class.getName()).log(Level.SEVERE, null, ex);
        }
        if (!sequence) {
            PauseTransition pause = new PauseTransition(Duration.seconds(0.001));
            pause.setOnFinished(event -> model.verification(color));
            pause.play();
        }

    }

    /**
     * Method that allows you to disable the buttons that serve as colors in the game.
     */
    public void disableColors() {
        green.setDisable(true);
        red.setDisable(true);
        yellow.setDisable(true);
        blue.setDisable(true);
        green.setOpacity(1.0);
        red.setOpacity(1.0);
        yellow.setOpacity(1.0);
        blue.setOpacity(1.0);
    }

    /**
     * Method which allows to deactivate the start, last and longest buttons.
     */
    public void disableButtons() {
        start.setDisable(true);
        last.setDisable(true);
        longest.setDisable(true);
    }

    /**
     * Method used to activate the start, last and longest buttons.
     */
    public void activateButtons() {
        start.setDisable(false);
        last.setDisable(false);
        longest.setDisable(false);
    }

    /**
     * Method that allows you to activate the buttons that serve as colors in the game.
     */
    public void activateColors() {
        green.setDisable(false);
        red.setDisable(false);
        yellow.setDisable(false);
        blue.setDisable(false);
    }

    /**
     * Method that allows to disable the last and longest buttons
     */
    public void disableLongestLast() {
        last.setDisable(true);
        longest.setDisable(true);
    }

    @Override
    public void update(State state) {
        stateView = state;
        if (model.getActualList().size() > model.getLongestList().size()
                && state != State.LOOSE
                && model.getLongestList().size() > 0) {
            info.setText("Record : " + model.getLongestList().size());
            new BounceIn(info).setSpeed(1.3).play();
        }
        switch (state) {
            case START:
                disableButtons();
                simonText.setText("Simon");
                simonText.setStyle("-fx-text-fill: #2a2a33");
                nbrTimes = model.getActualList().size();
                playSequence(model.getActualList());
                break;
            case LOOSE:
                fail();
                break;
            case LAST:
                if (model.getActualList().size() >= 1) {
                    disableColors();
                    nbrTimes = model.getLastList().size() - 1;
                    playSequence(model.getActualList());
                }
                break;
            case LONGEST:
                    disableColors();
                    nbrTimes = model.getLongestList().size();
                    playSequence(model.getLongestList());
                break;
        }
    }
}