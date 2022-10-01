#include <QWidget>
#include <ControllerGui.h>
#include <QPushButton>
#include <QVBoxLayout>
#include "GraveyardsGui.h"

/**
 * @brief The GraveyardArea class the interface where the graveyard of both players are shown.
 */
class GraveyardArea : public QWidget
{
    Q_OBJECT

   public:

    explicit GraveyardArea(QWidget * parent, ControllerGui * ctrl);

    /**
     * @brief clear delete all the pawn that are in the graveyard (interface)
     *
     * When a game start, clear both graveyard from the previous game if there was one.
     */
    void clear();

    /**
     * @brief fillGraveyards When there is a dead pawn add the pawn on the interface in the correct graveyard.
     * @param duelResult the result of the duel. The result indicate which pawn is dead.
     * @param boardSize the size of the board for the correct size of the image.
     */
    void fillGraveyards(int duelResult, int boardSize);

   private:
    ControllerGui * _ctrl;
    GraveyardsGui * _blueGraveyards;
    GraveyardsGui * _redGraveyards;

    /**
     * @brief setUpGraveyardArea set up the graveyard when the game start.
     *
     * This widget will be used to display all the pawn that are dead.
     */
    void setUpGraveyardArea();

    /**
     * @brief imagePixmap find the path to image of the pawn.
     *
     * @param role the role of the pawn.
     * @param team the team of the pawn.
     * @return the path to get the image correcponding the pawn.
     */
    QString imagePixmap(const Role role, const Team team);

};
