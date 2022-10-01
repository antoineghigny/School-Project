#include "ViewConsole.h"
#include <regex>
#include <iostream>
#include "Controller.h"
#include <stdexcept>
#include <thread>

using namespace std;

const int blue {9};
const int red {12};
const int normal {15};
const int wall {8};
const int gold {14};

#define RED  "\x1B[31m"
#define BLUE  "\x1B[34m"
#define GREY "\033[1;37m"
#define NORMAL  "\x1B[0m"
#define GOLD  "\x1B[33m"

ViewConsole::ViewConsole(Controller * controller): _controller{controller}
{
    IFWIN32(_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);)
}

std::pair<char, char> ViewConsole::verifString()
{
    string input;
    cin >> input;

    while (!(regex_match(input,
                         regex("(?:[A-Ja-j])((?:1[0])|[1-9])\\s*(?!.(?:1[3-9])*)"))))
    {
        cout << "You have not entered your data correctly. Please try again."
             << endl;
        cin.clear();
        cin.ignore(255, '\n');
        cin >> input;
    }
    std::string s = input.substr(1);
    for (auto i : s)
        if (!std::isdigit(i))
            throw std::invalid_argument("The second value of the position must be a number.");
    int secondValue = std::stoi(s);
    std::pair<int, int> coordinates = make_pair(input[0], secondValue);

    return coordinates;
}

void ViewConsole::sendWelcomeMeesage()
{
    std::cout << "Welcome to the console version of Stratego dear user."
              << std::endl;
}

void ViewConsole::sendGoodbyeMessage()
{
    std::cout << "Goodbye dear user." << std::endl;
}

std::string ViewConsole::askGameMode()
{
    std::string input;
    std::cout <<
              "If you want an explication on how the game works type 'help'" <<
              std::endl;
    std::cout << "Do you want to play the game in easy mode ? [Y/N] : " <<
              std::endl;
    cin >> input;
    return input;
}

void ViewConsole::sendHelp()
{
    cout << "Stratego is played with 2 players, each player has 40 pawns."
         << endl;

    cout <<
         "At the start of the game, each player arranges his pieces as he sees fit in his first four rows."
         << endl;

    cout << "Each player moves a piece one square per turn: left, right, forward or backward."
         << endl;

    cout << "An attack occurs when the player moves his piece onto a square already occupied by the opponent.\n"
         "Each player then shows his piece to the opponent.\n"
         "The strongest piece remains in play, the other is eliminated; in case of a tie, both are eliminated.\n"
         << endl;

    cout << "Here are the coins ranked from strongest to weakest (strength in parentheses) :"
         << endl;

    cout << "the Marshal (10), 1 per player, \n "
         "the General (9), 1 per player \n"
         "the Colonels (8), 2 per player, \n"
         "Commanders (7), 3 per player,\n "
         "Captains (6), 4 per player, \n "
         "Lieutenants (5), 4 per player, \n "
         "Sergeants (4), 4 per player,  \n"
         "Minesweepers (3), 5 per player, \n "
         "Scouts (2), 8 per player, \n"
         "the Spy (1), 1 per player, \n"
         "the Flag (F), 1 per player \n" << endl;

    cout << "Added to these pieces are the Bombs (6 per player). Neither the Bombs nor the Flag can move."
         << endl;

    cout << "The objectif of the game is to capture the opponent's flag or to eliminate all the pawns of your opponent's."
         << endl;
}

std::string ViewConsole::askPlacementChoice()
{
    std::cin.clear();
    cout << "Player " << getPlayerTeam(_controller->getCurrentPlayer()) <<
         ", do you want to import a text file including your Board? [Y/N]"
         << endl;
    std::string input;
    while (!(std::cin >> input) || (input != "Y" && input != "N"))
    {
        std::cout << "Invalid input. Please retry." << input << std::endl;
        std::cin.clear();
        std::cin.ignore(255, '\n');
    }
    return input;
}

