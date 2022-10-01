package g56359.simon.simonGame;

import g56359.simon.controller.Controller;
import g56359.simon.model.Model;
import javafx.application.Application;
import javafx.stage.Stage;

/**
 * @author Antoine Ghigny - g56359
 */
public class Main extends Application {

    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage stage) {
        Model model = new Model();
        Controller controller = new Controller(model, stage);
    }
}
