#ifndef PLAYER_H
#define PLAYER_H

#include "Team.h"
#include "Graveyard.h"


/**
 * @brief The Player class Which represents the player's class,
 * each player has a team, a graveyard and a file which represents
 * the part of the board in a string file.
 */
class Player
{

    Team _team;
    Graveyard _graveyard;

  public:
    /**
     * @brief Player Constructor of the player
     */
    Player(Team team);

    /**
     * @brief getTeam Get the team of the player
     * @return the team of the player
     */
    Team getTeam() const;

    /**
     * @brief clean Cleans the graveyard by cleaning the vector and reset the bomb.
     */
    void clean();

    /**
     * @brief numberOfDeath Gets the numbers of dead pawn.
     *
     * @return the number of dead soldiers.
     */
    int numberOfDeath();

    /**
     * @brief isAllSoldierDead Determines if all the soldiers of a player are dead
     * @return true if all the soldiers of a player are dead
     */
    bool isAllSoldierDead();

    /**
     * @brief addDeadPawn Adds a pawn to the graveyard when a soldier died.
     *
     * @param pawn the pawn that died.
     */
    void addDeadPawn(const Pawn & pawn);

    /**
     * @brief getIsFlagCaptured get the boolean that indicate if the flag has been captured.
     * @return true if the flag has been captured
     */
    bool isFlagCaptured() const;

    /**
     * @brief graveyard Method that returns the graveyard
     * @return return the graveyard
     */
    const Graveyard & graveyard() const;

    /**
     * @brief toString Method that displays the string of a role at position
     * @param pos the position in the vector
     * @return the stringify of a pawn at position pos
     */
    std::string toString(int pos);

    /**
     * @brief getRoleOfDeadPawn
     * @param pos
     * @return Retrieves the role of a dead pawn in the graveyard at position pos.
     */
    Role getRoleOfDeadPawn(int pos) const;

    /**
     * @brief getLastDeadPawn get the last dead pawn of the player.
     * @return the role and the team of the dead pawn.
     */
    std::pair<Role, Team> getLastDeadPawn() const;

};

#endif // PLAYER_H
