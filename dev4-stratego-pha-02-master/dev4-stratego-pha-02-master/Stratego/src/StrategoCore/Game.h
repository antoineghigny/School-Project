#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Deck.h"
#include "Player.h"
#include "Model.h"
#include "map"
#include "Observable.h"
/**
 * @brief The Game class Class that will have methods
 * that will allow to play the game.
 */
class Game : public Model, public Observable
{

    Board _board;
    Deck _deck;
    GameResult _gameResult;
    std::vector<Player> _players;
    std::vector<Position> _lastPawnPlayed; // to know the previous pawn played for each player
    State _state;
    int _currentPlayer;
    bool _easyMode; // this attribut indicate if a pawn must stay permanently visible after he has been revealed
    Position _pickedPosition;
    Position _destinationPosition;
    int _duelResult;
    std::vector<Observer *> _observers;

    /**
     * @brief createPlayer create the players of the game.
     */
    void createPlayer();

    /**
     * @brief lastPawnPlayInitialisation fill in the vector as many times as there are players.
     */
    void lastPawnPlayInitialisation();

    /**
     * @brief isSamePositionPick check if the arrival position of the pawn is the same as
     * the source position.
     * @param pos the arrival destination of the pawn.
     */
    bool isSamePositionPicked(const Position & destiPos);

    /**
     * @brief isSamePawnPlayed check if the selected pawn is the same as the previous
     * one played by the current player.
     * @return true if it's the same pawn that is played else return false.
     */
    bool isSamePawnPlayed();

    /**
     * @brief noDuelPhase phase of the game where there is no duel.
     *
     * When there is no duel, the pawn will simply move. If the same pawn
     * is played, the destination will be to the historic of the pawn"s movement.
     * Also changes the state of the game to PICK_PAWN and moves to the next player.
     *
     * @param destiPos the arrival position of the selected pawn.
     */
    void noDuelPhase(const Position & destiPos);

    /**
     * @brief duelPhase phase of the game where there is duel.
     *
     * When there is a duel, check who win. Functions are called
     * depending on the outcome of the duel.
     *
     * @param destiPos the arrival position of the selected pawn.
     */
    void duelPhase(const Position & destiPos);

    /**
     * @brief duelPhaseGui a adapted version of the method duelPhase for the GUI.
     * @param destiPos the destination position.
     */
    void duelPhaseGui(const Position & destiPos);

    /**
     * @brief dualWin function call when a duel is win.
     *
     * When the duel is win, the ennemie pawn is remove from the board and replace by the winner of the duel.
     *
     * @param destiPos the destination of the pawn that has been attacked.
     */
    void dualWin(const Position & destiPos);

    /**
     * @brief dualDefeat function call when a duel is lose.
     *
     * When the duel is lose, the attacker pawn is remove from the board.
     *
     * @param destiPos the destination of the pawn that has been attacked.
     */
    void dualDefeat(const Position & destiPos);

    /**
     * @brief dualEquality function call when a duel is an equality.
     *
     * When there is no winner or loser, both pawn are remove from the board.
     *
     * @param destiPos the destination of the pawn that has been attacked.
     */
    void dualEquality(const Position & destiPos);

  public:

    /**
     * @brief Game Constructor of the class.
     */
    Game();

    void start(bool isEasyMode) override;

    void restart(bool isEasyMode) override;

    void generateDeck() override;

    bool canBePut(const Pawn & pawn, const Position pos) override;

    void putPawn(Pawn pawn, const Position pos) override;

    void putPawnAt(const Position pos, const int index) override;

    void loadFile(std::string path) override;

    const Pawn getPawnInDeck() const override;

    const Pawn getPawnInDeckAt(int index) const;

    int getDeckSize() const override;

    void nextPlayer() override;

    void canBePicked(const Position pos) override;

    bool canBePick(const Position pos) override;

    void movePawn(const Position destiPos) override;

    void movePawnGui(const Position destiPos) override;

    bool isCorrectMove(const Position destiPos) override;

    void isSamePosition(const Position destiPos) override;

    void isGameOver() override;

    int getBoardSideSize() const override;

    int getNumberOfPlayer() const override;

    Team getCurrentPlayer() const override;

    State getState() const override;

    Team getWinner() const override;

    const Pawn getPawn(const Position pos) override;

    GameResult getGameResult() const override;

    Position getPickedPosition() const override;

    Position getDestinationPosition() const override;

    int getDuelResult() const override;

    Team getPlayerTeam(int player) const override;

    void addObserver(Observer * observer) override;

    void removeObserver(Observer * observer) override;

    void notifyObservers() override;

    int numberOfDeadSoldier(int playerNumber) override;

    const std::string deadPawnToString(int index, int playerNumber) override;

    Role getRoleOfDeadPawn(int playerNumber, int pos) const override;

    std::pair<Role, Team> getLastDeadPawn(int playerNumber) const override;

};

#endif // GAME_H
