#include <algorithm>
#include "Game.h"

Game::Game() : _deck{Deck{}}, _gameResult{GameResult::CONTINUE},
    _players{}, _lastPawnPlayed{}, _state{State::NOT_STARTED},
    _currentPlayer{0},
    _pickedPosition{Position{}}, _destinationPosition{Position{}},
    _duelResult{2}, _observers{}
{}

void Game::start(bool isEasyMode)
{
    this->_board = Board{};
    this->_state = State::SET_UP;
    createPlayer();
    this->_easyMode = isEasyMode;
    notifyObservers();
}

void Game::restart(bool isEasyMode)
{
    this->_board = Board{};
    this->_state = State::SET_UP;
    this->_gameResult = GameResult::CONTINUE;
    this->_easyMode = isEasyMode;
    this->_duelResult = 2;
    this->_currentPlayer = 0;
    this->_destinationPosition = Position{};
    this->_pickedPosition = Position{};
    for (int i{}; i < (int)this->_lastPawnPlayed.size(); i++)
        this->_lastPawnPlayed.at(i) = Position{};
    this->_players.at(0).clean();
    this->_players.at(1).clean();
    notifyObservers();
}

Team Game::getPlayerTeam(int player) const
{
    return _players.at(player).getTeam();
}

void Game::createPlayer()
{
    Player player1 {Team::BLUE};
    Player player2 {Team::RED};
    this->_players = {player1, player2};
    lastPawnPlayInitialisation();
}

void Game::lastPawnPlayInitialisation()
{
    for (int i {}; i < (int)this->_players.size(); i++)
    {
        this->_lastPawnPlayed.push_back(Position{});
    }
}

void Game::generateDeck()
{
    this->_deck.generateDeck(this->_players.at(
                                 this->_currentPlayer).getTeam());
}

const Pawn Game::getPawnInDeck() const
{
    return this->_deck.getPawnInDeck();
}

const Pawn Game::getPawnInDeckAt(int index) const
{
    return this->_deck.getPawnInDeckAt(index);
}

int Game::getDeckSize() const
{
    return this->_deck.numberOfPawn();
}

void Game::putPawn(Pawn pawn, const Position pos)
{
    this->_board.putPawn(pawn, pos);
    this->_deck.removePawnInDeck();
    notifyObservers();
    if (this->_deck.numberOfPawn() == 0 &&
            this->_currentPlayer == (int)this->_players.size() - 1)
    {
        this->_state = END_SET_UP;
        notifyObservers();
        this->_state = State::PICK_PAWN;
        nextPlayer();
        notifyObservers();
    }
    else if (this->_deck.numberOfPawn() == 0)
    {
        nextPlayer();
        notifyObservers();
    }
}

bool Game::canBePut(const Pawn & pawn, const Position pos)
{
    return this->_board.canBePut(pawn, pos);
}

void Game::putPawnAt(const Position pos, const int index)
{
    Pawn p = this->_deck.removePawnInDeckAt(index);
    this->_board.putPawn(p, pos);

    if (this->_deck.numberOfPawn() == 0 &&
            this->_currentPlayer == (int)this->_players.size() - 1)
    {
        this->_state = END_SET_UP;
        notifyObservers();
        this->_state = State::PICK_PAWN;
        nextPlayer();
    }
    else if (this->_deck.numberOfPawn() == 0)
    {
        nextPlayer();
    }
}

void Game::loadFile(std::string path)
{
    this->_board.loadFile(path,
                          this->_players.at(this->_currentPlayer).getTeam());
    this->_state = END_FILE_SET_UP;
    notifyObservers();
    this->_state = SET_UP;
    if (this->_currentPlayer == (int)this->_players.size() - 1)
    {
        this->_state = END_SET_UP;
        notifyObservers();
        this->_state = State::PICK_PAWN;
    }
    nextPlayer();
}

void Game::nextPlayer()
{
    this->_currentPlayer = (this->_currentPlayer + 1) % 2;
    notifyObservers();
    if (this->_state == State::END_TURN)
        this->_state = State::PICK_PAWN;
}

void Game::canBePicked(const Position pos)
{
    if (this->_board.canBePicked(pos, this->_players.at(this->_currentPlayer).getTeam()))
    {
        this->_pickedPosition = pos;
        this->_state = State::MOVE_PAWN;
    }
}

