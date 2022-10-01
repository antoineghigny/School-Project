/**
 * The layers (Layer) each group together a set of tiles in order to
 * constitute a level. In our case, we are going to have two layers. 
 * The first made up ofwalls with which we will have to manage the collision. 
 * The second consists of elements with
 * which Pacman can interact with, that is, the gums
 */

class Layer {

    /**
     * @param {*} nbRows the number of row
     * @param {*} nbColumns the number of column
     */
    constructor(nbRows, nbColumns) {
        this._nbRows = nbRows;
        this._nbColumns = nbColumns;
        this._tiles = Array(nbRows).fill().map(() => Array(nbColumns));
    }

    /**
      * @returns {Integer} the number of rows
      */
    get nbRows() { return this._nbRows; }

    /**
      * @returns {Integer} the number of columns
      */
    get nbColumns() { return this._nbColumns; }
    /**
     * 
     * @param {Position} pos the position
     * @returns true if the position belongs to the board=
     * layer (row / column between 0 and number of rows / columns -1).
     */
    contains(pos) {
        return pos.row >= 0 && pos.row <= this._nbRows - 1 &&
            pos.column >= 0 && pos.column <= this._nbColumns - 1;
    }
    /**
     * Place a tile in the indicated position
     * @param {*} pos the position
     * @param {*} tile the tile to lay
     */

    setTile(pos, tile) {
        this._tiles[pos.row][pos.column] = tile;
    }

    /**
     * return the tile to the position
     * @param {Position} pos the position
     * @returns the tile present on the layer at the given position
     */
    getTile(pos) {
        return this._tiles[pos.row][pos.column];
    }
    /**
     * if the tile at position is undefinied, returns true
     * @param { } pos the position
     * @returns true if the given position does contain a
     * tile and not a void
     */
    hasTile(pos) {
        return this._tiles[pos.row][pos.column] != undefined;
    }
}