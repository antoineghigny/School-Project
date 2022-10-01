package command;

import model.FacadeInterface;
import model.GameState;

/**
 * The DeleteCommand class inherits from CommandInterface and allows
 * executing or cancel a command
 */
public class DeleteCommand implements CommandInterface {
    private GameState state;
    private final FacadeInterface game;
    private final int x;
    private final int y;

    /**
     * The control builder
     * @param game the current game
     * @param x the current x
     * @param y the current y
     */
    public DeleteCommand(FacadeInterface game, int x, int y) {
        this.game = game;
        this.x = x;
        this.y = y;
    }

    @Override
    public void execute() {
        state = new GameState(game.getBoard(),game.getScore(),game.getRemainTiles(), game.getPrevious(), game.getDeletedColumn());
        game.play(x, y);
    }

    @Override
    public void undo() {
        game.setState(state);
    }

}
