/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package observer;

import model.State;

/**
 * @author Antoine Ghigny - g56359
 */
public interface Observer {
    /**
     * Method which, once called, updates the parameters to be updated in all the views.
     */
    void update(State state);
}
