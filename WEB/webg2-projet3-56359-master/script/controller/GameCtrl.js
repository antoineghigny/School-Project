/**
 * the game controller
 */
class GameCtrl {

    constructor() {
        this._game = new Game(RAW_MAZE, this);
        this._view = new GameView(this._game, this)
        this._maze = new Maze(RAW_MAZE);
        this._pacmanCtrl = new PacmanCtrl(this._game.pacman);
        this._pacmanView = new PacmanView(this._pacmanCtrl);
        this._pacman = new Pacman(this._maze.pacmanStartPosition, Direction.WEST, "pacman");

    }
    /**
     * When this method is called, launch the run () method.
     */
    startHasBeenRequested() {
        this.run();
    }
    /**
     * Creates an interval that refreshes all methods in it every 0.3 seconds.
     * if the level is finished, change level and reset everything.
     * if the game is over, reset the game, and display the restart 
     * button along with a message in the console indicating defeat.
     */
    run() {
        this._timer = setInterval(() => {
            this._game.moveSprites();
            this._view.updateFrame();
            this._view.updateLives();
            this._game.saveScore();
            this._view.displayGameOver();

            if (this._game.lvlSucceed()) {
                this._game.nextLevel();
                this._view.nextLevel();
            }

            if (this._game.isGameOver()) {
                this._game.nextLevel();
                this._view.nextLevel();
                this._game.restartButton();
                console.log("Vous avez perdu :(");
                clearInterval(this._timer);
            }

        }, 300);
    }
}

