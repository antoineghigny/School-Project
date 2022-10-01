/**
 * This class will allow the user to be able to change
 * the direction of the pacman
 */
class PacmanView {

    /**
     * when the user clicks on a direction key, calls askToChangeDirection 
     * with the requested direction
     * @param {*} pacmanCtrl the pacmanCtrl class
     */
    constructor(pacmanCtrl) {
        this._pacmanCtrl = pacmanCtrl
        let pacman = this._pacmanCtrl
        $(window).on("keydown", function (event) {
            switch (event.key) {
                case `ArrowLeft`:
                    pacman.askToChangeDirection(Direction.WEST);
                    break;
                case `ArrowRight`:
                    pacman.askToChangeDirection(Direction.EAST);
                    break;
                case `ArrowUp`:
                    pacman.askToChangeDirection(Direction.NORTH);
                    break;
                case `ArrowDown`:
                    pacman.askToChangeDirection(Direction.SOUTH);
                    break;
            }
        })
    }
}

