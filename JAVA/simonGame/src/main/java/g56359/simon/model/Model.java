package g56359.simon.model;

import g56359.simon.observer.Observable;
import g56359.simon.observer.Observer;
import javafx.animation.PauseTransition;
import javafx.util.Duration;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author Antoine Ghigny - g56359
 */
public class Model implements Observable {

    private final List<Observer> observers;

    private final ArrayList<Color> actualList = new ArrayList<>();
    private final ArrayList<Color> lastList = new ArrayList<>();
    private final ArrayList<Color> longestList = new ArrayList<>();

    private int step = 0;
    private State state;

    public Model() {
        this.observers = new ArrayList<>();
    }
    /**
     * Method for creating a random (enumeration) color sequence.
     */

    public void newSequence() {
        colorSequence();
        notifyObservers();
    }

    public void colorSequence() {
        int randomColor = new Random().nextInt(Color.values().length);
        actualList.add(Color.values()[randomColor]);
    }

    /**
     * Method used to compare a color to the corresponding color in the list.
     *
     * @param colors an enumeration (in this case, one of the colors of the game)
     */
    public void verification(Color colors) {
        if (colors != actualList.get(step)) {
            fail();
        }
        // to update the record in real time (put it in the longestList method if you only want this to be the case at gameOver
        if (actualList.size() > longestList.size() && colors == actualList.get(step)) {
            longestList.clear();
            longestList.addAll(actualList);
        }
        step++;

        if (step == actualList.size()) {
            step = 0;
            colorSequence();
            PauseTransition pause = new PauseTransition(Duration.seconds(0.3));
            pause.setOnFinished(event -> notifyObservers());
            pause.play();
        }
    }

    /**
     * The method that will be called when the user presses the start button.
     */
    public void startMethod() {
        state = State.START;
        actualList.clear();
        step = 0;
        newSequence();
    }

    /**
     * Method that will be called when pressing the longest button.
     */
    public void longestMethod() {
        state = State.LONGEST;
        notifyObservers();
    }

    /**
     * Method that will be called when pressing the last button.
     */
    public void lastMethod() {
        state = State.LAST;
        lastList.clear();
        lastList.addAll(actualList);
        notifyObservers();
    }

    /**
     * Method which encountered the state attribute at "loose", the nbrTimes attribute at 1s
     */
    public void fail() {
        state = State.LOOSE;
        step = 0;
        notifyObservers();
    }

    /**
     * Method which, when called, retrieves the longest list entered by the user.
     *
     * @return the highest color list entered by the user
     */
    public ArrayList<Color> getLongestList() {
        return longestList;
    }

    public ArrayList<Color> getLastList() {
        return lastList;
    }

    /**
     * Allows you to retrieve the list of colors
     *
     * @return the color list
     */
    public ArrayList<Color> getActualList() {
        return actualList;
    }

    @Override
    public void registerObserver(Observer obs) {
        if (!observers.contains(obs)) {
            observers.add(obs);
        }
    }

    @Override
    public void removeObserver(Observer obs) {
        observers.remove(obs);
    }

    @Override
    public void notifyObservers() {
        for (Observer obs : observers) {
            obs.update(state);
        }
    }

}
