package main;

import controller.Controller;
import model.Game;

public class Main {
    public static void main(String[] args) {
        Game game = new Game();
        Controller controller = new Controller(game);
    }
}
