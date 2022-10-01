#ifndef DECKGUI_H
#define DECKGUI_H

#include <QListWidget>
#include "QLabel"
#include "QCheckBox"
#include "QPoint"
#include "controllergui.h"


/**
 * @brief The DeckGui class this class is a widget that will contain all the possible
 * if the player decide to put the pawn manualy on the board
 */
class DeckGui : public QListWidget
{
    Q_OBJECT

  public:

    explicit DeckGui(const int pawnSize, ControllerGui * ctrl, QWidget * parent);

    /**
     * @brief displayPawn display the pawn in the deck.
     *
     * When the current player choose to put manualy the pawn, all the pawn generated will be
     * display in the interface that the player can drag and drop on the board.
     */
    void displayPawn();

    static QString pawnMimeType()
    {
        return QStringLiteral("image/pawn");
    }

  protected:

    /**
     * @brief dragEnterEvent When entering drag, this event is called
     *
     * @param event which is sent to a widget when a drag and drop action enters it
     */
    void dragEnterEvent(QDragEnterEvent * event) override;

    /**
     * @brief dragMoveEvent If the mimeData of the event has the right format,
     * the pawn can be moved.
     *
     * @param event Event which is sent while a drag and drop action is in progress
     */
    void dragMoveEvent(QDragMoveEvent * event) override;

    /**
     * @brief startDrag we assign it an identifier corresponding to its location
     * in the list of widgets, a team... But also a mimeData, we launch a drag
     * by assigning it a pixmap, a starting position and we take the widget from the list.

     * @param supportedActions provides an event which is sent when a drag and drop action is completed.
     */
    void startDrag(Qt::DropActions supportedActions) override;

    /**
     * @brief _pawnSize the size of the pawnGui
     */
    int _pawnSize;

  private:
    /**
     * @brief _ctrl the controller of the GUI
     */
    ControllerGui * _ctrl;

    /**
     * @brief imagePixmap get the image of the pawn.
     *
     * Get the the path of the image corresponding the role of the pawn and the team of the pawn.
     *
     * @param role the role of the pawn.
     * @param team the team of the pawn.
     * @return a string which is the path to get the image of the pawn.
     */
    QString imagePixmap(const Role role, const Team team);

    /**
     * @brief addPawn add a pawn in the interface.
     *
     * A pawn is created with other data like the team, the role, the image of the paw,.
     *
     * @param pixmap the image of the pawn.
     * @param currentPlayer the
     */
    void addPawn(const QPixmap & pixmap, const int currentPlayer);
};

#endif // DECKGUI_H
