#ifndef MODEL_H
#define MODEL_H

#include "Position.h"
#include "Graveyard.h"
#include "GameResult.h"
#include "State.h"
#include <string>
#include "Deck.h"
/**
 * @brief The Model class The interface that declares
 * the different methods used in the Game class.
 */
class Model
{

  public:

    virtual ~Model() {};

    /**
     * @brief start the method to start a game.
     * @param isEasyMode indicate if the game is in easy mode or not.
     */
    virtual void start(const bool isEasyMode) = 0;

    /**
     * @brief restart restart the game.
     *
     * @param isEasyMode the game mode.
     */
    virtual void restart(const bool isEasyMode) = 0;

    /**
     * @brief generateDeck generate the deck of pawn for the current player.
     */
    virtual void generateDeck() = 0;

    /**
     * @brief getPawnInDeck get the first pawn in the deck.
     * @return the pawn in the deck.
     */
    virtual const Pawn getPawnInDeck() const = 0;

    /**
     * @brief getDeckSize get the size of the deck.
     *
     * So the size rrepresent the number of pawn in the deck.
     *
     * @return the size of the deck.
     */
    virtual int getDeckSize() const = 0 ;

    /**
     * @brief putPawn put the pawn at the given position.
     * @param pawn the pawn.
     * @param pos the position where the pawn will be put.
     */
    virtual void putPawn(Pawn pawn, const Position pos) = 0;

    /**
     * @brief loadFile load the file that contains the placement of the pawn.
     * @param path the path of the file that will be used to place the pawn
     * of the current player.
     */
    virtual void loadFile(const std::string path) = 0;

    /**
     * @brief nextPlayer Pass to the next player.
     */
    virtual void nextPlayer() = 0;

    /**
     * @brief putPawnAt a modified version of the method putPawn adapted for the GUI.
     * @param pawn the pawn.
     * @param pos the position of the where the pawn will be put in the board.
     * @param index the index of the pawn in the deck.
     */
    virtual void putPawnAt(const Position pos, const int index) = 0;

    /**
     * @brief canBePut check if the current player can play.
     *
     * Before the current player plays, check if the current player
     * is not blocked so that's means if the current player has at least one pawn
     * that can move.
     */
    virtual bool canBePut(const Pawn & pawn, const Position pos) = 0;

    /**
     * @brief canBePicked Checks if the pawn at the given position can be picked.
     *
     * By correct, it's means that the position of the wanted pawn is inside the board.
     * Also check if there is a pawn at this position, if the selected pawn is moveable,
     * if the selected pawn is a pawn of the current player and this pawn is not surrounded
     * by allied pawn and/or wall.
     *
     * @param pos The position of the pawn that the user wants to move
     * @param team The team to which the counter belongs
     */
    virtual void canBePicked(const Position pos) = 0;

    /**
     * @brief canBePick a modified version of the method canBePicked for the GUI.
     * @param pos the position where the player want to pick the pawn.
     * @return true if the pawn can be picked else return false.
     */
    virtual bool canBePick(const Position pos) = 0;

    /**
     * @brief movePawn Method that determines if a pawn can be moved
     * to a certain position.
     * It must verify that the destination is not a wall or an ally.
     * But also that he has indeed the right move.
     * All roles except bomb, flag and wall can be moved one square,
     * except the scout, who can move one square in one direction.
     * But he can't jump over several enemy counters.
     *
     * @param destiPos The destination position of the pawn.
     */
    virtual void movePawn(const Position destiPos) = 0;

    /**
     * @brief movePawnGui a modified version of the method movePawn for the GUI.
     * @param destiPos the destination.
     */
    virtual void movePawnGui(const Position destiPos) = 0;

    /**
     * @brief isCorrectMove check if the destination is move that is correct.
     * @param destiPos the destination where the player want to move the pawn to.
     * @return true if the player can else return false.
     */
    virtual bool isCorrectMove(const Position destiPos) = 0;

    /**
     * @brief isSamePosition check if the picked position is the same as the destination position.
     * @param destiPos the destination's position.
     */
    virtual void isSamePosition(const Position destiPos) = 0;

    /**
     * @brief isGameOver checks if the game is over.
     *
     * The result of the game is for the current player.
     * So that means if the current player lose, it's the other
     * who wins.
     */
    virtual void isGameOver() = 0;

    /**
     * @brief getBoardSize Get the size of the board.
     * @return the size of the board.
     */
    virtual int getBoardSideSize() const= 0;

    /**
     * @brief getPlayerTeam Gets the current player.
     *
     * @param player the player's number.
     * @return the curren player team.
     */
    virtual Team getPlayerTeam(const int player)const = 0;

    /**
     * @brief getCurrentPlayer get the current player's number
     * @return the team of the current player.
     */
    virtual Team getCurrentPlayer() const= 0;

    /**
     * @brief getNumberOfPlayer get the number of player in the game.
     * @return the number of players in the game.
     */
    virtual int getNumberOfPlayer() const= 0;

    /**
     * @brief getState Get the current state size
     * @return the current state size
     */
    virtual State getState()const = 0;

    /**
     * @brief getWinner Get the winner of the game
     * @return the winner of the game
     */
    virtual Team getWinner() const = 0;

    /**
     * @brief numberOfDeadSoldier get the total of dead pawn in the graveyard of a specific player.
     * @param playerNumber the player number.
     * @return the number of dead pawn in the graveyard.
     */
    virtual int numberOfDeadSoldier(int playerNumber) = 0;

    /**
     * @brief getPawn get the pawn at a certain position
     * @param pos The position where to recover the pawn
     * @return the pawn at a certain position
     */
    virtual const Pawn getPawn(const Position pos) = 0;

    /**
     * @brief getGameResult Gets the result of the game.
     * So that means if the current player win, lose or is it a
     * equality.
     * @return the result of the game.
     */
    virtual GameResult getGameResult() const = 0;

    /**
     * @brief getDuelResult return the result of a duel.
     *
     * 1 means a victory, -1 a deafeat, 0 an egality and 2 means no duel happend.
     *
     * @return the result of a duel.
     */
    virtual int getDuelResult() const = 0;

    /**
     * @brief getPickedPosition get the position of the pawn that is picked by the player.
     * @return the positon of the picked pawn.
     */
    virtual Position getPickedPosition()const = 0;

    /**
     * @brief getDestinationPosition get the position of the pawn that is picked by the player.
     * @return the destination of the pawn.
     */
    virtual Position getDestinationPosition() const = 0 ;

    /**
     * @brief getRoleOfDeadPawn get the role of a dead pawn in the graveyard of a specific player.
     * @param playerNumber the player number.
     * @param index the position of the dead pawn in the graveyard.
     * @return the role of the dead pawn.
     */
    virtual Role getRoleOfDeadPawn(int playerNumber, int index) const = 0;

    /**
     * @brief deadPawnToString get the symbole of the pawn in the graveyard of a specific player.
     * @param pos the position of the dead pawn in the graveyard
     * @param playerNumber the player number.
     * @return the symbole of the dead pawn.
     */
    virtual const std::string deadPawnToString(int index, int playerNumber) = 0;

    /**
     * @brief getLastDeadPawn get the last dead pawn of the given player's number.
     * @param playerNumber the plyaer number.
     * @return the role and the team of the pawn.
     */
    virtual std::pair<Role, Team> getLastDeadPawn(int playerNumber) const = 0;
};

#endif // MODEL_H
