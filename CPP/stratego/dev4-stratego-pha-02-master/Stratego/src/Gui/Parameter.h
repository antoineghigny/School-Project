#ifndef PARAMETER_H
#define PARAMETER_H

#include <QWidget>
#include <ControllerGui.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

/**
 * @brief The Parameter class interface where the application ask the game mode.
 */
class Parameter : public QWidget
{
    Q_OBJECT

  public:

    explicit Parameter(QWidget * parent, ControllerGui * ctrl);

  private slots:

    /**
     * @brief startNormalGame slot used to launch a game in normal mode.
     */
    void startNormalGame();

    /**
     * @brief startEasyGame slot used to launch the game in easy mode.
     */
    void startEasyGame();

  private:

    ControllerGui * _ctrl;

    /**
     * @brief setUpLayout set up the interface that will ask the game mode of the game.
     */
    void setUpLayout();
};

#endif // PARAMETER_H
