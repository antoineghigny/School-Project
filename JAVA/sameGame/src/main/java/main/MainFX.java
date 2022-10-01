package main;

import controller.ControllerFX;
import javafx.application.Application;
import javafx.stage.Stage;
import model.Game;

public class MainFX extends Application {
    public static void main(String[] args) {
        launch();
    }
    @Override
    public void start(Stage stage) {
        Game game = new Game();
        ControllerFX controllerFx = new ControllerFX(game, stage);
    }
}
