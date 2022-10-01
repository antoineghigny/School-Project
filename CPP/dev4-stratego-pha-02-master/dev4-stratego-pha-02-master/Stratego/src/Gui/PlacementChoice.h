#ifndef PLACEMENTCHOICE_H
#define PLACEMENTCHOICE_H

#include <QWidget>
#include "QLabel"
#include "QPushButton"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGroupBox"

/**
 * @brief The PlacementChoice class interface where the application ask the type of placement.
 */
class PlacementChoice : public QWidget
{
    Q_OBJECT

   public:

    explicit PlacementChoice(QWidget * parent);

    /**
     * @brief setupUpPlacementChoice set up the interface where it will ask how the player want to put his pawns.
     *
     * @param manual the button where the player will put his pawn one by one.
     * @param file the button where the player will put his pawn with a file.
     */
    void setupUpPlacementChoice(QPushButton * manual, QPushButton * file);
};

#endif // PLACEMENTCHOICE_H