char ViewConsole::askRestart()
{
    std::cin.clear();
    cout << "Do you want to play another game ? [Y/N]" << endl;
    char input;
    while (!(std::cin >> input) || (input != 'Y' && input != 'N'))
    {
        std::cout << "Invalid input. Please retry." << input << std::endl;
        std::cin.clear();
        std::cin.ignore(255, '\n');
    }
    return input;
}


void ViewConsole::manuelPlacement()
{
    cout << "Please place your pawns 1 by 1 indicating for each pawn, its position in X and Y (ex : A10, B3, C5, F8)."
         << endl;
    if (this->_controller->getCurrentPlayer() == 0)
        std::cout <<
                  "Your side of the board is between the row 7 (included) and 10." <<
                  std::endl;
    else
        std::cout <<
                  "Your side of the board is between the row 1 and 4 (included)." <<
                  std::endl;

    int numberOfPawn {_controller->getDeckSize()};

    for (int i = 0; i < numberOfPawn; i++)
    {
        // ah merde je me pose la question, vu
        cout << "Pawn : " << (i + 1) << "/" << numberOfPawn << " : " <<
             _controller->getPawnInDeck().toString() << endl;

        bool input = true;
        while (input)
        {
            try
            {
                cout << "Where do you want to put the pawn ? : ";
                pair<int, int> position = verifString();

                int y = (position.first % 32);
                int x = (position.second);
                _controller->putPawn(_controller->getPawnInDeck(), x, y);
                input = false;
            }
            catch (std::invalid_argument & exception)
            {
                displayErrorMessage(exception.what());
            }
        }

    }
    cout << "You have placed all of your pawns." << endl;
}

void ViewConsole::pickPawn()
{
    bool input = true;
    while (input)
    {
        try
        {
            cout << "Which pawn do you want to pick ? ";
            auto pos = verifString();
            int y = (pos.first % 32);
            int x = (pos.second);
            _controller->canBeMoved(x, y);
            input = false;
        }
        catch (std::invalid_argument & exception)
        {
            displayErrorMessage(exception.what());
        }
    }
}

void ViewConsole::movePawn()
{
    bool input = true;
    while (input)
    {
        try
        {
            cout << "Where do you want to move the pawn ? ";
            auto pos = verifString();
            int y = (pos.first % 32);
            int x = (pos.second);
            _controller->movePawn(x, y);
            input = false;
        }
        catch (std::invalid_argument & exception)
        {
            displayErrorMessage(exception.what());
        }
    }
}

void ViewConsole::printGraveyardInContext(int playerNumber)
{
#ifdef _WIN32
    if (playerNumber == 1)
    {
        SetConsoleTextAttribute(_hConsole, red);
        cout << "       Graveyard RED";
    }
    else
    {
        SetConsoleTextAttribute(_hConsole, blue);
        cout << "       Graveyard BLUE";
    }
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    (playerNumber == 1) ? cout << RED "       Graveyard" NORMAL :
                               cout << BLUE "      Graveyard" NORMAL;
#endif
    cout << endl;
}

void ViewConsole::askFile()
{
    string path;
    bool input = true;
    while (input)
    {
        cout << "Please indicate the absolute path to your text file (ex: C:/user/antoi/board.txt) : ";
        std::cin >> path;
        try
        {
            _controller->loadFile(path);
            input = false;
        }
        catch (std::invalid_argument & exception)
        {
            displayErrorMessage(exception.what());
        }
    }

    cout << "You have placed all of your pawns." << endl;
}

void ViewConsole::displayCurrentPlayer()
{
    cout << "----------  ";
#ifdef _WIN32
    (_controller->getCurrentPlayer() == 0) ? SetConsoleTextAttribute(
        _hConsole, blue) : SetConsoleTextAttribute(_hConsole, red);
    cout << "PLAYER " << getPlayerTeam(_controller->getCurrentPlayer());
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    (_controller->getCurrentPlayer() == 0) ? cout << BLUE "PLAYER BLUE"
            NORMAL : cout << RED "PLAYER RED" NORMAL;
#endif
    (_controller->getCurrentPlayer() == 0) ? cout << "  ----------" <<
            endl : cout << "  -----------" << endl;
}

