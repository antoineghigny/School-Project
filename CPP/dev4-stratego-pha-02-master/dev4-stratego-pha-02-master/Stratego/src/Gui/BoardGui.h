#ifndef BOARDGUI_H
#define BOARDGUI_H

#include <QPoint>
#include <QPixmap>
#include <QList>
#include <QWidget>
#include "controllergui.h"
#include "Pawn.h"
#include "deckgui.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

/**
 * @brief The BoardGui class board of the game that will contain the pawn.
 */
class BoardGui : public QWidget, public Observer
{
    Q_OBJECT

  public:

    explicit BoardGui(MainWindow * parent = nullptr,
                      ControllerGui * controller = nullptr);

    /**
     * @brief placePawnFile A method that places a PawnGui in the
     * counter vector but also in the boardGui at position x, y
     * resize to match the size of the board whose image matches the pixmap.
     * @param x The x location of the pawn on the board.
     * @param y The y location of the pawn on the board.
     * @param pixmap The picture corresponding to the piece to be placed on the board.
     * @param team the team of the pawn
     */
    void placePawnFile(int x, int y, QPixmap pixmap, int team);

    /**
     * @brief clear Removes the PawnGui list and refreshes
     * the boardGui using the repaint() method
     */
    void clear();

  protected:
    /**
     * @brief mousePressEvent This event is called when the BoardGui is clicked.
     * If the state is set to PICK_PAWN, the timer is not active and the pawn is
     * in the model at position pos, the event is accepted. In this case, we will
     * retrieve the pawn at the clicked position, we will find the pawn in the vector.
     * If the pawn exists, it will be removed from the vector to become a pawn,
     * an update event will be launched to update the board to the location of the QRect.
     * We will then assign pixmap, team... Create a Qdrag to which we will assign a mimeData, a
     *  starting position and a pixmap.
     *  After that, the pawn will be inserted in the vector of pawns and update the position.

     * @param event The QMouseEvent that detects when a user clicks on the BoardGui.
     */
    void mousePressEvent(QMouseEvent * event) override;

    /**
     * @brief
     * dragEnterEvent When entering drag, this event is called
     *  If the state of the game is pickpawn, put the counter previously
     *  selected when clicking back into the current counter.
     *  Is called when the user takes the dragged pawn out of the board without dropping it,
     *  and ends up back on the board.
     *
     * @param event which is sent to a widget when a drag and drop action enters it
     */
    void dragEnterEvent(QDragEnterEvent * event) override;

    /**
     * @brief dragLeaveEvent When leaving drag, this event is called
     *
     * When the user drops the dragged pawn or takes the pawn out of the boardgui,
     * this event is called. If the game state is move_pawn, then the destination
     * position will be sent to the starting position and the path will be cancelled
     * in the model. The state of the game changes back to pick_pawn.
     *
     * @param event that is sent to a widget when a drag and drop action leaves it
     */
    void dragLeaveEvent(QDragLeaveEvent * event) override;

    /**
     * @brief dragMoveEvent When a pawnGui is in drag and moves, this method is called.
     * If the state of the game is set to setup, i.e. when an element is moved from the
     * DeckGui to the BoardGui, the piece is assigned its pixmap, id, inDeck, team.
     * If the state of the game is setup and the user can place his piece at the cursor position. T
     * he piece can be placed and the location under the cursor is highlighted
     * to get an idea of where the piece will be placed.
     * If the state of the game is movePawn and the location where the cursor is located
     * is a valid move position in the model. The pawn can then be dropped.
     *
     * @param event which is sent while a drag and drop action is in progress
     */
    void dragMoveEvent(QDragMoveEvent * event) override;

    /**
     * @brief dropEvent If the state of the game is SET_UP, the piece can be placed and is added to the model board.
     * If the state of the game is MOVE_PAWN and the destination position is a valid destination,
     * the pawn can be placed and the caller moves the pawn in the model.
     *
     * @param event which is sent when a drag and drop action is completed
     */
    void dropEvent(QDropEvent * event) override;

    /**
     * @brief This function is triggered when the program needs to display
     * the elements. It displays the parts, the background image,
     * if we change the page, it also refreshes when we come back.
     * Also when we resize the page...

     * @param event Paint events are sent to widgets that need to update themselves,
     * for instance when part of a widget is exposed because a covering widget was moved.
     */
    void paintEvent(QPaintEvent * event) override;

  private:

    struct PawnGui
    {
        QPixmap pixmap;
        QRect rect;
        int id;
        bool inDeck;
        int team;
    };

    ControllerGui * _controller;
    QTimer * _timer;
    QList<PawnGui> pawns;
    QRect _highlightedRect;
    QPixmap _hideRed;
    QPixmap _hideBlue;
    Position * _firstPos;

    /**
     * @brief updateView update the leftwidget depending the current state of the game.
     *
     * @param m the model
     */
    void updateView(Model * m) override;

    /**
     * @brief findPixmap A method of giving a pixmap to each pawn.
     * During the game, each piece can have a visible or hidden pixmap.
     *
     * If the pawn at the position is visible and the current player
     * is different from the pawn's team, flip the pawn's pixmap.
     * If the pawn is not visible. Flip the hidden blue pixmap
     * if the current player is 1, the hidden red
     * if the current player is 0.
     *
     * @param currentPlayer the current player
     * @param pos the position of the pawn
     * @param pawn the pawnGui
     * @return a pixmap corresponding to its current state in the model.
     * Whether the pawn should be visible, invisible,
     * if the current player is the same as the pawn's team.
     */
    QPixmap findPixmap(const Team currentPlayer, const Position pos,
                       const PawnGui pawn) const;

    /**
     * @brief updateDuel update the board if a duel happen.
     *
     * @param pos the position where there is a duel.
     * @param duelResult the result of the duel.
     */
    void updateDuel(const Position pos, const int duelResult);

    /**
     * @brief deletePawnGui delete the pawn at the position on the interface.
     *
     * @param pos the position of the pawn that will be deleted.
     * @return the pawn that has been deleted.
     */
    PawnGui deletePawnGui(const Position & pos);

    /**
     * @brief targetPawn Retrieves a rectangle of points corresponding to
     * the position in the BoardGui.
     *
     * @param position The point to find the rectangle to which this point belongs.
     * @return Le point auquel il faut trouver le rectangle dont ce point appartient.
     */
    const QRect targetPawn(const QPoint & position) const;

    /**
     * @brief findPawn Find the location of the pawn in the pawn vector.
     *
     * @param pieceRect the location of the pawnGui in the BoardGui.
     * @return Returns the index of the counter in the vector
     * if the location of the pawn is found in the location
     * of the pawn in the list (QRect), -1 in the opposite case.
     */
    int findPawn(const QRect & pieceRect) const;

    /**
     * @brief setupBoardForFile display all the pawn if a file is use to put the pawn.
     */
    void setupBoardForFile();

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
     * @brief getPawnSize Gets the size of the pawn
     *
     * @return a int wich is the size of the pawn
     */
    int getPawnSize() const;

  private slots:

    /**
     * @brief refresh refresh the board to show the correct image?
     */
    void refresh();
};

#endif // BOARDGUI_H
