package g56359.luckynumbers.model;

public enum State {
    /**
     * At the beginning, we are in the NOT_STARTED state, and the only possible
     * action on the game will be to call the start () state.
     */
    NOT_STARTED,
    /**
     * When the start state is launched, PICK_TILE will choose a tile and the
     * only possible action on the game will be to call the pickTile () state.
     */
    PICK_TILE,
    /**
     * When the pickTile () state is launched, PLACE_TILE will place the tile
     * in the correct position, verifying that all the conditions are met. If
     * the game is over, the only possibility will be to start one again. If the
     * game is not over, we are at the end of the player's turn and the only
     * possible continuation is to move on to the next player.
     */
    PLACE_TILE,
    /**
     * When TURN_END is called, the only possible action of the game is to go to
     * the next player
     *
     *
     */
    TURN_END,
    /**
     * When GAME_OVER is called, the game is over, the only possibility is to
     * start a new one.
     */
    GAME_OVER,
    /**
     * When PLACE_OR_DROP_TILE is called,there are 2 possibility, the first
     * possibility is to lay the tile and the second is to drop the tile. If the
     * tile is dropped, it's the next player's turn, otherwise, if the game is
     * over, start a new game, if the game is not over it's the next player's
     * turn.
     */
    PLACE_OR_DROP_TILE;
}
