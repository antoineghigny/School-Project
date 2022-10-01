/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package command;

/**
 *
 * @author antoi
 */
public interface CommandInterface {
    
     /**
     * Allows you to make or replay a move
     */
    void execute();
    
    /**
     * Allows you to cancel a move.
     */
    void undo();
}
