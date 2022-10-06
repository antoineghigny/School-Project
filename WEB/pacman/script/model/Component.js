/**
 * make a connection with the tiles
 */
class Component {

    /**
     * 
     * @param {string} id id unique tile’s id
     */
    constructor(id) {
        this._id = id;
    }

    /**
     * @returns {string} the id of the pacman
     */
    get id() { return this._id; }
}

