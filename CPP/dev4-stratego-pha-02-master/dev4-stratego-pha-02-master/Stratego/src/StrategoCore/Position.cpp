#include "Position.h"

Position::Position(int x, int y) : _x{x}, _y{y}
{}

Position::Position() : _x{0}, _y{0}
{}

int Position::getX() const
{
    return _x;
}

int Position::getY() const
{
    return _y;
}
