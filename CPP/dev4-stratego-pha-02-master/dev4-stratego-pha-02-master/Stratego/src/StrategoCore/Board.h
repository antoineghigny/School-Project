#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Pawn.h"
#include "Position.h"
#include <string>

/**
 * @brief The Board class that represents the game board,
 * the methods that will allow to interact with this board.
 */
class Board
{

    std::array<std::array<Pawn, 12>, 12> _board {};

    /**
     * @brief createBoderTopBottom create top and bottom borders of the board.
     */
    void createBoderTopBottom();

    /**
     * @brief createBorderRightLeft create left and right borders of the board.
     */
    void createBorderRightLeft();

    /**
     * @brief createCenterWall create the wall that are in the center of the map.
     */
    void createCenterWall();

    /**
     * @brief fillTheBord fill the board with empty pawn.
     */
    void fillTheBord();

    /**
     * @brief fileChecker Checks checks if the constains of the file is correct.
     *
     * if a pawn miss or if the number maximum of pawn for a pawn is exceeded,
     * an exception will be throwned.
     *
     * @param file the file
     * @param team the team of the current player.
     */
    void fileChecker(std::ifstream * file, Team & team);

    /**
     * @brief putPawn create and put a pawn in the given position.
     *
     * This function is used when the current player uses
     * a file to do the placement of the pawn.
     *
     * @param role the role of the pawn.
     * @param pos the position of the pawn.
     * @param team the team of the pawn.
     */
    void createPawn(Role & role, Position & pos, Team & team);

    /**
     * @brief symboleConverter convert the symbol into role.
     * @param symbol the symbole of the pawn.
     * @return the role of the pawn that is associated to the symbol.
     */
    std::pair<Role, std::string> symboleConverter(std::string symbol);

    /**
     * @brief numberOfPossiblePawn count the number of possible pawn in the game.
     * @return the number of possible pawn.
     */
    int numberOfPossiblePawn();

    /**
     * @brief isInside Checks if the given position in inside the board.
     *
     * @param pos the position.
     * @return true if the positon is inside the board else return false.
     */
    bool isInside(const Position & pos);

    /**
     * @brief isCorrectSide Check if the pawn is put on the correct size of the board.
     *
     * By correct side, we means if the pawn is from the blue team, the pawn must be placed
     * in the lower part of the board and for red pawn in the upper part of the board.
     *
     * @param pos the position where the pawn will be put.
     * @param team the team.
     * @return true if the pawn will be place in the correct side else return false
     */
    bool isCorrectSide(const Position & pos, const Team & team);

    /**
     * @brief isSurrounded check if the choosen pawn wan be moved.
     * So that means if the pawn is not surrounded by allied pawns and/or wall.
     * @param pos the position of the pawn.
     * @param team the team of the pawn.
     * @return true if the pawn can move else return false.
     */
    bool isSurrounded(const Position & pos, const Team & team);

    /**
     * @brief isFreePosition check if the given position in the board is free.
     *
     * This function will if at the given there is no pawm of the same team or
     * a wall. If the position is occupied by an enemy, it will be considered
     * as a free position.
     *
     * @param pos the position.
     * @param team the team of the current player.
     * @return true if true the position is free else return false.
     */
    bool isFreePosition(const Position & pos, const Team & team);

    /**
     * @brief isBackAndForthTooMuch If the player plays the same pawn as the previous played
     *
     * checks if the pawn will do too much back and forth.
     *
     * @param srcPos the current pawn played.
     * @param destiPos the destination of the pawn.
     * @return true if there is too much back and forth else return false.
     */
    bool isBackAndForthTooMuch(const Position & srcPos,
                               const Position & destiPos);

    /**
     * @brief isNeighbor check if the destination a a neighbouring square.
     * @param neighbor the potential neighbouring square.
     * @return true if the position is in the neighbor else return false.
     */
    bool isNeighbor(const Position & neighbor);

