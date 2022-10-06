/**
 * The direction class will allow us to describe the directions that can
 * take our sprites
 */
class Direction {

    /**
     * @param {*} deltaRow The delta on the vertical axis which describes the direction
     * @param {*} deltaColumn The delta on the horizontal axis which describes the direction.
     */
    constructor(deltaRow, deltaColumn) {
        this._deltaRow = deltaRow;
        this._deltaColumn = deltaColumn;
    }

    /**
     * @returns {string} the line of the requested direction
     */
    get deltaRow() { return this._deltaRow; }
    
    /**
     * @returns {Integer} the column of the requested direction
     */
    get deltaColumn() { return this._deltaColumn; }
}

Direction.NORTH = new Direction(-1, 0)
Direction.SOUTH = new Direction(1, 0)
Direction.WEST = new Direction(0, -1)
Direction.EAST = new Direction(0, 1)