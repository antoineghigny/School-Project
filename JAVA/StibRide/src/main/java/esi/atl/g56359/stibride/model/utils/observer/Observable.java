package esi.atl.g56359.stibride.model.utils.observer;

import java.util.List;

public interface Observable {
     /**
     * Register an observer.
     *
     * @param observer the observer.
     */
    /**
     * Register an observer to be notified when the data changes.
     *
     * @param observer The observer to register.
     */
    public void registerObserver(Observer observer);

    /**
     * Remove the observer from the list of observers.
     *
     * @param obs The observer to remove.
     */
    void removeObserver(Observer obs);

    /**
     * Notify all observers of a change in state.
     */
    public void notifyObservers(Object...args);
}
