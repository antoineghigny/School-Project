/**
 * 
 */
class Position {
    /**
     * 
     * @param {*} row the line of the position object
     * @param {*} column the column of the position object
     */
    constructor(row, column) {
        this._row = row;
        this._column = column;

    }

    /**
      * @returns {Integer} the unique row of the constructor
      */
    get row() { return this._row; }

    /**
      * @returns {Integer} the unique column of the constructor
      */
    get column() { return this._column; }

    /**
     * return a new position, add the position direction of row side and column side
     * @param {Direction} dir 
     * @returns returns the next position
     */
    nextPosition(dir) {
        return new Position(this._row + dir._deltaRow, this._column + dir._deltaColumn);
    }

}

