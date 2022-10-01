/**
 * Pacman class that inherits from Sprite
 */
class Pacman extends Sprite {

    /**
     * @param {Position} position The Pac-Man Position
     * @param {Direction} direction The Pac-Man direction
     * @param {String} PACMAN_ID the id of the pacman
     * @param {Position} previousPosition the previous position of the pacman
     * @param {Integer} nbLives the number of lives remaining of the pacman
     */
    constructor(position, direction, PACMAN_ID, previousPosition, nbLives) {
        super(position, direction, PACMAN_ID, previousPosition);

        this._nbLives = PACMAN_LIFE;
    }

    /**
      * @returns {Integer} the remaining life count of the pacman
      */
    get nbLives() { return this._nbLives; }

    /**
     * Subtract 1 from the pacman's remaining life count
     */
    hasBeenEaten() {
        this._nbLives = this._nbLives - 1;

    }
}