void ViewConsole::printInContext(const Position p)
{
#ifdef _WIN32
    (_controller->getPawn(p).getTeam() == 0) ? SetConsoleTextAttribute(
        _hConsole, blue) : SetConsoleTextAttribute(_hConsole, red);
    (_controller->getPawn(p).getRole() == 10) ?
    cout << _controller->getPawn(p).getRole() << " "
         : cout << _controller->getPawn(p).toString() << "  ";
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    colorItems(_controller->getPawn(p).getRole(),
               _controller->getPawn(p).getTeam());
#endif
}

void ViewConsole::printBoard()
{
    displayCurrentPlayer();
    cout << "    ";
    for (auto letter {'A'}; letter <= 'J'; letter++)
    {
        cout << letter << "  ";
    }
    cout << endl << "----------------------------------- ";

    printGraveyardInContext(_controller->getCurrentPlayer());
    for (auto i {1}; i <= _controller->getBoardSize(); i++)
    {
        (i <= 9) ? cout << " " << i : cout << i;
        cout << "|";
        for (auto j {1}; j <= _controller->getBoardSize(); j++)
        {
            const Position p {i, j};
            if (p.getY() == 1)
            {
                cout << " ";
            }

            if (_controller->getPawn(p).getRole() == EMPTY)
            {
                cout << "   ";
            }
            else if (_controller->getPawn(p).getRole() == WALL)
            {
#ifdef _WIN32
                SetConsoleTextAttribute(_hConsole, wall);
                cout << "#  ";
                SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
                cout << GREY "#  " NORMAL;
#endif
            }
            else
            {
                if (_controller->getPawn(p).getTeam() ==
                        _controller->getCurrentPlayer() ||
                        _controller->getPawn(p).isVisible() )
                {
                    printInContext(p);
                }
                else
                {
#ifdef _WIN32
                    (_controller->getPawn(p).getTeam() == 0 ) ? SetConsoleTextAttribute(
                        _hConsole, blue) : SetConsoleTextAttribute(_hConsole, red);
                    cout << "X  ";
                    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
                    (_controller->getPawn(p).getTeam() == 0) ? cout << BLUE "X  "
                            NORMAL : cout << RED "X  " NORMAL;
#endif
                }
            }
        }
        cout << "|" << (i);
        if (i <= 4)
        {
            printGraveYard(i - 1, _controller->getCurrentPlayer());
        }
        else if (i == 6)
        {
            int team {};
            (_controller->getCurrentPlayer() == 0) ? team = 1 : team = 0;
            printGraveyardInContext(team);
        }
        else if (i > 6)
        {
            printGraveYardBelow(i - 1, _controller->getCurrentPlayer());
        }
        else
        {
            cout << endl;
        }
    }

    cout << "-----------------------------------" << endl;
    cout << "    ";
    for (auto letter {'A'}; letter <= 'J'; letter++)
    {
        cout << letter << "  ";
    }
    cout << endl << endl;
}

void ViewConsole::printGraveYard(int index,
                                 int playerNumber)
{
    cout << "  | ";
    if (index == 1) index = 10;
    else if (index > 1) index *= 10;

#ifdef _WIN32
    if (playerNumber == 0)
    {
        SetConsoleTextAttribute(_hConsole, blue);
        displayForPlayer(index, index, 0);
    }
    else
    {
        SetConsoleTextAttribute(_hConsole, red);
        displayForPlayer(index, index, 1);
    }
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    (playerNumber == 0) ? displayForPlayer(index, index,
                                           0) : displayForPlayer(index, index, 1);
#endif
    cout << endl;
}

void ViewConsole::printGraveYardBelow(int index,
                                      int playerNumber)
{
    (index >= 9) ? cout << " | " : cout << "  | ";
    int tmp = index - 6;
    if (tmp == 1) tmp = 10;
    else if (tmp > 1) tmp *= 10;

#ifdef _WIN32
    if (playerNumber == 0)
    {
        SetConsoleTextAttribute(_hConsole, red);
        displayForPlayer(index, tmp, 1);
    }
    else
    {
        SetConsoleTextAttribute(_hConsole, blue);
        displayForPlayer(index, tmp, 0);
    }
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    (playerNumber == 0) ? displayForPlayer(index, tmp,
                                           1) : displayForPlayer(index, tmp, 0);
#endif
    cout << endl;
}

