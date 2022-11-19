package g56359.luckynumbers.view;

import g56359.luckynumbers.model.Position;

/**
 *
 * @author antoi
 */
public interface View {

    /**
     * Displays welcome to the user, the creator of the game and all that
     * follows.
     */
    void displayWelcome();

    /**
     * Displays the number of players, displays the game board, shows the number
     * of face down tiles and the number of face up tiles, along with their
     * values ​​and asks the user if he wants to draw a face down or up tile, if
     * he chooses the face up, asks the user which one he wants to draw among
     * all the face up cards, otherwise, chooses a random tile. among the face
     * down tiles.
     */
    void displayGame();

    /**
     * Displays the winner (s) of the game, they can win either by completing
     * the game, or if there are no more cards face down, the winner (s) are
     * then those with the most cards in their deck.
     */
    void displayWinner();

    /**
     * Asks for the number of players who will participate in the game.
     *
     * @return the number of players
     */
    int askPlayerCount();

    /**
     * Ask the user for the position of the tile
     *
     * @return the position where to place the tile.
     */
    Position askPosition();

    /**
     * Displays the error message
     *
     * @param message the error message to display
     *
     */
    void displayError(String message);

    /**
     * Asks the user if he wants to choose a tile to put on his deck, or put the
     * tile face up.
     */
    void chooseDropOrPutTile();
}
