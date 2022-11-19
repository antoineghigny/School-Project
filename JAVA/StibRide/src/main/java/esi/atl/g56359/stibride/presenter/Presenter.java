package esi.atl.g56359.stibride.presenter;

import esi.atl.g56359.stibride.model.Model;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.utils.GameState;
import esi.atl.g56359.stibride.model.utils.LangState;
import esi.atl.g56359.stibride.model.utils.RepositoryException;
import esi.atl.g56359.stibride.model.utils.observer.Observable;
import esi.atl.g56359.stibride.model.utils.observer.Observer;
import esi.atl.g56359.stibride.view.View;
import javafx.application.Platform;
import javafx.collections.ObservableSet;

import java.io.IOException;
import java.util.List;

public class Presenter implements Observer {
    private final Model model;
    private final View view;

    public Presenter(Model model, View view) {
        this.model = model;
        this.view = view;
    }

    public void initialize() {
        view.initialize(model.getAllStations(), model.getAllFavorites());
    }

    public void search(StationDto source, StationDto destination) {
        model.setMsgFavorite(null);
        try {
            view.closeFavorite();
            model.search(source, destination);
        } catch (RepositoryException e) {
            throw new IllegalArgumentException("Impossible to search theses datas.");
        }
    }

    public void searchByName(String name) {
        model.setMsgFavorite(null);
        view.closeFavorite();
        model.searchByName(name);
    }

    public void showFavoriteStage(String name) {
        model.setMsgFavorite(null);
        try {
            view.showFavorite(name);
        } catch (IOException e) {
            throw new IllegalArgumentException("Impossible to load the FXML Controller for popup.");
        }
    }

    public void deleteFavorite(String name) {
        model.setMsgFavorite(null);
        try {
            model.deleteFavorite(name);
        } catch (RepositoryException e) {
            model.setMsgFavorite(Model.FAVORITE_REPO_ERROR);
            model.notifyObservers();
            return;
        }
        if (model.getMsgFavorite() == null) {
            view.closeFavorite();
        }
    }

    public void addFavorite(StationDto source, StationDto destination, String name) {
        model.setMsgFavorite(null);
        try {
            model.addFavorite(source, destination, name);
        } catch (RepositoryException e) {
            model.setMsgFavorite(Model.FAVORITE_REPO_ERROR);
            model.notifyObservers();
            return;
        }
        if (model.getMsgFavorite() == null) {
            view.closeFavorite();
        }
    }

    /**
     * Update the favorite with the given name to have the given text.
     *
     * @param name The name of the favorite to update.
     * @param text The text to be saved
     */
    public void updateFavorite(String name, String text) {
        model.updateFavorite(name, text);
    }

    /**
     * The setLanguage function sets the language of the model.
     *
     * @param language The language to use for the application
     */
    public void setLanguage(LangState language) {
        model.updateLanguage(language);
    }

    @Override
    public void update(Object... args) {
        Platform.runLater(() -> {
            view.changeLanguageComboBox(model.getAllStations());
            view.setMenuFavorite(model.getAllFavorites());
            view.setPathStations(model.getPathStations());
            view.setNbStation(model.getPathStations().size());
            view.setStatusSearch(model.isDoneSearch());
            view.setMsgFavorite(model.getMsgFavorite());
        });
    }
}
