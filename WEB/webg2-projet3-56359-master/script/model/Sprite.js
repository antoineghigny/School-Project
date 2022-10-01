/**
 * The Sprite class inherits from Component, 
 * this is what will determine the position,
 * the positions of pacman and ghosts
 */
class Sprite extends Component {



    /**
     * Creation of the Sprite constructor, which takes 4 parameters
     * @param {Position} position the position of the Sprite (ghost or pacman)
     * @param {Direction} direction la direction du Sprite (fantome ou pacman)
     * @param {String} id the direction of the Sprite (ghost or pacman)
     * @param {Position} previousPosition the previous Sprite position (pacman or ghost)
     */
    constructor(position, direction, id, previousPosition) {
        super(id);
        this._position = position;
        this._direction = direction;
        this._previousPosition = previousPosition;
        this._askedToChangeDirection = false;
        this._askedDirection = undefined;
        this._isDead = false;
        this._initialPosition = this._position;
        this._initialDirection = this._direction;
    }
    /**
      * @returns {Position} the position of a sprite
      */
    get position() { return this._position; }

    /**
      * @returns {Direction} the direction of a sprite
      */
    get direction() { return this._direction; }

    /**
      * @returns {String} the id of the Sprite
      */
    get id() { return this._id; }

    /**
      * @returns {Position} the previous position of the Sprite
      */
    get previousPosition() { return this._previousPosition; }

    /**
      * @returns {boolean} true or false if the user wants to change direction
      */
    get askedToChangeDirection() { return this._askedToChangeDirection; }

    /**
      * @returns {boolean} true or false if pacman is dead
      */
    get isDead() { return this._isDead; }
    /**
     * the previous position becomes the current position.*
     * and the position in front of the next position taking the current direction.
     */
    move() {
        this._previousPosition = this._position;
        this._position = this._position.nextPosition(this._direction);
    }

    /**
     * When this method is called, askedToChangeDirection
     * changes to true and askedDirection changes to the desired direction.
     */
    askToChangeDirection(direction) {
        this._askedToChangeDirection = true;
        this._askedDirection = direction;
    }
    /**
     * When this method is called, the direction attribute changes 
     * to the requested position, and the askedToChangeDirection 
     * attribute changes to false.
     */
    changeDirection() {
        this._direction = this._askedDirection;
        this._askedToChangeDirection = false;
    }
    /**
     * When this method is called, the isDead attribute changes to true.
     */
    hasBeenEaten() {
        this._isDead = true;
    }

    /**
     * When this method is called, the isDead attribute changes to false, 
     * and the position changes to the initial position 
     * and the direction changes to the initial direction.
     */
    respawn() {
        this._isDead = false;
        this._position = this._initialPosition;
        this._direction = this._initialDirection;
    }


}