bool Game::canBePick(const Position pos)
{
    if (this->_board.canBePick(pos, this->_players.at(this->_currentPlayer).getTeam()))
    {
        this->_pickedPosition = pos;
        this->_state = State::MOVE_PAWN;
        return true;
    }
    return false;
}

void Game::movePawn(const Position destiPos)
{
    if (isSamePositionPicked(destiPos))
    {
        this->_state = State::PICK_PAWN;
    }
    else if (this->_board.isCorrectMove(this->_pickedPosition, destiPos))
    {
        this->_destinationPosition = destiPos; // save the wanted destination
        if (this->_board.isThereEnemy(destiPos,
                                      this->_players.at(this->_currentPlayer).getTeam()))
        {
            duelPhase(destiPos);
        }
        else
        {
            noDuelPhase(destiPos);
        }

        if (this->_state != State::GAME_OVER)
        {
            this->_state = State::END_TURN;
        }
    }
}

void Game::movePawnGui(const Position destiPos)
{
    this->_destinationPosition = destiPos; // save the wanted destination

    if (this->_board.isThereEnemy(destiPos,
                                  this->_players.at(this->_currentPlayer).getTeam()))
    {
        duelPhaseGui(destiPos);
    }
    else
    {
        noDuelPhase(destiPos);
    }

    if (this->_state != State::GAME_OVER)
    {
        this->_state = State::END_TURN;
        nextPlayer();
    }
}

bool Game::isCorrectMove(const Position destiPos)
{
    return this->_board.isCorrectMove(this->_pickedPosition, destiPos);
}

void Game::isSamePosition(const Position destiPos)
{
    if(isSamePositionPicked(destiPos)){
        this->_state = State::PICK_PAWN;
    }
}

bool Game::isSamePositionPicked(const Position & destiPos)
{
    return this->_pickedPosition == destiPos;
}

void Game::noDuelPhase(const Position & destiPos)
{
    if (isSamePawnPlayed())
    {
        Pawn & pawn {this->_board.getPawn(this->_pickedPosition)};
        pawn.addMove(destiPos);
    }
    else
    {
        Pawn & previousPawn {this->_board.getPawn(this->_lastPawnPlayed.at(this->_currentPlayer))};
        if (previousPawn.getTeam() == this->_players.at(
                    this->_currentPlayer).getTeam())
        {
            previousPawn.clearMove();
        }
        Pawn & pawn {this->_board.getPawn(this->_pickedPosition)};
        pawn.addMove(destiPos);
    }
    this->_lastPawnPlayed.at(this->_currentPlayer) = destiPos;
    this->_board.move(this->_pickedPosition, destiPos);
    this->_duelResult = 2;
    notifyObservers();
}


void Game::duelPhase(const Position & destiPos)
{
    this->_board.getPawn(this->_pickedPosition).reveal();
    this->_board.getPawn(destiPos).reveal();
    notifyObservers();
    this->_duelResult = {this->_board.pawnDuel(this->_pickedPosition, destiPos)};
    if (this->_duelResult == 1)
    {
        dualWin(destiPos);
    }
    else if (this->_duelResult == -1)
    {
        dualDefeat(destiPos);
    }
    else
    {
        dualEquality(destiPos);
    }
    isGameOver();
    if (this->_gameResult != GameResult::CONTINUE)
    {
        this->_state = State::GAME_OVER;
    }
    notifyObservers();
}

void Game::duelPhaseGui(const Position &destiPos)
{
    this->_board.getPawn(this->_pickedPosition).reveal();

    this->_board.getPawn(destiPos).reveal();

    this->_duelResult = {this->_board.pawnDuel(this->_pickedPosition, destiPos)};

    if (this->_duelResult == 1)
    {
        dualWin(destiPos);
    }
    else if (this->_duelResult == -1)
    {
        dualDefeat(destiPos);
    }
    else
    {
        dualEquality(destiPos);
    }
    isGameOver();
    if (this->_gameResult != GameResult::CONTINUE)
    {
        this->_state = State::GAME_OVER;
    }
    notifyObservers();
}

