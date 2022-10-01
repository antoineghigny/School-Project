#ifndef CONTROLLERH_H
#define CONTROLLERH_H

#include <Game.h>
#include <Player.h>
#include <Model.h>
#include <Deck.h>
#include <Board.h>

#include "QMainWindow"

#include "mainwindow.h"

class ControllerGui
{
  private:
    Game _game;

  public:

    /**
     * @brief checkInputGameMode check the input of the player.
     *
     * Check if the player has enter Y, N or help.
     * If he enter other things display an error message.
     */
    void startGame(const bool easyMode);

    /**
     * @brief Controller Constructor that will initialize the model and the view.
     */
    ControllerGui();

    /**
     * @brief startGame Method that calls the start method in game.
     * @param easyMode 1 if the user wants to run in easy mode, 0 otherwise.
     */
    void startGame(const int easyMode);

    /**
     * @brief loadFile Method that calls the game's loadFile method.
     * @param path a string that contains the location to a txt file that contains the board.
     */
    void loadFile(const std::string path);

    /**
     * @brief getCurrentPlayer Method that retrieves the current player from the game.
     * @return the current player
     */
    Team getCurrentPlayer() const;

    /**
     * @brief putPawn Method that calls the game's putPawn method.
     * @param pawn The pawn to be moved
     * @param x The x-position of the pawn
     * @param y The y-position of the pawn
     */
    void putPawn(const Pawn pawn, const int x, const int y);

    /**
     * @brief addObserver
     * @param o
     */
    void addObserver(Observer * o);

    /**
     * @brief getWinner Method that retrieves the current winner from the game.
     * @return the winner of the game
     */
    Team getWinner() const;

    /**
     * @brief canBePut check if the given position is a position where the pawn can be put.
     * @param pawn the pawn.
     * @param x the position on the x-axis.
     * @param y the position on the y-axis
     * @return true if the can be put at the position else return false.
     */
    bool canBePut(const Pawn pawn, const int x, const int y);

    /**
     * @brief canBeMoved Method that calls the game method, which
     * indicates whether the chosen pawn can move
     * @param x The x-position of the pawn
     * @param y The y-position of the pawn
     */
    bool canBeMoved(const int x, const int y);

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
    int getDeckSize() const;

    /**
     * @brief getDeadPawnRole get the role a dead pawn of a specific player.
     * @param playerNumber the player number.
     * @param index the index of the dead pawn in the graveyard of the player.
     * @return the role of the dead pawn.
     */
    Role getDeadPawnRole(const int playerNumber, const int index) const;

    /**
     * @brief getDeckSize Method that calls the game
     * method, which returns the size of the board
     * @return the size of the board
     */
    int getBoardSize() const;

    /**
     * @brief numberOfDeadSoldier Method that calls
     *  the game method, which returns the number of
     *  dead soldiers.
     * @param playerNumber The player to whom we want to
     *  find the number of his dead pieces.
     * @return the number of dead pawn.
     */
    int numberOfDeadSoldier(const int playerNumber);

    /**
     * @brief deadPawnToString A method that flips a
     * player's pawn at a given position. Display the stringify role.
     * @param pos the position in the vector
     * @param playerNumber The position of the dead pawn in the graveyard
     * @return a string composed of the role of the dead pawn
     */
    std::string deadPawnToString(const int pos, const int playerNumber);

    /**
     * @brief getPawnInDeck Calls the method of the game that retrieves a pawn from the deck
     * @return a pawn in the deck
     */
    Pawn getPawnInDeck() const;

    /**
     * @brief getPawnInDeckAt get the pawn in the deck.
     * @param index the index of the pawn in the deck.
     * @return the pawn.
     */
    Pawn getPawnInDeckAt(const int index) const;

    /**
     * @brief isSamePosition check if the destination position is the same as the original position of the pawn.
     * @param pos
     */
    void isSamePosition(const Position pos);

    /**
     * @brief movePawnGui move the pawn.
     *
     * If the pawn can't be moved it will throw an error et return to the interface
     * false to indaicate the player that the position where he want to put the pawn is not correct.
     *
     * @param pos the destination of the pawn.
     * @return false if the pawn can't be put at the destination.
     */
    bool isCorrectMove(const Position pos);

    void movePawnGui(const Position pos); // a delete ?

    /**
     * @brief getDestinationPosition get the destination that the player choose.
     * @return the destination's position.
     */
    Position getDestinationPosition() const;

    /**
     * @brief getPawn Method that calls the method of the game that retrieves the pawn at a certain position.
     * @param position The position of a pawn
     * @return returns the pawn to a certain position
     */
    Pawn getPawnAtPos(const Position position);

    /**
     * @brief getLastDeadPawn get the last dead pawn of the given player number.
     * @param playerNumber the player number.
     * @return return the role and the team of the dead pawn.
     */
    std::pair<Role, Team> getLastDeadPawn(const int playerNumber) ;

    /**
     * @brief play Calls the method of the game that starts the game.
     */
    void play();

    /**
     * @brief getState get the current state of the game.
     * @return return the current state of the game.
     */
    State getState() const;

    /**
     * @brief putPawnAt put the pawn in the board at the given position.
     * @param pawn the pawn.
     * @param x the position on the x-axis.
     * @param y the position on the y-axis.
     * @param index the index of the pawn in the deck.
     */
    void putPawnAt(const int x, const int y, const int index);

    /**
     * @brief getGameResult get the result of the game.
     */
    GameResult getGameResult() const;
};

#endif // CONTROLLERH_H
