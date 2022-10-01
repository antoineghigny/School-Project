/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.simon.observer;

/**
 * @author Antoine Ghigny - g56359
 */
public interface Observable {
    /**
     * Method used to record an observer.
     *
     * @param obs The current observer
     */
    void registerObserver(Observer obs);

    /**
     * Allows you to remove an observer
     * @param obs The current observer
     */
    void removeObserver(Observer obs);

    /**
     * Once this method is called, call the update method of all observers.
     */
    void notifyObservers();

}
