#include "controllergui.h"
#include <Game.h>
#include <mainwindow.h>

#include <Position.h>
#include <Team.h>


ControllerGui::ControllerGui():
    _game{}
{

}

void ControllerGui::addObserver(Observer * o)
{
    _game.addObserver(o);
}

void ControllerGui::loadFile(const std::string path)
{
    try
    {
        _game.loadFile(path);
    }
    catch (std::invalid_argument & exception)
    {
        std::cout << "catch exception in loadfile" << std::endl;
    }
}

Team ControllerGui::getCurrentPlayer() const
{
    return this->_game.getCurrentPlayer();
}

void ControllerGui::isSamePosition(const Position pos)
{
    _game.isSamePosition(pos);
}

bool ControllerGui::isCorrectMove(const Position pos)
{
    try
    {
        return _game.isCorrectMove(pos);
    }
    catch (std::invalid_argument & exception)
    {
        return false;
    }

}

void ControllerGui::movePawnGui(const Position pos)
{
    try
    {
        _game.movePawnGui(pos);
    }
    catch (std::out_of_range & exception)
    {
        std::cout << "catch out_of_range" << std::endl;
    }
    catch (std::invalid_argument & exception)
    {
        std::cout << "catch invalid_argument" << std::endl;
     }
}

Position ControllerGui::getDestinationPosition() const
{
    return _game.getDestinationPosition();
}

Pawn ControllerGui::getPawnInDeck() const
{
    return _game.getPawnInDeck();
}

Pawn ControllerGui::getPawnInDeckAt(const int index) const
{
    return _game.getPawnInDeckAt(index);
}

void ControllerGui::putPawn(const Pawn pawn, const int x,  const int y)
{
    auto position = Position(x, y);
    _game.putPawn(pawn, position);
}

void ControllerGui::putPawnAt(const int x, const int y, const int index)
{
    auto position = Position(x, y);
    _game.putPawnAt(position, index);
}

Team ControllerGui::getWinner() const
{
    return _game.getWinner();
}

bool ControllerGui::canBePut(const Pawn pawn, const int x, const int y)
{
    return _game.canBePut(pawn, Position(x, y));
}

bool ControllerGui::canBeMoved(const int x, const int y)
{
    return _game.canBePick(Position(x, y));
}

Role ControllerGui::getDeadPawnRole(const int playerNumber, const int index) const
{
    return _game.getRoleOfDeadPawn(playerNumber, index);
}

void ControllerGui::generateDeck()
{
    this->_game.generateDeck();
}

int ControllerGui::getDeckSize() const
{
    return _game.getDeckSize();
}

int ControllerGui::getBoardSize() const
{
    return _game.getBoardSideSize();
}

int ControllerGui::numberOfDeadSoldier(const int playerNumber)
{
    return _game.numberOfDeadSoldier(playerNumber);
}

std::string ControllerGui::deadPawnToString(const int pos, const int playerNumber)
{
    return _game.deadPawnToString(pos, playerNumber);
}

Pawn ControllerGui::getPawnAtPos(const Position position)
{
    return _game.getPawn(position);
}

std::pair<Role, Team> ControllerGui::getLastDeadPawn(const int playerNumber)
{
    return _game.getLastDeadPawn(playerNumber);
}

State ControllerGui::getState() const
{
    return _game.getState();
}

void ControllerGui::startGame(const bool easyMode)
{
    if(_game.getState() == NOT_STARTED)
    {
        _game.start(easyMode);
    }else if(_game.getState() == GAME_OVER)
    {
        _game.restart(easyMode);
    }
}

GameResult ControllerGui::getGameResult() const
{
    return this->_game.getGameResult();
}

