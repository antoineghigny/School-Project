#include "Board.h"
#include <array>
#include "Pawn.h"
#include "Position.h"
#include <string>
#include <fstream>

Board::Board()
{
    createBoderTopBottom();
    createBorderRightLeft();
    fillTheBord();
    createCenterWall();
}



void Board::createBoderTopBottom()
{
    int size {(int)this->_board.size()};
    for (int i {0}; i < size; i++)
    {
        this->_board[0].at(i) = Pawn {Role::WALL, Team::NONE};
        this->_board[size - 1].at(i) = Pawn {Role::WALL, Team::NONE};
    }
}

void Board::createBorderRightLeft()
{
    int size {(int)this->_board.size()};
    for (int i {1}; i < size - 1; i++)
    {
        this->_board[i].at(0) = Pawn {Role::WALL, Team::NONE};
        this->_board[i].at(size - 1) = Pawn {Role::WALL, Team::NONE};
    }
}

void Board::createCenterWall()
{
    int line1 {((int)this->_board.size() - 1) / 2};
    int line2 {((int)this->_board.size()) / 2};

    for (int i {}, j{3}; i < 4; i++, j++)
    {
        this->_board[line1].at(j) = Pawn {Role::WALL, Team::NONE};
        this->_board[line2].at(j) = Pawn {Role::WALL, Team::NONE};
        if (j == 4)
        {
            j += 2;
        }
    }
}

void Board::fillTheBord()
{
    for (int i {1}; i < (int)this->_board.size() - 2; i++)
    {
        for (int j {1}; j < (int)this->_board.size() - 2; j++)
        {
            this->_board[i].at(j) = Pawn{};
        }
    }
}

bool Board::canBePut(const Pawn & pawn, const Position & pos)
{
    return isInside(pos) && isCorrectSide(pos, pawn.getTeam()) &&
           isFreePosition(pos, pawn.getTeam());

}

void Board::putPawn(Pawn & pawn, const Position & pos)
{
    if (!isInside(pos))
    {
        throw std::invalid_argument("The position is not inside the board.");
    }
    else if (!isCorrectSide(pos, pawn.getTeam()))
    {
        throw std::invalid_argument("The pawn can only be placed on your side of the board.");
    }
    else if (!isFreePosition(pos, pawn.getTeam()))
    {
        throw std::invalid_argument("The pawn can't be placed at this position because the position "
                                    "is already occupied by a pawn.");
    }
    pawn.addMove(pos);
    this->_board[pos.getX()].at(pos.getY()) = pawn;
}

bool Board::isCorrectSide(const Position & pos, const Team & team)
{
    if (team == Team::BLUE)
    {
        return pos.getX() > 6 && pos.getX() < (int)this->_board.size() - 1
               && pos.getY() > 0 && pos.getY() < (int)this->_board.size() - 1;
    }
    else
    {
        return pos.getX() < 5 && pos.getX() > 0
               && pos.getY() > 0 && pos.getY() < (int)this->_board.size() - 1;
    }
}

bool Board::isCurrentPlayerBlocked(const Team & team)
{
    int i {};
    if (team == Team::RED)
    {
        i = 1;
    }
    else
    {
        i = 7;
    }

    for (; i <= getSize(); i++)
    {
        for (int j {1}; j <= getSize(); j++)
        {
            if (this->_board[i].at(j).isMoveable() &&
                    !isSurrounded(Position(i, j), team))
                return false;
        }
    }
    return true;
}

void Board::loadFile(std::string & path, Team team)
{
    std::ifstream file;
    file.open(path);

    if (file.is_open())
    {
        fileChecker(&file, team);
        file.close();
    }
    else
    {
        throw std::invalid_argument("The file doesn't exist or the path is wrong");
    }
}

