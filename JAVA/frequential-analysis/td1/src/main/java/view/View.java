package view;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import java.util.Scanner;

public class View {

    public void header() {
        System.out.println("This program helps you encode and crack messages.");
        System.out.println("Please, use it wisely.");
        System.out.println(helpCommand());
        System.out.println("- - - - - - - - - - - - - - - - - -");
    }


    public String introduceProgram() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("\n\nDo you want to encode, decode or crack a text? help for more information");
        return scanner.nextLine();
    }

    public String helpCommand() {
        String s = "To encode a message : ENCODE&MESSAGE&KEY&METHOD\n"
                + "To decode a message : DECODE&MESSAGE&KEY&METHOD\n"
                + "To crack a message  : CRACK&MESSAGE\n"
                + "If you are using a file, you must replace "
                + "MESSAGE by the absolute path of the file.\n"
                + "Note that if you are using Caesar method, the key must be an integer between 1 and 25.\n"
                + "\nTo exit the program, type exit.";
        return s;
    }

    public void printText(String s) {
        System.out.println(s);
    }

    public void writeInFile(String txt) {
        File answer = new File("answer.txt");
        try {
            answer.createNewFile();
            Files.writeString(Paths.get(answer.getAbsolutePath()), txt, StandardOpenOption.TRUNCATE_EXISTING);
            System.out.println("Answer writed in file answer.txt at : " + answer.getAbsolutePath());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
