#ifndef POSITION_H
#define POSITION_H

/**
 * @brief The Position class which represents the position of each pawn.
 */
class Position
{
    int _x;
    int _y;

  public:

    /**
     * @brief Position Constructor to create a position.
     * To create a position, it needs a horizhontal
     * value and a vertical value.
     *
     * @param x the horizhontal value.
     * @param y the vertical value.
     */
    Position(int x, int y);

    Position();

    /**
     * @brief getX Gets the value of x.
     *
     * @return the value of x.
     */
    int getX() const;

    /**
     * @brief getY Gets the value of y.
     *
     * @return the value of y.
     */
    int getY() const;
};

/**
 * @brief operator == compare if 2 position are the same.
 * @param a the first position.
 * @param b the second position.
 * @return true if the position are the same else return false.
 */
inline bool operator==(Position const & a, Position const & b)
{
    return a.getX() == b.getX() && a.getY() == b.getY();
}

#endif // POSITION_H
