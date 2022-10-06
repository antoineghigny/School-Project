#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "Team.h"
#include "Position.h"
#include <vector>
#include "map"
#include "algorithm"
#include "utility"

/**
 * @brief The Role enum This enumeration contains all the possible role for a pawn.
 */
enum Role {FLAG, SPY, SCOUT, DEMINER, SERGEANT, LIEUTENANT,
           COMMANDER, MAJOR, COLONEL, GENERAL, MARECHAL,
           BOMB, EMPTY, WALL
          };

/** role is a map that contains the value of a pawn and the number of pawn for each role.
 *The Role enum will be used as the key fr this map.
 */
extern std::map<Role, std::pair<int, std::string>> allPossiblePawn;

/**
 * @brief The Pawn class which represents the different pawns of the game,
 * each pawn has a role, a team and a visibility.
 */
class Pawn
{

    Role _role;
    Team _team;
    bool _visibility;
    bool _moveable;
    std::vector<Position> _move;

  public:

    /**
     * @brief Pawn Create with the color of the team.
     *
     * @param pawn the pawn that will be copy.
     * @param color the color of the team of the pawn.
     */
    Pawn(Role role, Team color);

    /**
     * @brief Pawn construtor with no parameter that create a pawn
     * with the empty role and no team.
     */
    Pawn();

    /**
     * @brief addMove Add the current position of the pawn.
     * @param pos the current position of the pawn.
     */
    void addMove(const Position & pos);

    /**
     * @brief cleanMove remove all his previous move in the list.
     * Only keep the position of the pawn where it's.
     */
    void clearMove();

    /**
     * @brief isBackAndForthTooMuch count the number of comeback that the pawn
     * did.
     * @return true if there is too much back and forth else return false.
     */
    bool isBackAndForthTooMuch(const Position & pos);

    /**
     * @brief toString Print the value of the pawn
     */
    const std::string toString() const;

    /**
     * @brief getRole Gets the role of the pawn.
     * @return the role of the pawn.
     */
    Role getRole() const;

    /**
     * @brief getTeam  Gets the team of the pawn.
     * @return the team of the pawn.
     */
    Team getTeam() const;

    /**
     * @brief isMoveable get the boolean that indicate if the pawn is moveable.
     * @return true if the pawn is moveable else return false.
     */
    bool isMoveable() const;

    /**
     * @brief getVisibility Get the visibility of the pawn
     * @return the visibility of the pawn
     */
    bool isVisible() const;

    /**
     * @brief reveal Set the visibility of the pawn to true.
     */
    void reveal();

    /**
     * @brief hide set the visibility of the pawn to false.
     */
    void hide();
};

#endif // PAWN_H
