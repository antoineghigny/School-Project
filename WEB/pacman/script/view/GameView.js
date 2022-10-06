/**
 * GameView will centralize the display of each component of our game;
 * the tiles, Pacman and the ghosts.
 */
class GameView {

    /**
     * Add a Start button which on click, launches the startHasBeenRequested 
     * function of the controller
     * Add the maximum score to the highScore id
     * Browse the 2 layers and display the Dot and the Wall
     * 
     * @param {*} game the game
     * @param {*} GameCtrl the controller

     */
    constructor(game, GameCtrl) {
        this._game = game;
        this._gameCtrl = GameCtrl;
        let row = this._game.maze.nbRows;
        let column = this._game.maze.nbColumns;
        let getPacman = this._game.pacman;
        let getGhosts = this._game.ghosts;

        $("#vie").fadeIn().append(
            $('<button>').attr({
                id: "startGame",
                class: "boutons"
            }).text("Start").click(() => {
                this.startGame();
                this._gameCtrl.startHasBeenRequested();
            })
        );

        $(`#highScore`).text(this._game.highScore);

        $("<span>", {
            id: PACMAN_ID
        }).css({
            top: `${getPacman.position.row * SIZE_TILE}px`,
            left: `${getPacman.position.column * SIZE_TILE}px`,
        }).appendTo("#cadre");

        for (let i = 0; i < GHOSTS_ID.length; i++) {
            $("<span>", {
                id: GHOSTS_ID[i]
            }).css({
                top: `${getGhosts[i].position.row * SIZE_TILE}px`,
                left: `${getGhosts[i].position.column * SIZE_TILE}px`,
            }).appendTo("#cadre");
        }

        for (let lg = 0; lg < row; lg++) {
            for (let col = 0; col < column; col++) {
                let getWall = this._game.maze.getWallLayerTile(new Position(lg, col));
                let getDot = this._game.maze.getDotLayerTile(new Position(lg, col));

                if (!getWall) {
                    $("<span>", {
                    }).appendTo("#cadre");
                } else if (getWall) {
                    $("<span>", {
                        id: `wall${lg}-${col}`,
                        class: "wall"
                    }).css({
                        top: `${SIZE_TILE * lg}px`,
                        left: `${SIZE_TILE * col}px`,
                    }).appendTo("#cadre");
                }
                if (getDot) {
                    if (getDot.isEnergizer) {
                        $("<span>", {
                            id: `dot${lg}-${col}`,
                            class: "pac-dot energizer"
                        }).css({
                            top: `${SIZE_TILE * lg}px`,
                            left: `${SIZE_TILE * col}px`,
                        }).appendTo("#cadre");
                    } else {
                        $("<span>", {
                            id: `dot${lg}-${col}`,
                            class: "pac-dot"
                        }).css({
                            top: `${SIZE_TILE * lg}px`,
                            left: `${SIZE_TILE * col}px`,
                        }).appendTo("#cadre");
                    }
                }
            }
        }
    }

    get game() { return this._game; }

    /**
     * updates the current score, removes the dowry in 
     * which the pacman is located and modifies the position 
     * of the pacman and the ghosts
     */
    updateFrame() {
        let pacmanPosition = this._game.pacman.position;
        let getGhosts = this._game.ghosts;
        $("#pacman").css({
            top: `${pacmanPosition.row * SIZE_TILE}px`,
            left: `${pacmanPosition.column * SIZE_TILE}px`,
        });
        for (let i = 0; i < getGhosts.length; i++) {

            $(`#${GHOSTS_ID[i]}`).css({
                top: `${getGhosts[i].position.row * SIZE_TILE}px`,
                left: `${getGhosts[i].position.column * SIZE_TILE}px`,
            });
        }
        $(`#dot${this._game.pacman.position.row}-${this._game.pacman.position.column}`).remove();
        $(`#scoreActuel`).text(this._game.score);

    }
    /**
     * Updated the number of lives of the Pac-Man
     */
    updateLives() {
        let j = 0;
        $(`.lifeRemaining`).remove();
        for (let i = 0; i < this._game.pacman.nbLives; i++) {
            $("<span>", {
                id: `life${i}`,
                class: "lifeRemaining"
            }).css({
                top: `${0}px`,
                left: `${j}px`,
            }).appendTo("#vie");
            j += 20;
        }
    }
    /**
     * This method displays the value of the
     * highest score present in the Game instance.
     */
    displayGameOver() {
        let highScore = localStorage.getItem("highScore");
        $(`#highScore`).text(highScore);
    }
    /**
     * When this function is called, a new labyrinth is created and the
     * position and direction of the characters are reset to initial values.
     */
    nextLevel() {
        let row = this._game.maze.nbRows;
        let column = this._game.maze.nbColumns;
        $(".pac-dot").remove();

        $(`.wall`).remove();

        this._game._maze = new Maze(RAW_MAZE);

        for (let lg = 0; lg < row; lg++) {
            for (let col = 0; col < column; col++) {
                let getWall = this._game.maze.getWallLayerTile(new Position(lg, col));
                let getDot = this._game.maze.getDotLayerTile(new Position(lg, col));

                if (!getWall) {
                    $("<span>", {
                    }).appendTo("#cadre");
                } else if (getWall) {
                    $("<span>", {
                        id: `wall${lg}-${col}`,
                        class: "wall"
                    }).css({
                        top: `${SIZE_TILE * lg}px`,
                        left: `${SIZE_TILE * col}px`,
                    }).appendTo("#cadre");
                }
                if (getDot) {
                    if (getDot.isEnergizer) {
                        $("<span>", {
                            id: `dot${lg}-${col}`,
                            class: "pac-dot energizer"
                        }).css({
                            top: `${SIZE_TILE * lg}px`,
                            left: `${SIZE_TILE * col}px`,
                        }).appendTo("#cadre");
                    } else {
                        $("<span>", {
                            id: `dot${lg}-${col}`,
                            class: "pac-dot"
                        }).css({
                            top: `${SIZE_TILE * lg}px`,
                            left: `${SIZE_TILE * col}px`,
                        }).appendTo("#cadre");
                    }
                }
            }
        }
    }
    /**
     * Apply a fade out effect on startGame
     */
    startGame() {
        $(`#startGame`).fadeOut();
    }

}