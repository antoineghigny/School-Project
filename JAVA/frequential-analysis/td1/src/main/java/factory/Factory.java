package factory;

import command.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import model.Model;
import model.Preprocess;
import java.util.Objects;
import java.util.stream.Stream;

import view.View;


public class Factory {
    private Model model;
    private View view;

    public Factory(Model model) {
        this.model = model;
    }

    public void addView(View view) {
        this.view = view;
    }

    /**
     * Create a command according to the user's input.
     * Also verify the parameters of the command.
     * @param commandString the user's input
     * @param file If the message is a path
     * @return The created command
     */
    public Command createCommand(String commandString, boolean file) {
        String[] command = commandString.split("&");
        String verifCommand = verifCommand(command[0].toUpperCase());
        return switch (verifCommand) {
            case "HELP" -> new Help(view);
            case "ENCODE" -> {
                Cypher cyph = new Cypher(model, fileToString(command[1], file), verifKey(command[2].toUpperCase(), verifMethod(command[3].toUpperCase()), command[1].length()), command[3].toUpperCase());
                yield cyph;
            }
            case "DECODE" -> {
                Decypher decyph = new Decypher(model, fileToString(command[1], file), verifKey(command[2].toUpperCase(), verifMethod(command[3].toUpperCase()), command[1].length()), command[3].toUpperCase());
                yield decyph;
            }
            case "CRACK" -> {
                Crack crack = new Crack(model, fileToString(command[1], file));
                yield crack;
            }
            default -> null;
        };
    }


    /**
     * Check if the parameter is a path.
     * If yes, reads the file and returns the text.
     * @param paths the user's input
     * @param file If the message is a path
     * @return The text
     */
    private String fileToString(String paths, boolean file) {
        String text = "";
        if (file) {
            try {
                text = Preprocess.sanitizeToAlpha(Files.readString(Paths.get(paths)));
                return text.toUpperCase();
            } catch (IOException e) {
                throw new IllegalArgumentException("File not found");
            }
        } else {
            text = Preprocess.sanitizeToAlpha(paths);
            return text.toUpperCase();
        }
    }

    private String verifCommand(String s) {
        if (Stream.of("ENCODE", "DECODE", "CRACK", "HELP", "EXIT").noneMatch(v -> Objects.equals(s, v))) {
            throw new IllegalArgumentException("You did not enter a correct command");
        }
        return s;
    }

    private String verifMethod(String s) {
        if (Stream.of("CAESAR", "VIGENERE").noneMatch(v -> Objects.equals(s, v))) {
            throw new IllegalArgumentException("You did not enter a correct command");
        }
        return s;
    }

    private String verifKey(String s, String method, int msgLength) {
        if (method.equals("CAESAR")) {
            try{
                if (Integer.parseInt(s) <= 0 || Integer.parseInt(s) >= 26) {
                    throw new IllegalArgumentException();
                }
            }catch(Exception e){
                throw new IllegalArgumentException("Using Caesar Method, your key must be a number between 1 and 25");
            }
        } else {
            if (s.length() > msgLength)
                s = s.substring(0, msgLength);
        }
        return s;
    }
}
