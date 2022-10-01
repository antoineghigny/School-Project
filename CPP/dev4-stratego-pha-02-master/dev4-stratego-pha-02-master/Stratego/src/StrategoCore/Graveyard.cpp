#include "Graveyard.h"

Graveyard::Graveyard() : _deadPawn{}, _isFlagCaptured{false}
{}

void Graveyard::clean()
{
    this->_deadPawn.clear();
    this->_isFlagCaptured = false;
}

int Graveyard::numberOfDeathPawn() const
{
    return this->_deadPawn.size();
}

bool Graveyard::isAllSoldierDead()
{
    int numberTotalSoldiers {numberTotalOfSoldier()};
    int deadPawn {numberOfDeadSoldier()};

    return deadPawn == numberTotalSoldiers;
}

int Graveyard::numberTotalOfSoldier() const
{
    int counter{};
    for(auto & i : allPossiblePawn)
    {
        if(!isalpha(i.second.second.at(0)))
        {
            counter += i.second.first;
        }
    }
    return counter;
}

int Graveyard::numberOfDeadSoldier() const
{
    int counter{};
    for(auto & pawn : this->_deadPawn)
    {
        if(!isalpha(allPossiblePawn.at(pawn.getRole()).second.at(0))) {counter++;}
    }
    return counter;
}

void Graveyard::addDeadPawn(const Pawn & pawn)
{
    if(pawn.getRole() == Role::FLAG) {this->_isFlagCaptured = true;}
    this->_deadPawn.push_back(pawn);
}

bool Graveyard::isFlagCaptured() const
{
    return this->_isFlagCaptured;
}


std::string Graveyard::toString(int pos) const{
    return _deadPawn.at(pos).toString();
}

Role Graveyard::getRoleOfDeadPawn(int pos) const
{
    return _deadPawn.at(pos).getRole();
}

std::pair<Role, Team> Graveyard::getLastDeadPawn() const
{
    return std::pair(_deadPawn.at(_deadPawn.size()-1).getRole(), _deadPawn.at(_deadPawn.size()-1).getTeam());
}

