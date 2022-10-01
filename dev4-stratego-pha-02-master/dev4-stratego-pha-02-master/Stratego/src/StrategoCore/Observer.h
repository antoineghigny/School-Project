#ifndef OBSERVER_H
#define OBSERVER_H

#include <Model.h>

class Observer{

public :

    /**
     * @brief ~Observer The destroyer of observers
     */
    virtual ~Observer(){};

    /**
     * @brief update update simple update, extended class must have
     * virtual void update(const Observable & source) = 0;
     * update with Observable in parametre
     * reference to observable
     * to cast Observable to child
     * @param m The model
     */
    virtual void updateView(Model* m) = 0;
};

#endif // OBSERVER_H
