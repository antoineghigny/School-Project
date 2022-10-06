package controller;

import command.Command;
import factory.Factory;
import view.View;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Controller {
    private Factory factory;
    private View view;

    public Controller(Factory factory) {
        this.factory = factory;
        this.view = new View();
        this.factory.addView(view);
        choiceCommand();
    }

    private void choiceCommand() {
        view.header();
        String text = " ";
        do {        
                text = view.introduceProgram();
                boolean file = true;
                try{
                    if (!text.equalsIgnoreCase("exit")) {
                        String[] paths = text.split("&");
                        Path path = Paths.get(paths[1]);
                        file = Files.isRegularFile(path);
                    }
                }catch(Exception e){
                    file = false;
                }
                try{
                    Command command = factory.createCommand(text, file);
                    if (command == null && !text.equalsIgnoreCase("exit")) {
                        view.helpCommand();
                    } else if (command != null) {
                        String txt = command.execute();
                        if (file) view.writeInFile(txt);
                        else view.printText(txt); System.out.println("");
                    }
                } catch (Exception e) {
                    System.out.println("\n" + e.getMessage());
                }
        } while (!text.equalsIgnoreCase("exit"));
    }
}