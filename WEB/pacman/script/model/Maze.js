/**
 * The maze class will allow you to define 2 keys, one for the walls and one for the dots
 */

class Maze {


    /**
     * The Maze constructor will define 2 layers, one for the walls 
     * and one for the dots, but also will define the initial position
     *  of the pacman and the ghosts.
     * @param {Maze} rawMaze the table that will allow you to build the labyrinth
     */
    constructor(rawMaze) {
        this._rawMaze = rawMaze;
        this._nbDots = 0;
        this._layer1 = new Layer(rawMaze.table.length, rawMaze.table[0].length);
        this._layer2 = new Layer(rawMaze.table.length, rawMaze.table[0].length);
        let i = 0;
        for (let lg = 0; lg < rawMaze.table.length; lg++) {
            for (let col = 0; col < rawMaze.table[lg].length; col++) {
                var pos = new Position(lg, col)
                if (rawMaze.table[lg][col] == 1) {
                    this._nbDots++;
                    this._layer1.setTile(pos, new Wall(`${i}`));
                } else if (rawMaze.table[lg][col] == 2) {
                    this._layer2.setTile(pos, new Dot(i, false));
                } else if (rawMaze.table[lg][col] == 3) {
                    this._layer2.setTile(pos, new Dot(i, true));
                } else if (rawMaze.table[lg][col] == 4) {
                    this._pacmanStartPosition = new Position(lg, col)
                } else if (rawMaze.table[lg][col] == 5) {
                    this._ghostStartPosition = new Position(lg, col)
                }
                i++;
            }

        }
    }

    /**
     * @returns {Maze} the Maze of the game
     */
    get maze() { return this._rawMaze; }

    /**
      * @returns {Integer} the number of rows
      */
    get nbRows() {
        return this._rawMaze.table.length;
    }

    /**
      * @returns {Integer} the number of columns
      */
    get nbColumns() {
        return this._rawMaze.table[0].length;
    }

    /**
      * @returns {Position} the starting position of the pacman
      */
    get pacmanStartPosition() {
        return this._pacmanStartPosition;
    }

    /**
      * @returns {Integer} the starting position of the ghost
      */
    get ghost() {
        return this._ghostStartPosition;
    }

    /**
     * After checking that the position is Dot contained in the layer, 
     * return the wall tile available at the given position
     * @param {*} pos 
     * @returns true if there is a Wall object at position
     */
    getWallLayerTile(pos) {
        if (this._layer1.contains(pos)) {
            if (this._layer1.hasTile) {
                return this._layer1.getTile(pos);
            }

        }
    }
    /**
     * After checking that the position is Dot contained in the layer, 
     * return the eraser tile available at the given position.
     * @param {*} pos 
     * @returns true if there is a Dot object at position
     */
    getDotLayerTile(pos) {
        if (this._layer2.contains(pos)) {
            if (this._layer2.hasTile) {
                return this._layer2.getTile(pos);
            }

        }
    }
    /**
     * checks if the position is contained in the maze 
     * and if there is no tile at the indicated position
     * @param {*} position 
     * @returns returns true if the position is part of the maze 
     * and there is no collision with a wall at the given position, false otherwise.
     */
    canWalkOn(position) {
        return (this._layer1.contains(position)
            && !this._layer1.hasTile(position));
    }
    /**
     * checks if the position is Dot located in layer number 2 
     * and if there is indeed a Dot object at the indicated position
     * @param {*} position 
     * @returns – returns true if the position is part of the maze 
     * and there is an eraser to take.
     */
    canPick(position) {
        return this._layer2.contains(position)
            && this._layer2.hasTile(position);
    }
    /**
     * if there is a Dot at the indicated position, the last tile 
     * is the Dot at that position, and the undefined is set at the indicated position.
     * @param {*} position 
     * @returnsreturns the eraser (normal or energetic) which is 
     * at the given position. Throw an error if there is nothing.
     */
    pick(position) {
        if (this._layer2.hasTile(position)) {
            let dernièreTuile = this._layer2.getTile(position);
            this._layer2.setTile(position, undefined);
            return dernièreTuile;
        }
        throw ("Il n'y a pas de gommes à cet emplacement !")
    }
    /**
     * Iterates the array and if there is a Dot at the indicated position
     * increments the counter, returns true if there is no more Dot.
     * @returns true if there is no more dot in the array layer number 2.
     */
    isEmpty() {
        let compteur = 0;
        for (let lg = 0; lg < this._rawMaze.table.length; lg++) {
            for (let col = 0; col < this._rawMaze.table[lg].length; col++) {

                if (this._layer2.hasTile(new Position(lg, col))) {
                    compteur++;
                }

            }
        }
        return compteur == 0;
    }
}