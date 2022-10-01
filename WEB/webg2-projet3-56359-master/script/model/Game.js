/**
 * The Game class will serve as a front for us. 
 * For this first iteration, it only owns the labyrinth in ownership.
 */
class Game {

    /**
     * @param {*} rawMaze the table of the labyrinth
     * @param {*} GameCtrl the controller
     */

    constructor(rawMaze, GameCtrl) {
        this._maze = new Maze(rawMaze);
        this._score = 0;
        this._removeDot;
        this._highScore = 0;
        this._gameCtrl = GameCtrl;

        this._pacman = new Pacman(this._maze.pacmanStartPosition, Direction.WEST, "pacman");
        this._fantomes = [
            new Ghost(this._maze._ghostStartPosition, Direction.WEST, "blinky"),
            new Ghost(this._maze._ghostStartPosition, Direction.WEST, "pinky"),
            new Ghost(this._maze._ghostStartPosition, Direction.WEST, "inky"),
            new Ghost(this._maze._ghostStartPosition, Direction.WEST, "clyde")
        ]
    }

    /**
     * @returns {Maze} the Maze of the game
     */
    get maze() { return this._maze; }

    /**
     * @returns {Pacman} the unique Pacman of the game
     */
    get pacman() { return this._pacman; }

    /**
     * @returns {Ghost} the unique Ghost of the game
     */
    get ghosts() { return this._fantomes; }

    /**
     * @returns {Integer} the current score
     */
    get score() { return this._score; }

    /**
      * @returns {Integer} the maximum score obtained
      */
    get highScore() { return this._highScore; }

    /**
      * @returns {Integer} the last Dot removed
      */
    get removeDot() { return this._removeDot; }
    
    /**
     * This method will move the Pacman. Special case: 
     * If a change direction has been requested and it is possible 
     * to go in the desired direction, then this change of direction 
     * must be made effective before moving the Pacman.
     * Also checks if the pacman should fit into the glass hole
     */
    moveSprites() {

        if (this._pacman.askedToChangeDirection &&
            this._maze.canWalkOn(this._pacman.position.nextPosition(this._pacman._askedDirection))) {
            this._pacman.changeDirection();
            this._pacman.move();
            if (this._maze.getDotLayerTile(this._pacman.position) != undefined) {
                if (this._maze.getDotLayerTile(this._pacman.position)._isEnergizer) {
                    this._removeDot = this._pacman.position; // dernière position
                    this._maze.pick(this._pacman.position) // enlevement
                    this._score = this._score + 100; // update score +100
                } else if (!this._maze.getDotLayerTile(this._pacman.position)._isEnergizer) {
                    this._removeDot = this._pacman.position; // dernière position
                    this._maze.pick(this._pacman.position) // enlevement
                    this._score = this._score + 10; // update score +10
                }
            }
        } else if (this._maze.canWalkOn(this._pacman.position.nextPosition(this._pacman.direction))) {
            this._pacman.move();
            if (this._maze.getDotLayerTile(this._pacman.position) != undefined) {
                if (this._maze.getDotLayerTile(this._pacman.position)._isEnergizer) {
                    this._removeDot = this._pacman.position; // dernière position
                    this._maze.pick(this._pacman.position) //enlevement
                    this._score = this._score + 100; // update score +100
                } else if (!this._maze.getDotLayerTile(this._pacman.position)._isEnergizer) {
                    this._removeDot = this._pacman.position; // dernière position
                    this._maze.pick(this._pacman.position) // enlevement
                    this._score = this._score + 10; // update score +10
                }
            }

        } else if (this._pacman.position._column == 0) {
            this._pacman.position._column = this._maze.nbColumns - 1;
            console.log(this._pacman.position._column)
        } else if (this._pacman.position._column == this._maze.nbColumns - 1) {
            this._pacman.position._column = 0;
        }



        for (let i = 0; i < this._fantomes.length; i++) {
            if (this._fantomes[i].askedToChangeDirection &&
                this._maze.canWalkOn(this._fantomes[i].position.nextPosition(this._fantomes[i]._askedDirection))) {

                this._fantomes[i].notifyIsBlocked();
                this._fantomes[i].move();
            } else if (this._maze.canWalkOn(this._fantomes[i].position.nextPosition(this._fantomes[i].direction))) {
                this._fantomes[i].move();
            } else {
                this._fantomes[i].notifyIsBlocked();
            }


        }

        for (let j = 0; j < this._fantomes.length; j++) {
            if (this._fantomes[j].canEat(this._pacman)) {
                this.isGameOver();
                this._pacman.hasBeenEaten();
                this._pacman.respawn();
                for (let i in this._fantomes) {
                    this._fantomes[i].respawn()
                }
                break;
            }
        }

    }
    /**
     * the game is over if the Pacman has no life left
     * @returns true if the pacman has no more life

     */
    isGameOver() {
        return this._pacman._nbLives == 0;
    }
    /**
     * if the game is over, add a restart button which, when clicked, 
     * will reset the game.
     */
    restartButton() {
        if (this.isGameOver) {
            $("#vie").append(
                $('<button>').attr({
                    id: "restartGame",
                    class: "boutons"
                }).text("Restart").click(() => {
                    $(`#restartGame`).remove();
                    this._gameCtrl.startHasBeenRequested();
                })
            );
            this._pacman._nbLives = PACMAN_LIFE;
            this._score = 0;
        }
    }
    /**
     * 
     * @returns true if pacman has been eaten (if he's dead)
     */
    pacmanHasBeenEaten() {
        return this._pacman.isDead;
    }
    /**
     * reset position, movement and isDead properties for all sprites
     * stake.
     */
    respawn() {
        this._pacman._direction.respawn();
        this._pacman._position.respawn();
    }
    /**
     * This function compares the current score with the best score. If the score
     * current is better, then it should be saved (in the instance and in the localstorage).
     */
    saveScore() {
        if (localStorage.getItem("highScore") < this._score) {
            this._highScore = this._score;
            localStorage.setItem("highScore", this._highScore)
        }
    }
    /**
     * Used to find out if the current level has ended
     * @returns true if there is no dot left in layer number 2
     */
    lvlSucceed() {
        return this._maze.isEmpty();
    }

    /**
     * When this function is called, a new labyrinth is created and the
     * position and direction of the characters are reset to initial values.
     */
    nextLevel() {
        this._pacman.respawn();
        for (let i in this._fantomes) {
            this._fantomes[i].respawn()
        }
        new Maze(RAW_MAZE);
    }
}


