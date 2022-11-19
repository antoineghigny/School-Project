/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.luckynumbers.view;

import g56359.luckynumbers.model.Game;
import g56359.luckynumbers.model.Position;
import g56359.luckynumbers.model.Model;
import g56359.luckynumbers.model.Tile;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author antoi
 */
public class MyView implements View {

    final static Scanner clavier = new Scanner(System.in);

    private Model model;

    public MyView(Model model) {
        this.model = model;
    }

    @Override
    public void displayWelcome() {
        System.out.println("LuckyNumbers - g56359 - Version 2");
    }

    @Override
    public void displayGame() {
        System.out.println("Joueur " + (model.getCurrentPlayerNumber() + 1));
        for (int i = 0; i < model.getBoardSize() + 1; i++) {
            if (i == 0) {
                System.out.print("  ");
            } else {
                System.out.print(i + "  ");
            }
        }
        System.out.println();

        System.out.println("-------------");
        for (int i = 0; i < model.getBoardSize(); i++) {
            System.out.print(i + 1 + "|");
            for (int j = 0; j < model.getBoardSize(); j++) {
                if (model.getTile(model.getCurrentPlayerNumber(), new Position(i, j)) == null) {
                    System.out.print(".  ");
                } else {
                    System.out.print(model.getTile(model.getCurrentPlayerNumber(), new Position(i, j)) + "  ");
                }
            }
            System.out.println();

        }

        System.out.println("-------------");

        System.out.println("Nombre de tuiles face cachées : " + model.faceDownTileCount());
        System.out.println("Les tuiles faces visibles : " + model.getAllfaceUpTiles() + ", elles sont au nombre de " + model.faceUpTileCount());
        String piocher = lectureRobusteString("Voulez-vous piocher une tuile face cachée ou face visible ? (c/v)");

        if ("v".equals(piocher)) {
            System.out.println("Laquelle voulez-vous piocher : ");
            int tuileChoisie = clavier.nextInt();
            model.pickFaceUpTile(findTileByValue(model.getAllfaceUpTiles(), tuileChoisie));
        } else {
            model.pickFaceDownTile();
            System.out.println("Tuile choisie : " + model.getPickedTile().getValue());
        }
    }

    private String lectureRobusteString(String msg) {
        System.out.print(msg + ": ");
        while (!clavier.hasNext()) {
            System.err.println("Ce n’est pas un String que vous avez indiqué!");
            clavier.next();
            System.out.print(msg + ": ");
        }
        return (clavier.next());
    }

    @Override
    public void displayWinner() {
        if (model.getWinners().size() > 1) {
            System.out.print("Les gagnants du jeu sont : ");
            printMultipleWinners(model.getWinners());
        } else {
            System.out.println("Le gagnant du jeu est : ");
            printMultipleWinners(model.getWinners());
        }
        System.out.println();
    }

    private static void printMultipleWinners(List<Integer> winners) {

        for (int i = 0; i < winners.size(); i++) {
            if (i < winners.size() - 1) {
                System.out.print("Joueur ");
                System.out.print(winners.get(i) + 1 + ", ");
            } else {
                System.out.print("Joueur ");
                System.out.print(winners.get(i) + 1);
            }
        }
    }

    public static void main(String[] args) {
        printMultipleWinners(List.of(1, 2));
    }

    @Override
    public int askPlayerCount() {
        return lectureRobuste("Combien de joueurs participent à la partie ? ");
    }

    private int lectureRobuste(String msg) {
        System.out.print(msg + ": ");
        while (!clavier.hasNextInt()) {
            System.err.println("Ce n’est pas un entier que vous avez indiqué!");
            clavier.next();
            System.out.print(msg + ": ");
        }
        return (clavier.nextInt());
    }

    @Override
    public Position askPosition() {
        int row = lectureRobuste("Entrez un numéro de ligne") - 1;
        int col = lectureRobuste("Entrez un numéro de colonne") - 1;
        Position pos = new Position(row, col);
        if (!model.canTileBePut(pos) || !model.isInside(pos)) {
            throw new IllegalArgumentException("Vous n'avez pas entré un numéro de ligne et de colonne valide.");
        }
        return pos;
    }

    @Override
    public void displayError(String message) {
        System.err.println(message);
    }

    @Override
    public void chooseDropOrPutTile() {
        System.out.println("Voulez-vous choisir de poser la tuile dans le jeu OU de déposer la tuile face visible p/v");
        String decision = clavier.next();
        if ("v".equals(decision)) {
            model.dropTile();
        } else {
            model.putTile(askPosition());
        }
    }

    private Tile findTileByValue(List<Tile> allfaceUpTiles, int tuileChoisie) {
        for (Tile tile : allfaceUpTiles) {
            if (tile.getValue() == tuileChoisie) {
                return tile;
            }
        }
        return null;
    }
}
