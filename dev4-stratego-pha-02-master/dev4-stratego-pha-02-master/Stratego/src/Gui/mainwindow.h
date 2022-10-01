#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "QCheckBox"
#include "QLabel"

#include "Observer.h"

class ControllerGui;
class DeckGui;
class BoardGui;
class LeftWidget;
class GraveyardsGui;
class Rules;

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace ui
{
class MainWindow;
}

/**
 * @brief The MainWindow class the main window of the application.
 */
class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

  public:

    explicit MainWindow(QWidget * parent = nullptr,
                        ControllerGui * controller = nullptr);

    /**
     * @brief updateView update the main window depending the current state of the model.
     * @param m the model.
     */
    void updateView(Model * m);

  public slots:

    void displayCurrentPlayer();

  private slots:

    void exit();
    void help();
    void clearBoard();

  private:

    ControllerGui * _controller;
    BoardGui  * _boardGui;
    LeftWidget * _leftWidget;
    Rules * _rules;
    QLabel * _currentPlayer;

    /**
     * @brief setupWidgets set up the interface.
     *
     * Put the leftWidget on the left and the board on the right
     */
    void setupWidgets();

    /**
     * @brief setupMenus set up the menu bar where the player can
     * to click to exit or to get the rule of the game.
     */
    void setupMenus();

};

#endif // MAINWINDOW_H
