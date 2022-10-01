#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <vector>
#include "Pawn.h"

/**
 * @brief The Graveyard class that represents the graveyard,
 * where the pieces will end up when they have lost a battle.
 */
class Graveyard
{

    std::vector<Pawn> _deadPawn;
    bool _isFlagCaptured;

    /**
     * @brief numberTotalOfSoldier get the number total of soldier.
     *
     * By soldier we means pawns that can move.
     *
     * @return the number of soldier.
     */
    int numberTotalOfSoldier() const;

    /**
     * @brief numberOfDeadSoldier get the number of dead soldier.
     *
     * By soldier we means pawns that can move.
     *
     * @return the number of dead soldier.
     */
    int numberOfDeadSoldier() const;

public:

    /**
     * Constructor that create the graveyard. The graveyard is used to stock
     * the apwn that are dead and the bombs that exploded.
     */
    Graveyard();

    /**
     * @brief clean Cleans the graveyard by cleaning the vector.
     */
    void clean();

    /**
     * @brief numberOfDeathPawn Gets the numbers of dead pawns.
     *
     * @return the number of dead pawn.
     */
    int numberOfDeathPawn() const;

    /**
     * @brief isAllSoldierDead check if all the soldiers of a player are dead.
     *
     * By soldier we means pawns that can move.
     *
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
     * @brief IsFlagCaptured get the boolean that indicate if the flag has been captured.
     * @return true if the flag has been captured else return false.
     */
    bool isFlagCaptured() const;

    /**
     * @brief toString Method that displays in std::string the pawn at position pos in the graveyard
     * @param pos the position in the graveyard
     * @return the role of the pawn at the pos position in the graveyard
     */
    std::string toString(int pos) const;

    /**
     * @brief getRoleOfDeadPawn Displays the role of a dead pawn at the pos position
     * @param pos the position in the graveyard vector
     * @return the role of a dead pawn at the pos position
     */
    Role getRoleOfDeadPawn(int pos) const;

    /**
     * @brief getLastDeadPawn get the last dead pawn of the player.
     * @return the role and the team of the dead pawn.
     */
    std::pair<Role, Team> getLastDeadPawn() const;

};

#endif // GRAVEYARD_H
