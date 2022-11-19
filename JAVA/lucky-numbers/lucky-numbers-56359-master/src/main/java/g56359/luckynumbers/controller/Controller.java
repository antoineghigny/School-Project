/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.luckynumbers.controller;

import g56359.luckynumbers.model.Game;
import g56359.luckynumbers.model.Model;
import g56359.luckynumbers.model.Position;
import static g56359.luckynumbers.model.State.NOT_STARTED;
import g56359.luckynumbers.view.MyView;
import g56359.luckynumbers.view.View;

/**
 *
 * @author antoi
 */
public class Controller {

    private Model model;
    private View view;

    public Controller(Model model, View view) {
        this.view = view;
        this.model = model;
    }

    public void play() {
        view.displayWelcome();
        while (true) {
            switch (model.getState()) {
                case NOT_STARTED:
                    int playerCount = view.askPlayerCount();
                    model.start(playerCount);
                    break;
                case PICK_TILE:
                    view.displayGame();
                    break;

                case PLACE_TILE:
                    Position pos = view.askPosition();
                    model.putTile(pos);
                    break;

                case PLACE_OR_DROP_TILE:
                    view.chooseDropOrPutTile();

                    break;
                case TURN_END:
                    model.nextPlayer();
                    break;

                case GAME_OVER:
                    view.displayWinner();
                    view.displayWelcome();
                    playerCount = view.askPlayerCount();
                    model.start(playerCount);
                    break;
            }
        }
    }
}
