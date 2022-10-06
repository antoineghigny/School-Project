/**
 * the Dot class allows you to define what a ball is, if it is energy or not.
 */
class Dot extends Tile{

    /**
     * 
     * @param {*} id the id of the dit
     * @param {*} isEnergizer true ou false if the dot is energizer.
     */
    constructor(id, isEnergizer) {
        super(id);
        this._isEnergizer = isEnergizer;

    }
    /**
     * @returns {boolean} true or false depending on whether the Dot is energizer
     */
    get isEnergizer() { return this._isEnergizer; }
}

