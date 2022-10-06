#include "deckgui.h"
#include "iostream"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include "QPoint"

DeckGui::DeckGui(const int pawnSize, ControllerGui * ctrl, QWidget * parent)
    : QListWidget{parent}, _pawnSize{pawnSize}, _ctrl{ctrl}
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(pawnSize, pawnSize));
    setSpacing(10);
    setAcceptDrops(false);
    setDropIndicatorShown(true);
}

void DeckGui::dragEnterEvent(QDragEnterEvent * event)
{

    if (event->mimeData()->hasFormat(DeckGui::pawnMimeType()))
        event->accept();
    else
        event->ignore();
}

void DeckGui::dragMoveEvent(QDragMoveEvent * event)
{
    if (event->mimeData()->hasFormat(DeckGui::pawnMimeType()))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void DeckGui::displayPawn()
{
    QPixmap pixMap;
    _ctrl->generateDeck();
    int currentPlayer {_ctrl->getCurrentPlayer()};

    for (int index = 0; index < _ctrl->getDeckSize(); ++index)
    {
        pixMap.load(imagePixmap(_ctrl->getPawnInDeckAt(
                                         index).getRole(), _ctrl->getPawnInDeckAt(index).getTeam()));

        pixMap = pixMap.copy((pixMap.width()),(pixMap.height()), pixMap.width(),pixMap.height()).scaled(500 / _ctrl->getBoardSize(),
                                                       500 / _ctrl->getBoardSize(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);


        addPawn(pixMap, currentPlayer);
    }
}

QString DeckGui::imagePixmap(Role role, Team team)
{
    QString s;
    s += ":/images/allPawns";
    switch (team)
    {
        case 0:
            s += "/blue/";
            break;
        case 1:
            s += "/red/";
            break;
    }
    QString roleString = QString::number(role);
    s += roleString;
    s += ".png";
    return s;
}

void DeckGui::addPawn(const QPixmap & pixmap, const int currentPlayer)
{
    QListWidgetItem * pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole + 1, currentPlayer);

    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                        Qt::ItemIsDragEnabled);
}

void DeckGui::startDrag(Qt::DropActions event)
{
    QListWidgetItem * item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));

    int id = row(item);
    bool inDeck = true;
    int team = qvariant_cast<int>(item->data(Qt::UserRole + 1));

    dataStream << pixmap << id << inDeck << team;

    QMimeData * mimeData = new QMimeData;
    mimeData->setData(DeckGui::pawnMimeType(), itemData);

    QDrag * drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
}
