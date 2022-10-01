#include "Deck.h"

Deck::Deck() : _availablePawn{}
{}

void Deck::generateDeck(const Team team)
{
    this->_availablePawn.clear();
    for (auto i : allPossiblePawn)
    {
        for (int j = 0; j < i.second.first; j++)
        {
            Pawn p {i.first, team};
            this->_availablePawn.push_back(p);
        }
    }
}

const Pawn & Deck::getPawnInDeck() const
{
    return this->_availablePawn.at(0);
}


const Pawn & Deck::getPawnInDeckAt(int index) const
{
    return this->_availablePawn.at(index);
}

void Deck::removePawnInDeck()
{
    this->_availablePawn.erase(this->_availablePawn.begin());
}

Pawn Deck::removePawnInDeckAt(int index)
{
    Pawn p = this->_availablePawn.at(index);
    this->_availablePawn.erase(this->_availablePawn.begin() + index);
    return p;
}

int Deck::numberOfPawn() const
{
    return this->_availablePawn.size();
}
