package view;

import javafx.scene.control.Button;

public class ButtonFX extends Button {

    private final int row;
    private final int column;

    /**
     * Overloading the ButtonFX constructor, we give it a row and a column.
     * @param row the row where the button is located
     * @param column the column where the button is located
     */
    public ButtonFX(int row, int column) {
        super();
        this.row = row;
        this.column = column;
    }

    /**
     * Getter of the row
     * @return the row where the button is located
     */
    public int getRow() {
        return row;
    }

    /**
     * Getter of the column
     * @return the column where the button is located
     */
    public int getColumn() {
        return column;
    }

}