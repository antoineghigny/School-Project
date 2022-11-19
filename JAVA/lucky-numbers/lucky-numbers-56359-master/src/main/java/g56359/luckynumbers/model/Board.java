package g56359.luckynumbers.model;

/**
 * Antoine Ghigny
 *
 * @author g56359 - luckyNumbers
 *
 */
public class Board {

    private final Tile[][] board;

    public Board() {
        board = new Tile[4][4];
    }

    public int getSize() {
        return board.length;
    }

    /**
     * will return true if the tile is located in the 4x4 array, if the position
     * of the tile is located outside the array, will return false
     *
     * @param pos the position of the tile
     *
     * @return true if the position is present in the array and false if the
     * position is not present in deans.
     *
     */
    public boolean isInside(Position pos) {

        return (pos.getColumn() <= getSize() - 1)
                && (pos.getColumn() >= 0)
                && (pos.getRow() <= getSize() - 1)
                && (pos.getRow() >= 0);

    }

    /**
     *
     * uses column and row getter to create a tile position and return it
     *
     * @param pos the position of the tile
     * @return returns the position of the tile
     *
     */
    public Tile getTile(Position pos) {
        Tile positionDemande = board[pos.getRow()][pos.getColumn()];
        return positionDemande;
    }

    /**
     * @paramc tile The tile to put on the board (its value is between 1 and
     * 20).
     * @param pos the position of the tile
     * @return true if the tile can be placed respecting the rules of the game,
     * false if this is not the case. To return true, everything must be true.
     *
     *
     */
    public boolean canBePut(Tile tile, Position pos) {
        boolean left = position(tile, pos, 0, -1);
        boolean right = position(tile, pos, 0, +1);
        boolean up = position(tile, pos, +1, 0);
        boolean down = position(tile, pos, -1, 0);
        if (!(left && right && up && down)) {
            throw new IllegalArgumentException("La position n'est pas valide");
        }
        return left && right && up && down;
    }

    /**
     * each direction uses the position method by taking the tile, the position
     * and two integers which allow to check if the tile can be placed according
     * to the rules of the game (the tile must be greater than a tile coming
     * from the left in the row , the tile must be smaller than a tile being
     * placed to its right in the row. The tile must be larger than the tile
     * above it, and smaller than the tile below.
     *
     * @param tile The tile to put on the board (its value is between 1 and 20).
     * @param pos the position of the tile
     * @param dr the position which must vary in row to indicate the direction
     * @param dc the position which must vary in column to indicate the
     * direction
     * @return true if the tile meets the conditions to be placed in the desired
     * direction. false if not.
     *
     */
    public boolean position(Tile tile, Position pos, int dr, int dc) {
        int i = pos.getRow() + dr;
        int j = pos.getColumn() + dc;

        while (isInside(new Position(i, j)) && board[i][j] == null) {
            i = i + dr;
            j = j + dc;
        }

        if (!isInside(new Position(i, j))) {
            return true;
        }

        Tile newPosition = board[i][j];

        if (dc >= 1) {
            return tile.getValue() < newPosition.getValue();
        } else if (dr >= 1) {
            return tile.getValue() < newPosition.getValue();

        } else {
            return tile.getValue() > newPosition.getValue();

        }
    }

    /**
     * places a tile at the indicated position, if there is already a position,
     * the tile replaces the previous tile.
     *
     * @param tile The tile to put on the board (its value is between 1 and 20).
     * @param pos the position of the tile
     */
    public void put(Tile tile, Position pos) {
        int pos1 = pos.getRow();
        int pos2 = pos.getColumn();
        board[pos1][pos2] = tile;

    }

    /**
     * checks each cell of the array if there is an empty cell, if nothing is
     * empty, return true.
     *
     * @return true if the array is complete, false if the array is not complete
     *
     */
    public boolean isFull() {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board.length; j++) {
                if (board[i][j] == null) {
                    return false;
                }
            }
        }
        return true;
    }
}
