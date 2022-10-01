#ifndef STATE_H
#define STATE_H

/**
 * @brief The State enum which represents the states in which the game can be found.
 */

enum State
{
    // The game is in the NOT_STARTED position before starting.
    NOT_STARTED,
    // The game state changes to SET_UP when the user must choose
    // how to import their board, by hand or using a .txt file.
    SET_UP,
    // State where the player uses a file to set up his formation of pawn.
    END_FILE_SET_UP,
    // State when both player has set up their formation of pawn.
    END_SET_UP,
    // The game state is at the PICK_PAWN position when choosing a pawn to move.
    PICK_PAWN,
    // The game state is at the PICK_PAWN position when it is necessary to choose the position where to move the pawn.
    MOVE_PAWN,
    // When the game is over, the game state changes to GAME_OVER
    GAME_OVER,
    // When the turn of the current player is over.
    END_TURN
};

#endif // STATE_H