void Board::fileChecker(std::ifstream * file, Team & team)
{
    std::string symbol;
    std::map<Role, int> checker;
    std::pair<Role, std::string> role;
    int counter {0};
    int i{1}, j {1};

    if (team == Team::BLUE)
    {
        i = this->_board.size() - 2;   //blue invert file
    }

    while (*file >> symbol)
    {
        role = symboleConverter(symbol);
        if (role.first == Role::WALL || role.first == Role::EMPTY)
        {
            throw std::invalid_argument("There is a symbole that doesn't exist or this symbole can't be used : "
                                        + role.second);
        }

        if (checker.find(role.first) != checker.end())
        {
            checker.at(role.first)++;
            if (checker.at(role.first) > allPossiblePawn.at(role.first).first)
            {
                file->close();
                throw std::invalid_argument("The file contains an excess pawn type : "
                                            + role.second);
            }
        }
        else
        {
            checker.insert(std::pair<Role, int> {role.first, 1});
        }
        Position pos {i, j};
        createPawn(role.first, pos, team);
        counter++;
        j++;

        if (j > (int)this->_board.size() - 2)
        {
            j = 1;
            if (team == Team::RED)
            {
                i++;
            }
            else
            {
                i--;
            }
        }
    }

    if (counter != numberOfPossiblePawn())
    {
        file->close();
        auto s1 {"There are "};
        auto s2 {std::to_string(numberOfPossiblePawn() - counter)};
        auto s3 {" missing pawns."};
        throw std::invalid_argument(s1 + s2 + s3);
    }
}

void Board::createPawn(Role & role, Position & pos, Team & team)
{
    Pawn p {role, team};
    p.addMove(pos);
    this->_board[pos.getX()].at(pos.getY()) = p;
}

std::pair<Role, std::string> Board::symboleConverter(
    std::string symbol)
{
    for (auto & i : allPossiblePawn)
    {
        if (i.second.second == symbol)
        {
            std::pair<Role, std::string> role = make_pair(i.first, symbol);
            return role;
        }
    }
    std::pair<Role, std::string> role = make_pair(Role::EMPTY, symbol);
    return role;
}

int Board::numberOfPossiblePawn()
{
    int counter {};
    for (auto & i : allPossiblePawn)
    {
        counter += i.second.first;
    }

    return counter;
}

bool Board::canBePicked(const Position & pos, const Team & team)
{
    if (!isInside(pos))
    {
        throw std::invalid_argument("The given position is not inside the board.");
    }
    else if (getPawn(pos).getRole() == Role::EMPTY)
    {
        throw std::invalid_argument("There is no pawn at the given position.");
    }
    else if (!getPawn(pos).isMoveable())
    {
        throw std::invalid_argument("The chosen pawn is not a moveable pawn.");
    }
    else if (team != getPawn(pos).getTeam())
    {
        throw std::invalid_argument("You can't select an enemy pawn.");
    }
    else if (isSurrounded(pos, team))
    {
        throw std::invalid_argument("The can't move because it's surrounded by allied pawn or wall.");
    }

    return true;
}

bool Board::canBePick(const Position &pos, const Team &team)
{
    if (!isInside(pos)
            || getPawn(pos).getRole() == Role::EMPTY
            || !getPawn(pos).isMoveable()
            || team != getPawn(pos).getTeam()
            || isSurrounded(pos, team))
    {
        return false;
    }
    return true;
}



bool Board::isInside(const Position & pos)
{
    return 0 < pos.getX() && pos.getX() <= this->getSize() &&
           0 < pos.getY() && pos.getY() <= this->getSize();
}

bool Board::isSurrounded(const Position & pos, const Team & team)
{

    Position posUp {pos.getX() + 1, pos.getY()};
    Position posDown {pos.getX() - 1, pos.getY()};
    Position posRight {pos.getX(), pos.getY() + 1};
    Position posLeft {pos.getX(), pos.getY() - 1};

    return !isFreePosition(posUp, team) &&
           !isFreePosition(posDown, team) &&
           !isFreePosition(posRight, team) &&
           !isFreePosition(posLeft, team);
}

bool Board::isFreePosition(const Position & pos, const Team & team)
{
    return getPawn(pos).getTeam() != team &&
           getPawn(pos).getRole() != Role::WALL;
}

bool Board::isCorrectMove(const Position & srcPos,
                          const Position & destiPos)
{
    if (!isInside(destiPos))
    {
        throw std::invalid_argument("the destination is not inside the board.");
    }
    else if (!isFreePosition(destiPos,
                             this->_board[srcPos.getX()].at(srcPos.getY()).getTeam()))
    {
        throw std::invalid_argument("The destination is not free because there is an allied pawn or a wall.");
    }
    else if (isBackAndForthTooMuch(srcPos, destiPos))
    {
        throw std::invalid_argument("You can't do more than 3 back and forth.");
    }

    canGoToThePosition(srcPos, destiPos);

    return true;
}

