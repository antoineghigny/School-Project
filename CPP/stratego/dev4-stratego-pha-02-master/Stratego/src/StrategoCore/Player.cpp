#include "Player.h"


const Graveyard & Player::graveyard() const
{
    return _graveyard;
}

Player::Player(Team team) : _team{team}, _graveyard{Graveyard{}}
{}

Team Player::getTeam() const
{
    return this->_team;
}

void Player::clean()
{
    this->_graveyard.clean();
}

int Player::numberOfDeath()
{
    return this->_graveyard.numberOfDeathPawn();
}

bool Player::isAllSoldierDead()
{
    return this->_graveyard.isAllSoldierDead();
}

void Player::addDeadPawn(const Pawn & pawn)
{
    this->_graveyard.addDeadPawn(pawn);
}

bool Player::isFlagCaptured() const
{
    return this->_graveyard.isFlagCaptured();
}

std::string Player::toString(int pos)
{
    return this->_graveyard.toString(pos);
}

Role Player::getRoleOfDeadPawn(int pos) const
{
    return this->_graveyard.getRoleOfDeadPawn(pos);
}

std::pair<Role, Team> Player::getLastDeadPawn() const
{
    return this->_graveyard.getLastDeadPawn();
}




