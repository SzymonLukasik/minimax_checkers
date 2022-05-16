/**
 * Class providing simple operations on objects representing board positions,
 * i.e. Position objects and Arrays of form [x, y].
 */
export class Position {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    /**
     * If given Position object, returns it.
     * Otherwise, assumes that the Array of form [x, y] was given,
     * creates a new Position from it and returns it.
     * @param {*} object - Position or Array of form [x, y]
     */
    static from(object) {
        if (object.x === undefined)
            return new Position(...object);
        return object;
    }

    /**
     * Returns a possition being middle point between this and other.
     * @param {*} other - Position or Array of form [x, y]
     */
     middle(other) {
        other = Position.from(other);
        var mid = (a, b) => Math.floor((a + b) / 2);
        return new Position (mid(this.x, other.x), mid(this.y, other.y));
    }
    
    /**
     * Returns a possition being middle point between a and b.
     * @param {*} a - Position or Array of form [x, y]
     * @param {*} b - Position or Array of form [x, y]
     * @returns 
     */
    static middle(a, b) {
        [a, b] = [Position.from(a), Position.from(b)];
        return a.middle(b);
    }

    /**
     * Compares this with other. Other might be null.
     * @param {*} other - Position or Array of form [x, y] or null
     */
     isEqual(other) {
        if (other === null) return false;
        other = Position.from(other);
        return  this.x === other.x && this.y === other.y;
    }

    /**
     * Compares two positions. Nulls accepted.
     * @param {*} a - Position or Array of form [x, y] or null
     * @param {*} b - Position or Array of form [x, y] or null
     */
    static areEqual(a, b) {
        if (a === null && b === null) return true;
        if (a === null || b === null) return false;
        [a, b] = [Position.from(a), Position.from(b)];
        return a.isEqual(b);
    }

    /**
     * Returns a position object representing, distances between this and other
     * on x-axis and y-axis.
     */
    axisDist(other) {
        other = Position.from(other);
        var dist = (a, b) => Math.abs(a - b);
        return new Position(dist(this.x, other.x), dist(this.y, other.y))
    }

    /**
     * Checks whether a position is playable.
     */
    isPlayable() {
        return (this.x + this.y) % 2 === 0 ? true : false;
    }

    /**
     * Converts received pretty string e.g. 'B3' string to Position (2, 1)
     * @param {*} positionString - string of form [column letter][row number]
     * @returns Position of form (row index, column index)
     */
    static fromPrettyString(string) {
        return new Position(
            string.charCodeAt(1) - "1".charCodeAt(0), 
            string.charCodeAt(0) - "A".charCodeAt(0));
    }

    /**
     * Converts received position e.g. (2, 1) string to pretty string 'B3'
     * @param {*} position - position of form (row index, column index)
     * @returns string of form [column letter][row number]
     */
    toPrettyString() {
        return String.fromCharCode(
            this.y + "A".charCodeAt(0),
            this.x + "1".charCodeAt(0)
        );
    }
}

/**
 * Enables indexing 2D Arrays with Position or Arrays of form [x, y].
 */
// eslint-disable-next-line
Array.prototype.atPosition = function(position) {
    position = Position.from(position);
    return this[position.x][position.y];
};