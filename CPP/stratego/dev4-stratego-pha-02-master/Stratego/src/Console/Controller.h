#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ViewConsole.h>
#include <Player.h>
#include <Model.h>
#include <Deck.h>
#include <Board.h>

class Controller
{
private:

    Game _game;
    ViewConsole _viewConsole;

    /**
     * @brief checkInputGameMode check the input of the player.
     *
     * Check if the player has enter Y, N or help.
     * If he enter other things display an error message.
     */
    void checkInputGameMode(const std::string input);

public:

    /**
     * @brief Controller Constructor that will initialize the model and the view.
     */
    Controller();


    /**
     * @brief loadFile Method that calls the game's loadFile method.
     * @param path a string that contains the location to a txt file that contains the board.
     */
    void loadFile(std::string path);

    /**
     * @brief getCurrentPlayer Method that retrieves the current player from the game.
     * @return the current player
     */
    Team getCurrentPlayer();

    /**
     * @brief putPawn Method that calls the game's putPawn method.
     * @param pawn The pawn to be moved
     * @param x The x-position of the pawn
     * @param y The y-position of the pawn
     */
    void putPawn(Pawn pawn, int x, int y);

    /**
     * @brief getWinner Method that retrieves the current winner from the game.
     * @return the winner of the game
     */
    Team getWinner();

    /**
     * @brief canBeMoved Method that calls the game method, which
     * indicates whether the chosen pawn can move
     * @param x The x-position of the pawn
     * @param y The y-position of the pawn
     */
    void canBeMoved(int x, int y);

    /**
     * @brief generateDeck Method that calls the generateDeck
     * method of the pawn. If the user wants to place his pawns 1 by 1.
     */
    void generateDeck();

    /**
     * @brief getDeckSize Method that calls the game
     * method, which returns the size of the deck
     * @return the size of the deck
     */
    int getDeckSize();

    /**
     * @brief getDeadPawnRole get the role a dead pawn of a specific player.
     * @param playerNumber the player number.
     * @param index the index of the dead pawn in the graveyard of the player.
     * @return the role of the dead pawn.
     */
    Role getDeadPawnRole(int playerNumber, int index);

    /**
     * @brief getDeckSize Method that calls the game
     * method, which returns the size of the board
     * @return the size of the board
     */
    int getBoardSize();

    /**
     * @brief numberOfDeadSoldier Method that calls
     *  the game method, which returns the number of
     *  dead soldiers.
     * @param playerNumber The player to whom we want to
     *  find the number of his dead pieces.
     * @return the number of dead pawn.
     */
    int numberOfDeadSoldier(int playerNumber);

    /**
     * @brief deadPawnToString A method that flips a
     * player's pawn at a given position. Display the stringify role.
     * @param pos the position in the vector
     * @param playerNumber The position of the dead pawn in the graveyard
     * @return a string composed of the role of the dead pawn
     */
    std::string deadPawnToString(int pos, int playerNumber);

    /**
     * @brief getPawnInDeck Calls the method of the game that retrieves a pawn from the deck
     * @return a pawn in the deck
     */
    Pawn getPawnInDeck();

    /**
     * @brief currentPlayer Displays the current player
     * @return the current player
     */
    std::string currentPlayer();

    /**
     * @brief movePawn Choose the location to move the counter
     * @param x the position in x where to move the pawn
     * @param y the position in y where to move the pawn
     */
    void movePawn(int x, int y);

    /**
     * @brief getPawn Method that calls the method of the game that retrieves the pawn at a certain position.
     * @param position The position of a pawn
     * @return returns the pawn to a certain position
     */
    Pawn getPawn(Position position);

    /**
     * @brief play Calls the method of the game that starts the game.
     */
    void play();
};

#endif // CONTROLLER_H
