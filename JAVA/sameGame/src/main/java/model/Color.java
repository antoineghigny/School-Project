package model;

/**
 * The Color enumeration has all possible colours of the tiles
 */
public enum Color {

    GREEN("#6bb14c"),
    RED("#ea4c4b"),
    YELLOW("#f8cb24"),
    BLUE("#22a7b2"),
    PURPLE("#A051DC");

    public final String colorString;

    /**
     * The constructor of the Color class
     * @param colorString the given color.
     */
    Color(String colorString) {
        this.colorString = colorString;
    }

    /**
     * The colorString getter.
     *i @return the string present in each enumeration
     * (which will allow the tile to be coloured in the javafx view.
     */
    public String getColorString() {
        return colorString;
    }
}