bool Board::isBackAndForthTooMuch(const Position & srcPos,
                                  const Position & destiPos)
{
    return this->_board[srcPos.getX()].at(
               srcPos.getY()).isBackAndForthTooMuch(destiPos);
}

bool Board::isNeighbor(const Position & neighbor)
{
    return (neighbor.getX() == 0 && neighbor.getY() == 1) ||
           (neighbor.getX() == 0 && neighbor.getY() == -1) ||
           (neighbor.getX() == 1 && neighbor.getY() == 0) ||
           (neighbor.getX() == -1 && neighbor.getY() == 0);
}

void Board::canGoToThePosition(const Position & srcPos,
                               const Position & destiPos)
{
    if (this->_board[srcPos.getX()].at(srcPos.getY()).getRole() ==
            Role::SCOUT)
    {
        checkScoutMove(srcPos, destiPos);
    }
    else
    {
        Position checkPos {destiPos.getX() - srcPos.getX(), destiPos.getY() - srcPos.getY()};
        if (!isNeighbor(checkPos))
        {
            throw std::invalid_argument("the destination is not a square around the chosen pawn.");
        }
    }
}

void Board::checkScoutMove(const Position & srcPos,
                           const Position & destiPos)
{
    Position checkPos {destiPos.getX() - srcPos.getX(), destiPos.getY() - srcPos.getY()};

    if (checkPos.getX() != 0 && checkPos.getY() != 0)
    {
        throw std::invalid_argument("The destination of the pawn is not in the horizontal or "
                                    "vertical axis of the pawn.");
    }
    else if (isThereObstacle(srcPos, destiPos, checkPos))
    {
        throw std::invalid_argument("There is an obstacle in the way.");
    }
}

bool Board::isThereObstacle(const Position & srcPos,
                            const Position & destiPos, const Position & direction)
{
    int x {}, y {};
    if (direction.getX() != 0)
    {
        x = direction.getX() / abs(direction.getX());
    }
    else
    {
        y = direction.getY() / abs(direction.getY());
    }

    for (int i {srcPos.getX() + x}, j {srcPos.getY() + y}; i !=
            destiPos.getX() || j != destiPos.getY(); i += x, j += y)
    {
        if (this->_board[i].at(j).getRole() != Role::EMPTY)
        {
            return true;
        }
    }
    return false;
}

bool Board::isThereEnemy(const Position & pos, const Team & team)
{
    Pawn pawn {this->_board[pos.getX()].at(pos.getY())};
    return pawn.getTeam() != Team::NONE && pawn.getTeam() != team;
}

void Board::move(const Position & begin, const Position & end)
{
    Pawn tmpPawn {this->_board[begin.getX()].at(begin.getY())};
    this->_board[begin.getX()].at(begin.getY()) =
        this->_board[end.getX()].at(end.getY());
    this->_board[end.getX()].at(end.getY()) = tmpPawn;
}

int Board::pawnDuel(const Position & attackerPos,
                    const Position & defenderPos)
{
    Pawn attacker {this->_board[attackerPos.getX()].at(attackerPos.getY())};
    Pawn defender {this->_board[defenderPos.getX()].at(defenderPos.getY())};
    if ((attacker.getRole() == Role::SPY &&
            defender.getRole() == Role::MARECHAL)
            || (attacker.getRole() == Role::DEMINER &&
                defender.getRole() == Role::BOMB)
            || defender.getRole() == Role::FLAG
            || (attacker.getRole() > defender.getRole())) return 1;
    else if (attacker.getRole() == defender.getRole()) return 0;
    else return -1;
}

Pawn Board::removePawn(const Position & pos)
{
    Pawn pawn {this->_board[pos.getX()].at(pos.getY())};
    this->_board[pos.getX()].at(pos.getY()) = Pawn {};
    return pawn;
}

Pawn & Board::getPawn(const Position & pos)
{
    return this->_board[pos.getX()].at(pos.getY());
}

int Board::getSize() const
{
    return this->_board.size() - 2;
}
