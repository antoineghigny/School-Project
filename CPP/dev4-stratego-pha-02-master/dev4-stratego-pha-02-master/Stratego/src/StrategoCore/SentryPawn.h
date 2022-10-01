#ifndef SENTRYPAWN_H
#define SENTRYPAWN_H
#include "Pawn.h"

class SentryPawn : public Pawn
{
  public:

    /**
     * @brief specialPawn
     * @return
     */
    virtual bool specialPawn() const = 0;

    virtual ~SentryPawn();
};


#endif // SENTRYPAWN_H

