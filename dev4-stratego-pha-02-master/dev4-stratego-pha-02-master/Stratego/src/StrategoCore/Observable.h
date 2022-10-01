#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"

class Observable {

public :

    /**
     * @brief ~Observable the Observable destructor
     */
    virtual ~Observable(){};

    /**
     * @brief addObserver Method that adds a view as an observer.
     * @param observer the observer
     */
    virtual void addObserver(Observer * observer) = 0;

    /**
     * @brief removeObserver Method to remove a view as an observer.
     * @param observer the observer
     */
    virtual void removeObserver(Observer * observer) = 0;

    /**
     * @brief notifyObservers Allows you to notify observers.
     */
    virtual void notifyObservers() = 0;
};

#endif // OBSERVABLE_H