void Game::dualWin(const Position & destiPos){
    if (!this->_easyMode)
    {
        this->_board.getPawn(this->_pickedPosition).hide();
    }
    Pawn pawn {this->_board.removePawn(destiPos)};
    this->_players.at((this->_currentPlayer + 1) % 2).addDeadPawn(pawn);
    Pawn & currentPlayerPawn {this->_board.getPawn(this->_pickedPosition)};
    currentPlayerPawn.addMove(destiPos);
    this->_lastPawnPlayed.at(this->_currentPlayer) = destiPos;
    this->_board.move(this->_pickedPosition, destiPos);
}

void Game::dualDefeat(const Position & destiPos){
    if (!this->_easyMode)
    {
        this->_board.getPawn(destiPos).hide();
    }
    Pawn pawn {this->_board.removePawn(this->_pickedPosition)};
    this->_players.at(this->_currentPlayer).addDeadPawn(pawn);
}

void Game::dualEquality(const Position & destiPos){
    Pawn alliedPawn {this->_board.removePawn(this->_pickedPosition)};
    this->_players.at(this->_currentPlayer).addDeadPawn(alliedPawn);
    Pawn ennemiePawn {this->_board.removePawn(destiPos)};
    this->_players.at((this->_currentPlayer + 1) % 2).addDeadPawn(
                ennemiePawn);
}

bool Game::isSamePawnPlayed()
{
    return this->_lastPawnPlayed.at(this->_currentPlayer) ==
           this->_pickedPosition;
}

void Game::isGameOver()
{
    if (this->_players.at(this->_currentPlayer).isAllSoldierDead() &&
            this->_players.at((this->_currentPlayer + 1) % 2).isAllSoldierDead())
    {
        this->_gameResult = GameResult::EGALITY;
    }
    else if (this->_players.at((this->_currentPlayer + 1) %
                               2).isAllSoldierDead() ||
             this->_players.at((this->_currentPlayer + 1) % 2).isFlagCaptured())
    {
        this->_gameResult = GameResult::VICTORY;
    }
    else if (this->_players.at(this->_currentPlayer).isAllSoldierDead())
    {
        this->_gameResult = GameResult::DEFEAT;
    }
}

int Game::getBoardSideSize() const
{
    return this->_board.getSize();
}

Team Game::getCurrentPlayer() const
{
    return this->_players.at(this->_currentPlayer).getTeam();
}

int Game::getNumberOfPlayer() const
{
    return this->_players.size();
}

State Game::getState() const
{
    return this->_state;
}

Team Game::getWinner() const
{
    if (this->_gameResult == GameResult::VICTORY)
    {
        return this->_players.at(this->_currentPlayer).getTeam();
    }
    else
    {
        return this->_players.at((this->_currentPlayer + 1) % 2).getTeam();
    }
}

const Pawn Game::getPawn(const Position pos)
{
    return this->_board.getPawn(pos);
}

GameResult Game::getGameResult() const
{
    return this->_gameResult;
}

Position Game::getPickedPosition() const
{
    return this->_pickedPosition;
}

Position Game::getDestinationPosition() const
{
    return this->_destinationPosition;
}

int Game::getDuelResult() const
{
    return this->_duelResult;
}

void Game::addObserver(Observer * observer)
{
    _observers.push_back(observer);
}

void Game::removeObserver(Observer * observer)
{
    int offset = 0;
        for(; offset < (int) this->_observers.size() && observer != this->_observers.at(offset); offset++);
        _observers.erase(this->_observers.begin() + offset);
}

void Game::notifyObservers()
{
    for (Observer  * o : _observers)
    {
        o->updateView(this);
    }
}

int Game::numberOfDeadSoldier(int playerNumber)
{
    return this->_players.at(playerNumber).numberOfDeath();

}

const std::string Game::deadPawnToString(int pos, int playerNumber)
{
    return this->_players.at(playerNumber).toString(pos);
}

Role Game::getRoleOfDeadPawn(int playerNumber, int pos) const
{
    return this->_players.at(playerNumber).getRoleOfDeadPawn(pos);
}

std::pair<Role, Team> Game::getLastDeadPawn(int playerNumber) const
{
    return this->_players.at(playerNumber).getLastDeadPawn();
}
