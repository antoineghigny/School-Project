/**
 * A tile is a fixed Pacman maze component like a wall or a dot.
 */
class Tile extends Component {
    /**
     * To be created, a Tile just need an id.
     * @param {string} id id unique tile’s id
     */
    constructor(id) {
        super(id);
    }

    /**
     * @returns {string} the id of the tile
     */
    get id() { return this._id; }
}

