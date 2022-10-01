#include "Controller.h"
#include <Game.h>
#include <ViewConsole.h>
#include <Position.h>
#include <Team.h>
#include <Pawn.h>

Controller::Controller(): _game{}, _viewConsole{this}
{
    this->_game.addObserver(&_viewConsole);
}


void Controller::loadFile(std::string path)
{
    _game.loadFile(path);
}

Team Controller::getCurrentPlayer()
{
    return this->_game.getCurrentPlayer();
}

void Controller::movePawn(int x, int y)
{
    _game.movePawn(Position(x, y));
}

Pawn Controller::getPawnInDeck()
{
    return _game.getPawnInDeck();
}

void Controller::putPawn(Pawn pawn, int x, int y)
{
    auto position = Position(x, y);
    _game.putPawn(pawn, position);
}

Team Controller::getWinner()
{
    return _game.getWinner();
}

void Controller::canBeMoved(int x, int y)
{
    _game.canBePicked(Position(x, y));
}

Role Controller::getDeadPawnRole(int playerNumber, int index)
{
    return _game.getRoleOfDeadPawn(playerNumber, index);
}

void Controller::generateDeck()
{
    this->_game.generateDeck();
}

int Controller::getDeckSize()
{
    return _game.getDeckSize();
}

int Controller::getBoardSize()
{
    return _game.getBoardSideSize();
}

int Controller::numberOfDeadSoldier(int playerNumber)
{
    return _game.numberOfDeadSoldier(playerNumber);
}

std::string Controller::deadPawnToString(int pos, int playerNumber)
{
    return _game.deadPawnToString(pos, playerNumber);
}

Pawn Controller::getPawn(Position position)
{
    return _game.getPawn(position);
}

void Controller::checkInputGameMode(const std::string input)
{
    if (input == "Y")
        _game.start(true);
    else if (input == "N")
        _game.start(false);
    else if (input == "help")
        _viewConsole.sendHelp();
    else
        this->_viewConsole.displayErrorMessage("Please enter a correct input.");
}

void Controller::play()
{
    this->_viewConsole.sendWelcomeMeesage();
    while (true)
    {
        switch (_game.getState())
        {
            case NOT_STARTED:
                {
                    std::string modeInput = this->_viewConsole.askGameMode();
                    checkInputGameMode(modeInput);
                    break;
                }
            case SET_UP:
                {
                    std::string input = _viewConsole.askPlacementChoice();
                    if (input == "Y") _viewConsole.askFile();
                    else
                    {
                        _game.generateDeck();
                        _viewConsole.manuelPlacement();
                    }
                    break;
                }
            case PICK_PAWN:
                {
                    _viewConsole.pickPawn();
                    break;
                }
            case MOVE_PAWN:
                {
                    _viewConsole.movePawn();
                    break;
                }
            case END_TURN:
                {
                    this->_game.nextPlayer();
                    break;
                }
            case GAME_OVER:
                char input = _viewConsole.askRestart();
                if (input == 'Y')
                {
                    std::string modeInput = this->_viewConsole.askGameMode();
                    checkInputGameMode(modeInput);
                }
                else
                {
                    this->_viewConsole.sendGoodbyeMessage();
                    exit(0);
                }
        }
    }
}

