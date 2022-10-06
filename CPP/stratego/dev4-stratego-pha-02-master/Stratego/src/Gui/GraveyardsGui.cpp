#include "GraveyardsGui.h"
#include "QEvent"

GraveyardsGui::GraveyardsGui(const int pawnSize, QWidget * parent) : QListWidget{parent}
{
    setDragEnabled(false);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(pawnSize, pawnSize));
    setSpacing(10);
    setAcceptDrops(false);
    setDropIndicatorShown(false);
}

void GraveyardsGui::addPawn(const QPixmap & pixmap)
{
    QListWidgetItem * pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));

    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                        Qt::ItemIsDragEnabled);
}

void GraveyardsGui::clear()
{
    while(this->count()>0)
    {
      this->takeItem(0);
    }
}