    /**
     * @brief isThereObstacle Checks if there is an obstacle on the way to go to the destination.
     *
     * @param scrPos the current position of the scout.
     * @param destiPos the destination of the scout.
     * @param direction the direction to go to the destination.
     * @return true if there is an obstacle else return false.
     */
    bool isThereObstacle(const Position & srcPos,
                         const Position & destiPos, const Position & direction);

    /**
     * @brief canGoToThePosition check if the arrival position can be reached by the pawn.
     *
     * @param srcPos the choosen pawn.
     * @param destiPos the arrival position.
     */
    void canGoToThePosition(const Position & srcPos,
                            const Position & destiPos);

    /**
     * @brief checkScoutMove Checks if the distination of the scout is correct.
     *
     * So that means no diagonal move and their is no obstacle(wall or pawn allied or enemy pawn in his way.
     *
     * @param scrPos the position of the scout.
     * @param destiPos the destination of the scout.
     * @return true if the destination for the scout is correct else return false.
     */
    void checkScoutMove(const Position & scrPos,
                        const Position & destiPos);

  public:

    /**
     * @brief Board Constructor of the class. Create the board and the pawn
     * that will be used as wall of the board.
     */
    Board();

    bool canBePut(const Pawn & pawn, const Position & pos);

    /**
     * @brief putPawn Places a pawn in a certain position.
     *
     * @param pawn the pawn to place.
     * @param pos The position where to place the pawn.
     */
    void putPawn(Pawn & pawn, const Position & pos);

    /**
     * @brief isCurrentPlayerBlocked check if the current player is blocked.
     *
     * Blocked means that the current player doesn't have a pawn that can move.
     *
     * @return true if the current player is blocked else return false.
     */
    bool isCurrentPlayerBlocked(const Team & team);

    /**
     * @brief loadFile Loads the configuration file and applies it to the board.
     *
     * If the file doesn't exist or if the path is wrong, an exception will
     * be throwned.
     *
     * @param path the path of the file that will be used.
     * @param color the color of the team of the current player.
     */
    void loadFile(std::string & path, Team team);

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
     *
     * @return true if the pawn can move else throw an exception
     */
    bool canBePicked(const Position & pos, const Team & team);


    bool canBePick(const Position & pos, const Team & team);

    /**
     * @brief isCorrectMove Method that determines if a pawn can be moved
     * to a certain position.
     * It must verify that the destination is not a wall or an ally.
     *
     * But also that he has indeed the right move.
     * All roles except bomb, flag and wall can be moved one square,
     * except the scout, who can move one square in one direction.
     * But he can't jump over several enemy counters.
     *
     * @param srcPos The source position.
     * @param destiPos The destination position.
     * @return true if the pawn can go to the destination else throw an exception
     */
    bool isCorrectMove(const Position & srcPos,
                       const Position & destiPos);

    /**
     * @brief isThereEnemy Check if there is an enemy pawn at the given position.
     * @param pos the position.
     * @param team the team of the current player.
     * @return true if there is an enemy pawn else return false.
     */
    bool isThereEnemy(const Position & pos, const Team & team);

    /**
     * @brief move Moves a pawn from one position to another.
     * @param begin The position of the starting pawn.
     * @param end The arrival position of the pawn.
     */
    void move(const Position & begin, const Position & end);

    /**
     * @brief pawnDuel Compares the value of two pawnS
     * @param attackerPos the attaker's position.
     * @param defenderPos the defender's position.
     * @return return -1 if the attaker loses, return 0 if it's an equality and return 1 if the attaker wins.
     */
    int pawnDuel(const Position & attackerPos,
                 const Position & defenderPos);

    /**
     * @brief removePawn remove a pawn from the board.
     * @param pos the position of the pawn that will be removed.
     * @return the pawn that has been remove to be put in the graveyard.
     */
    Pawn removePawn(const Position & pos);

    /**
     * @brief getPawn Recover the pawn at a certain position.
     * @param pos The position where to recover the pawn.
     * @return A pawn
     */
    Pawn & getPawn(const Position & pos);

    /**
     * Get the size of the side of the board.
     *
     * include also corners.
     *
     * @return the size of the board.
     */
    int getSize() const;
};

#endif // BOARD_H
