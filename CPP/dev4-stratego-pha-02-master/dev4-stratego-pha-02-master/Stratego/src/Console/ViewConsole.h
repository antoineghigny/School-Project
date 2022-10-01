#ifndef VIEWCONSOLE_H
#define VIEWCONSOLE_H

#ifdef _WIN32
#define IFWIN32(arg) arg
#else
#define IFWIN32(arg)
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <Game.h>
#include "Observer.h"

class Controller;


class ViewConsole : public Observer
{
  private:
#ifdef _WIN32
    HANDLE _hConsole;
#endif

    /**
     * @brief ViewConsole The viewConsole constructor
     * @param controller The game controller
     */
    Controller * _controller;

    /**
     * @brief printInContext Displays each pawn in the board. If the pawn has a role of 10, add a space, otherwise 2.
     * @param p the position of each pawn
     * @param hConsole index used to reference a structure which is used for colors.
     */
    void printInContext(const Position p);

    /**
     * @brief displayForPlayer Display a current player's graveyard next to the displayBoard.
     * @param index the index of the dead pawn in vector
     * @param offset the current offset
     * @param playerNumber a player
     */
    void displayForPlayer(int index, int offset, int playerNumber);


    /**
     * @brief printGraveYard Shows the current user's graveyard at the top.
     * @param index The index is the position in the graveyard
     * @param hConsole index used to reference a structure which is used for colors.
     * @param playerNumber The player who owns the graveyard
     */
    void printGraveYard(int index, int playerNumber);

    /**
     * @brief printGraveyardInContext Indicates the player who owns the graveyard
     * @param hConsole index used to reference a structure which is used for colors.
     * @param playerNumber The player who owns the graveyard
     */
    void printGraveyardInContext(int playerNumber);

    /**
     * @brief printGraveYardBelow Shows the other player's graveyard at the bottom.
     * @param index The index is the position in the graveyard
     * @param hConsole index used to reference a structure which is used for colors.
     * @param playerNumber The player who owns the graveyard
     */
    void printGraveYardBelow(int index,
                             int playerNumber);

    /**
     * @brief colorItems Method used for linux. To display the colors of each pawn.
     * @param role the role of a pawn
     * @param team the team of the player to which the pawn belongs
     */
    void colorItems(Role role, int team);

    /**
     * @brief verifString Checks the user input, if it respects a certain pattern.
     * And returns in a std::pair the character 1 and 2
     * @return a std::pair with the first and second character.
     */
    std::pair<char, char> verifString();

    /**
     * @brief displayCurrentPlayer Method that displays the current player.
     * @param hConsole index used to reference a structure which is used for colors.
     */
    void displayCurrentPlayer();

    /**
     * @brief printBoard Displays the board with colors.
     */
    void printBoard();

    /**
     * @brief printVictory Shows which player won the game.
     */
    void printVictory();

    /**
     * @brief equality Displays a tie if both players have lost.
     */
    void equality();

  public:
    /**
     * @brief ViewConsole The ViewConsole constructor which takes a controller as a parameter.
     * @param controller the game controller.
     */
    ViewConsole(Controller * controller);

    /**
     * @brief sendWelcomeMeesage dispaly a welcome message foe the user.
     */
    void sendWelcomeMeesage();

    /**
     * @brief sendGoodbyeMessage Send a goodbye message when the user stop the game.
     */
    void sendGoodbyeMessage();

    /**
     * @brief askGameMode ask the user if he wants to play the game in easy mode or not.
     * @return
     */
    std::string askGameMode();

    /**
     * @brief sendHelp Displays the different rules of the game
     */
    void sendHelp();

    /**
     * @brief askPlacementChoice The user can choose the way to import his board.
     * By hand or via a txt file
     * @return Y if the player wants to import a file N (or other) otherwise.
     */
    std::string askPlacementChoice();

    /**
     * @brief askRestart Ask the user if they want to try again and recommend
     * @return Y if the user wants to restart the game, N (or other) otherwise.
     */
    char askRestart();

    /**
     * @brief manuelPlacement Method that asks the user to place each pawn 1 by 1.
     */
    void manuelPlacement();

    /**
     * @brief askFile Method that allows to import a board from a txt file
     */
    void askFile();

    /**
     * @brief pickPawn Method that allows you to choose a pawn to move
     */
    void pickPawn();

    /**
     * @brief getPlayerTeam Method that returns a string corresponding to a player's team.
     * @param team A team
     * @return a string that corresponds to the team.
     */
    std::string getPlayerTeam(Team team);

    /**
     * @brief movePawn Method that asks the user to which position to move the pawn chooses in the pickPawn method.
     */
    void movePawn();

    /**
     * @brief displayErrorMessage display the given error message.
     * @param error the error message.
     */
    void displayErrorMessage(const std::string error);

    /**
     * @brief updateView each time this method is called, the view should perform an action based on the current state of the game.
     * @param m the game model
     */
    void updateView(Model * m);
};

#endif // CONTROLLER_H
