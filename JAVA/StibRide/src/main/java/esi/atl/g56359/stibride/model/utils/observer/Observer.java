package esi.atl.g56359.stibride.model.utils.observer;

import java.util.List;

/**
 * A class can implement the {@code Observer} interface when it wants to be
 * informed of changes in observable objects.
 *
 * @author jlc
 */
public interface Observer {
    /**
     * This function is called when the object is updated.
     */
    public void update(Object...args);
}
