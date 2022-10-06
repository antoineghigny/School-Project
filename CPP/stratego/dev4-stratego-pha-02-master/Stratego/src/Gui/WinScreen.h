#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QWidget>
#include <ControllerGui.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

/**
 * @brief The WinScreen class interface that will display the winner and ask if the players want to restart.
 */
class WinScreen : public QWidget
{
    Q_OBJECT

   public:

    explicit WinScreen(QWidget * parent, ControllerGui * ctrl);

    /**
     * @brief displayWinner get the current winner and display it.
     */
    void displayWinner() const;

    /**
     * @brief setUpLayout set up the win screen.
     * @param replay the button to launch a new game.
     * @param exit the button to exit the game.
     */
    void setUpLayout(QPushButton * replay, QPushButton * exit);

   private:

    ControllerGui * _ctrl;
    QLabel * _winner;

};

#endif // WINSCREEN_H
