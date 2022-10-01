/**
 * the pacman controller
 */
class PacmanCtrl   {


    /**
     * 
     * @param {Pacman} pacman the only pacman
     */
     constructor(pacman){
        this._pacman = pacman;
    }
    /**
     * call the askToChangeDirection method
     * @param {Direction,} direction the direction requested
     */
    askToChangeDirection(direction){
        this._pacman.askToChangeDirection(direction);
    }
}