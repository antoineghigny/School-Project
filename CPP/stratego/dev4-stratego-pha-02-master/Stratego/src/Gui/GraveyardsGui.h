#ifndef GRAVEYARDSGUI_H
#define GRAVEYARDSGUI_H

#include <QListWidget>
#include "QLabel"
#include "QCheckBox"
#include "QPoint"

/**
 * @brief The GraveyardsGui class the graveyard of the player.
 */
class GraveyardsGui : public QListWidget
{
    Q_OBJECT

  public:

    explicit GraveyardsGui(const int pawnSize, QWidget * parent = nullptr);

    /**
     * @brief clear clear the graveyard.
     */
    void clear();

    /**
     * @brief addPawn add a new dead pawn in the graveyard.
     * @param pixmap the image of the pawn.
     */
    void addPawn(const QPixmap & pixmap);
};
#endif // GRAVEYARDSGUI_H
