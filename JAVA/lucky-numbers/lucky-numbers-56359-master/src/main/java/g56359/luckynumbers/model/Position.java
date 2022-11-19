package g56359.luckynumbers.model;

public class Position {

    private int row;
    private int column;

    /**
     *
     * @return the row of the position
     */
    public int getRow() {
        return row;
    }

    /**
     * @return the column of the position
     */
    public int getColumn() {
        return column;
    }

    /**
     *
     * @param row the row of the position
     * @param column the column of the position
     */
    public Position(int row, int column) {
        this.row = row;
        this.column = column;
    }
}
