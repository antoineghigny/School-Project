/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.simon.observer;
import g56359.simon.model.State;
/**
 * @author Antoine Ghigny - g56359
 */
public interface Observer {
    /**
     * Method which, once called, updates the parameters to be updated in all the views.
     *
     * @param state Based on this parameter,
     *              the update method will update certain things
     *              according to what is specified in that string.
     */
    void update(State state);
}
