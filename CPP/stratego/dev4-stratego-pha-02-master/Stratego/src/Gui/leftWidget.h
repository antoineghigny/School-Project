#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QPoint>
#include <QPixmap>
#include <QList>
#include <QWidget>
#include <controllergui.h>
#include <Pawn.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QStackedLayout>
#include "Parameter.h"
#include "PlacementChoice.h"
#include "deckgui.h"
#include "FileDropArea.h"
#include "DropFile.h"
#include "GraveyardArea.h"
#include "WinScreen.h"

/**
 * @brief The LeftWidget class a widget that has stack that contains the different widget.
 */
class LeftWidget : public QWidget, public Observer
{
    Q_OBJECT

  public:

    explicit LeftWidget(MainWindow * parent = nullptr,
                  ControllerGui * controller = nullptr);
  private:

    ControllerGui * _controller;
    QStackedLayout * _stack;

    /**
     * @brief setUpPlacementWidget set up the widgat that will ask the player the type of placement.
     *
     * It will create the button and connect them to a slot. The type of placement means if the player to put
     * the pawns manualy or with a file.
     */
    void setUpPlacementWidget();

    /**
     * @brief setUpWinScreenWidget set up the widget that display the winner and ask if the players want to restart.
     * @param mw the main window for the case where the player want to exit the application.
     * @param ctrl the ocntroller.
     */
    void setUpWinScreenWidget(MainWindow * mw, ControllerGui * ctrl);

  public slots:

    /**
     * @brief setDeck set the current widget to the one where the deck will be display
     * and the player will place them one by one.
     */
    void setDeck();

    /**
     * @brief setDropFile set the current widget to the one where it will ask a file
     * to set up the board.
     */
    void setDropFile();

    /**
     * @brief setPlacementChoice set the current widget to the one where it will ask
     * the player how he wants to put the pawn.
     */
    void setPlacementChoice();

    /**
     * @brief setGraveyardArea set the current widget to the one where it will display all the pawn that are dead.
     */
    void setGraveyardArea();

    /**
     * @brief setParameter set the current widget to the one where it will ask if the players want to play in easy or normal mode.
     */
    void setParameter();

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
     * @brief updateView update the leftwidget depending the current state of the game.
     * @param m the model
     */
    void updateView(Model * m);

    /**
     * @brief fillGraveyard fill the graveyard with the new dead pawn.
     *
     * When there are dead pawn, call the graveyardArea to add the new dead pawn.
     *
     * @param duleResult the result of the duel.
     * @param boardSize the size of the pawn to get the correct size of the image
     * that will be display in the graveyard.
     */
    void fillGraveyard(const int duleResult, const int boardSize);

    /**
     * @brief setWinScreen set the current widget to the one where it will display the winner
     * and ask if the players want to start a new game.
     */
    void setWinScreen();
};

#endif // LEFTWIDGET_H
