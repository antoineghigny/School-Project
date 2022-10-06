#ifndef DECK_H
#define DECK_H

#include "Pawn.h"
#include <vector>
/**
 * @brief The Deck class Class that represents the deck
 * with the different possible roles.
 */
class Deck
{

    std::vector<Pawn> _availablePawn;

  public:

    /**
     * @brief Deck Constructor of the class Deck.
     */
    Deck();

    /**
     * @brief generateDeck generate all the pawn of a team.
     * @param team the team of the pawn.
     */
    void generateDeck(const Team team);

    /**
     * @brief getDeck Get a pawn in the deck.
     *
     * @return the a reference to the pawn.
     */
    const Pawn & getPawnInDeck() const;

    /**
     * @brief getPawnInDeckAt get the pawn at a specific position in the deck.
     * @param index the index of the pawn in the deck.
     * @return return the pawn.
     */
    const Pawn & getPawnInDeckAt(int index) const;

    /**
     * @brief removePawnInDeck remove the pawn that has been put from the deck.
     */
    void removePawnInDeck();

    /**
     * @brief removePawnInDeckAt remove a specific pawn in the deck.
     * @param index
     */
    Pawn removePawnInDeckAt(int index);

    /**
     * @brief numberOfPawn get the number of pawns in the deck.
     * @return the number of pawn in the deck.
     */
    int numberOfPawn() const;
};

#endif // DECK_H
