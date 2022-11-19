package esi.atl.g56359.stibride;

import esi.atl.g56359.stibride.model.Model;
import esi.atl.g56359.stibride.presenter.Presenter;
import esi.atl.g56359.stibride.view.View;
import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        Model model = new Model();
        View view = new View(stage);
        Presenter presenter = new Presenter(model, view);
        presenter.initialize();
        view.addPresenter(presenter);
        model.registerObserver(presenter);
    }
}
