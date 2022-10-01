/**
 * Ghost class that inherits from Sprite. 
 * This is the class that will allow you to 
 * change the direction of the ghosts randomly.

 */
class Ghost extends Sprite {

    /**
     * 
     * @param {Position} position The position of the ghost
     * @param {Direction} direction The direction of the ghost
     * @param {String} id The id of the ghost
     */
    constructor(position, direction, id) {
        super(position, direction, id);
        this._timer = setInterval(() => {
            this._choiceNewDirection();
        }, 4000);

    }
    /**
     * Choose a direction randomly
     * will allow the ghost to signify its intention to change
     * direction.
     */
    _choiceNewDirection() {
        switch (Math.floor(Math.random() * RANDOM_DIRECTION)) {
            case 0:
                this.askToChangeDirection(Direction.SOUTH);
                this.changeDirection();
                break;
            case 1:
                this.askToChangeDirection(Direction.NORTH);
                this.changeDirection();
                break;
            case 2:
                this.askToChangeDirection(Direction.EAST);
                this.changeDirection();
                break;
            case 3:
                this.askToChangeDirection(Direction.WEST);
                this.changeDirection();
                break;
            default:
                this.askToChangeDirection(Direction.SOUTH);
                this.changeDirection();
        }
    }

    /**
     * 
     * @param {*} pacman The pacman
     * @returns  rue if the Pacman and the ghost are found
     * in the same position or if the Pacman is found 
     * in the old position of the ghost and the
     * ghost ends up in the old Pacman position.
     */
    canEat(pacman) {
        return JSON.stringify(pacman._position) === JSON.stringify(this._position)
            || JSON.stringify(pacman._position) === JSON.stringify(this._previousPosition)
            && JSON.stringify(this._position) === JSON.stringify(pacman._previousPosition);
    }
    /**
     * an intention to change direction is signified when the ghost
     * is blocked.
     */
    notifyIsBlocked() {
        this._choiceNewDirection();
    }
}

