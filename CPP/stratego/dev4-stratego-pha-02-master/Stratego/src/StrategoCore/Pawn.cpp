#include "Pawn.h"
#include <iostream>
#include "Team.h"
#include "Position.h"
#include <vector>

std::map<Role, std::pair<int, std::string>> allPossiblePawn =
{
    //first --> number of pawn, second --> symbol
    {Role::SPY, std::make_pair(1, "1")},
    {Role::SCOUT, std::make_pair(8, "2")},
    {Role::DEMINER, std::make_pair(5, "3")},
    {Role::SERGEANT, std::make_pair(4, "4")},
    {Role::LIEUTENANT, std::make_pair(4, "5")},
    {Role::COMMANDER, std::make_pair(4, "6")},
    {Role::MAJOR, std::make_pair(3, "7")},
    {Role::COLONEL, std::make_pair(2, "8")},
    {Role::GENERAL, std::make_pair(1, "9")},
    {Role::MARECHAL, std::make_pair(1, "10")},
    {Role::BOMB, std::make_pair(6, "B")},
    {Role::FLAG, std::make_pair(1, "F")},
    {Role::WALL, std::make_pair(0, "W")},
    {Role::EMPTY, std::make_pair(0, "*")}
};

Pawn::Pawn(Role role, Team team) : _role{role}, _team{team}, _visibility{false}, _move{}
{
    if(isalpha(allPossiblePawn.at(role).second.at(0))) {this->_moveable = false;}
    else {this->_moveable = true;}
}

Pawn::Pawn() : _role{Role::EMPTY}, _team{Team::NONE}, _visibility{false}, _moveable{false}, _move{}
{}

void Pawn::addMove(const Position & pos)
{
    _move.push_back(pos);
}

void Pawn::clearMove()
{
    auto tmpPos {this->_move.at(this->_move.size() - 1)};
    this->_move.clear();
    this->_move.push_back(tmpPos);
}

bool Pawn::isBackAndForthTooMuch(const Position & pos)
{
    int cpt {0};
    auto lenght {(int)this->_move.size()};
    int offset {2};
    while (lenght - offset >= 0 && pos == this->_move.at(lenght - offset))
    {
        cpt++;
        offset += 2;
    }
    return cpt > 3;
}

const std::string Pawn::toString() const
{
    return allPossiblePawn.at(this->_role).second;
}


Role Pawn::getRole() const
{
    return _role;
}

Team Pawn::getTeam() const
{
    return _team;
}

bool Pawn::isMoveable() const
{
    return this->_moveable;
}

bool Pawn::isVisible() const
{
    return _visibility;
}

void Pawn::reveal()
{
    this->_visibility = true;
}

void Pawn::hide()
{
    this->_visibility = false;
}
