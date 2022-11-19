/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package g56359.luckynumbers.model;

/**
 *
 * @author antoi
 */
public class Tile {

    private int value;
    private boolean faceUp;

    public int getValue() {
        return value;
    }

    public boolean isFaceUp() {
        return faceUp;
    }

    public Tile(int value) {

        this.value = value;
    }

    void flipFaceUp() {
        if (!isFaceUp()) {
            this.faceUp = true;
        }
    }

    @Override
    public String toString() {
        return value + "";
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 17 * hash + this.value;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Tile other = (Tile) obj;
        if (this.value != other.value) {
            return false;
        }
        return true;
    }

}
