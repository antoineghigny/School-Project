package esi.atl.g56359.stibride.view;

import esi.atl.g56359.stibride.model.Model;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.utils.RepositoryException;
import esi.atl.g56359.stibride.presenter.Presenter;
import javafx.collections.ObservableSet;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

public class FxmlControllerFavorite {

    @FXML
    private TextField name;

    @FXML
    private Button add;

    @FXML
    private Button delete;

    @FXML
    private Button search;
    @FXML
    private Text msg;

    @FXML
    private Text favoriteName;

    private Presenter presenter;

    /**
     * When the user clicks the search button, the presenter will search for the name the user entered.
     *
     * @param event The event that triggered the method.
     */
    @FXML
    private void search(ActionEvent event) throws RepositoryException {
        presenter.searchByName(name.getText());
    }

    /**
     * The delete function is called when the delete button is pressed. It calls the deleteFavorite function in the
     * presenter
     *
     * @param event The event that triggered the method.
     */
    @FXML
    private void delete(ActionEvent event) {
        presenter.deleteFavorite(name.getText());
    }


    /**
     * It updates the favorite with the new values.
     *
     * @param event The event that triggered the method call.
     */
    @FXML
    private void update(ActionEvent event) {
        System.out.println("entre update");
        System.out.println(name.getText());
        presenter.updateFavorite(favoriteName.getText(), name.getText());
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
     * This function sets the name of the favorite and the name of the contact.
     *
     * @param name The name of the favorite.
     */
    public void setName(String name) {
        favoriteName.setText(name);
        this.name.setText(name);
    }

    /**
     * It sets the text of a TextView to a message
     *
     * @param message the message to display
     */
    public void setMsgFavorite(String message) {
        if (message == null) {
            this.msg.setText("");
            return;
        }
        String fMsg;
        switch (message) {
            case Model.FAVORITE_ADD_FAIL_MAX:
                fMsg = "Vous avez atteint votre limite de trajet, merci d'en supprimer.";
                break;
            case Model.FAVORITE_REPO_ERROR:
                fMsg = "Une erreur est survenue, merci de vérifier votre saisie.";
                break;
            case Model.FAVORITE_DELETE_FAIL:
                fMsg = "Impossible de supprimer ce trajet.";
                break;
            case Model.INVALID_DATA:
                fMsg = "Les données indiquées sont invalides. Merci de réessayer.";
                break;
            case Model.FAVORITE_UPDATE_NO_CHANGES:
                fMsg = "Il n'y a pas eu de changement à mettre à jour.";
                break;
            default:
                fMsg = "";
        }
        this.msg.setText(fMsg);
    }
}
