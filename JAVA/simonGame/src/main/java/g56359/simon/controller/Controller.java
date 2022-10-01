/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.simon.controller;

import g56359.simon.model.Model;
import g56359.simon.view.View;
import javafx.stage.Stage;

/**
 * @author Antoine Ghigny - g56359
 */
public class Controller {
    private final Model model;

    public Controller(Model model, Stage stage) {
        this.model = model;
        View view = new View(this, model);
        view.start(stage);
    }

    public void sequence() {
        model.startMethod();
    }
}