void ViewConsole::displayForPlayer(int index, int offset,
                                   int playerNumber)
{
    while (offset < _controller->numberOfDeadSoldier(playerNumber) &&
            (offset < _controller->getBoardSize()))
    {
#ifdef _WIN32
        cout << _controller->deadPawnToString(offset, playerNumber) << " ";
#elif __linux__
        colorItems(_controller->getDeadPawnRole(playerNumber, index),
                   playerNumber);
#endif
        offset++;
    }
}


void ViewConsole::printVictory()
{
#ifdef _WIN32
    SetConsoleTextAttribute(_hConsole, gold);
    cout << "Well done player ";
    (_controller->getWinner() == 0) ? SetConsoleTextAttribute(_hConsole,
            blue) : SetConsoleTextAttribute(_hConsole, red);
    cout << getPlayerTeam(_controller->getWinner());
    SetConsoleTextAttribute(_hConsole, gold);
    cout << ", you have won the game. " << endl;
    SetConsoleTextAttribute(_hConsole, normal);
#elif __linux__
    cout << GOLD "Well done player ";
    (_controller->getWinner() == 0) ? cout << BLUE "BLUE" NORMAL : cout <<
                                           RED "RED" NORMAL;
    cout << GOLD ", you have won the game. " NORMAL << endl;
#endif
}

void ViewConsole::displayErrorMessage(const std::string error)
{
    std::cout << error << std::endl;
}

std::string ViewConsole::getPlayerTeam(Team team)
{
    std::string teamString;
    switch (team)
    {
        case 0:
            teamString = "BLUE";
            break;
        case 1:
            teamString = "RED";
            break;

        default:
            teamString = "NONE";
            break;
    }
    return teamString;
}

void ViewConsole::equality()
{
    cout << "Too bad, there is no winner this game.";
}

void ViewConsole::updateView(Model * model)
{
    if (model->getState() == END_TURN)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
#ifdef _WIN32
        system("CLS");
#elif __linux__
        system("clear");
#endif
    }
    if(model->getState() != END_SET_UP)
    {
        printBoard();

        if (model->getState() == GAME_OVER)
        {
            if (model->getGameResult() == GameResult::VICTORY)
            {
                printVictory();
            }
            else
            {
                equality();
            }
        }
    }
}

void ViewConsole::colorItems(Role role, int team)
{
    switch (role)
    {
        case FLAG:
            (team == 0) ? cout << BLUE "F  " : cout << RED "F  ";
            break;
        case SPY:
            (team == 0) ? cout << BLUE "1  " : cout << RED "1  ";
            break;
        case SCOUT:
            (team == 0) ? cout << BLUE "2  " : cout << RED "2  ";
            break;
        case DEMINER:
            (team == 0) ? cout << BLUE "3  " : cout << RED "3  ";
            break;
        case SERGEANT:
            (team == 0) ? cout << BLUE "4  " : cout << RED "4  ";
            break;
        case LIEUTENANT:
            (team == 0) ? cout << BLUE "5  " : cout << RED "5  ";
            break;
        case COMMANDER:
            (team == 0) ? cout << BLUE "6  " : cout << RED "6  ";
            break;
        case MAJOR:
            (team == 0) ? cout << BLUE "7  " : cout << RED "7  ";
            break;
        case COLONEL:
            (team == 0) ? cout << BLUE "8  " : cout << RED "8  ";
            break;
        case GENERAL:
            (team == 0) ? cout << BLUE "9  " : cout << RED "9  ";
            break;
        case MARECHAL:
            (team == 0) ? cout << BLUE "10 " : cout << RED "10 ";
            break;
        case BOMB:
            (team == 0) ? cout << BLUE "B  " : cout << RED "B  ";
            break;
    }
    cout << NORMAL;
}
