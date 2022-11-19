package esi.atl.g56359.stibride.view;

import esi.atl.g56359.stibride.model.dto.FavoriteDto;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.utils.LangState;
import esi.atl.g56359.stibride.presenter.Presenter;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.ObservableSet;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import org.controlsfx.control.SearchableComboBox;

public class FxmlController {
    @FXML
    private TableView<StationDto> table;

    @FXML
    private TableColumn<StationDto, String> lineCol;

    @FXML
    private TableColumn<StationDto, String> stationCol;

    @FXML
    private Label nbStation;

    @FXML
    private Label statusSearch;

    @FXML
    private Label chgLine;

    @FXML
    private Button search;

    @FXML
    private Button addToFavorite;

    @FXML
    private Menu menuFavorite;


    @FXML
    private Menu menuEdit;

    @FXML
    private MenuItem quit;

    @FXML
    private SearchableComboBox<StationDto> searchOrigine;

    @FXML
    private SearchableComboBox<StationDto> searchDestination;

    @FXML
    private TextField favoriteName;

    private ObservableList<StationDto> pathStations;
    private Presenter presenter;

    /**
     * When the user clicks the search button, the presenter will search for flights between the two airports selected by
     * the user.
     *
     * @param event The event that triggered the method.
     */
    @FXML
    private void search(ActionEvent event) {
        presenter.search(searchOrigine.getValue(), searchDestination.getValue());
    }

    /**
     * The function favorite() is called when the user clicks on the button "Add to favorites". It gets the values of the
     * two ComboBoxes and the text of the TextField and calls the function addFavorite() of the presenter
     *
     * @param event The event that triggered the handler.
     */
    @FXML
    private void favorite(ActionEvent event) {
        System.out.println(searchOrigine.getValue());
        System.out.println(searchDestination.getValue());
        favoriteName.getText();
        presenter.addFavorite(searchOrigine.getValue(), searchDestination.getValue(), favoriteName.getText());
    }

    /**
     * This function returns the statusSearch label.
     *
     * @return The statusSearch label.
     */
    public Label getStatusSearch() {
        return statusSearch;
    }

    /**
     * This function returns the number of stations
     *
     * @return The number of stations.
     */
    public Label getNbStation() {
        return nbStation;
    }

    /**
     * This function sets the presenter for the view.
     *
     * @param presenter The presenter that will be used to control the view.
     */
    public void setPresenter(Presenter presenter) {
        this.presenter = presenter;
    }

    /**
     * This function sets the pathStations variable to the newPath variable.
     *
     * @param newPath The new path to be set.
     */
    public void setPathStations(ObservableList<StationDto> newPath) {
        pathStations.setAll(newPath);
    }


    /**
     * It clears the menu, then adds a disabled menu item if there are no favorites, or adds a menu item for each favorite
     *
     * @param allFavorites a set of FavoriteDto objects
     */
    public void setMenuFavorite(ObservableSet<FavoriteDto> allFavorites) {
        menuFavorite.getItems().clear();
        if (allFavorites.isEmpty()) {
            MenuItem menuItem = new MenuItem("Aucun trajet pour l'instant");
            menuFavorite.getItems().add(menuItem);
            menuItem.setDisable(true);
        } else {
            allFavorites.forEach(v -> {
                var item = new MenuItem(v.getKey());
                item.setOnAction(e -> presenter.showFavoriteStage(v.getKey()));
                menuFavorite.getItems().add(item);
            });
        }
    }

    /**
     * It clears the menuEdit menu, adds two menu items to it, and sets the action of each menu item to a function that
     * calls the presenter's setLanguage function
     */
    public void setMenuEdit() {
        menuEdit.getItems().clear();
        MenuItem nd = new MenuItem("Stations en neerlandais");
        MenuItem fr = new MenuItem("Stations en français");

        nd.setOnAction(e -> presenter.setLanguage(getLanguage(nd.getText())));
        fr.setOnAction(e -> presenter.setLanguage(getLanguage(fr.getText())));

        menuEdit.getItems().add(fr);
        menuEdit.getItems().add(nd);
    }

    public LangState getLanguage(String sort) {
        switch (sort) {
            case "Stations en neerlandais":
                return LangState.ND;
            //  case "Stations en français":
            //    return LangState.ND;
            default:
                return LangState.FR;
        }
    }


    /**
     * It initializes the table, the comboboxes, the menus and the quit button
     *
     * @param allStations  an ObservableSet of all the stations in the database.
     * @param allFavorites the list of all favorites
     */
    public void initialize(ObservableSet<StationDto> allStations, ObservableSet<FavoriteDto> allFavorites) {
        // It creates an observable list of stations that will be used to display the path in the table.
        pathStations = FXCollections.observableArrayList();
        stationCol.setCellValueFactory(new PropertyValueFactory<>("name"));
        lineCol.setCellValueFactory(new PropertyValueFactory<>("linesToString"));
        table.setItems(pathStations);

        searchOrigine.setItems(FXCollections.observableArrayList(allStations));
        searchDestination.setItems(FXCollections.observableArrayList(allStations));
        searchOrigine.getSelectionModel().selectFirst();
        searchDestination.getSelectionModel().selectLast();

        setMenuFavorite(allFavorites);
        setMenuEdit();

        quit.setOnAction(e -> {
            Platform.exit();
            System.exit(0);
        });
    }

    /**
     * > The function changeLanguage is called when the language is changed. It clears the selection of the two ComboBoxes,
     * sets their items to an empty list, then sets their items to the list of all stations, and finally selects the first
     * and last items of the ComboBoxes
     *
     * @param allStations ObservableSet<StationDto>
     */
    public void changeLanguage(ObservableSet<StationDto> allStations) {
        System.out.println("changeLanguage");
        searchOrigine.getSelectionModel().clearSelection();
        ;
        searchDestination.getSelectionModel().clearSelection();
        ;

        searchOrigine.setItems(FXCollections.observableArrayList());
        searchDestination.setItems(FXCollections.observableArrayList());

        searchOrigine.setItems(FXCollections.observableArrayList(allStations));
        searchDestination.setItems(FXCollections.observableArrayList(allStations));
        searchOrigine.getSelectionModel().selectFirst();
        searchDestination.getSelectionModel().selectLast();
    }
}
