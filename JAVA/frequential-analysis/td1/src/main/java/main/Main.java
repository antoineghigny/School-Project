package main;

import controller.Controller;
import factory.Factory;
import model.Model;

public class Main {
    public static void main(String[] args) {
        Model model = new Model();
        Factory factory = new Factory(model);
        Controller controller = new Controller(factory);
    }
}
