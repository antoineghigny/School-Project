#include "deckgui.h"
#include "BoardGui.h"
#include "iostream"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include "Pawn.h"
#include "QPoint"
#include "Position.h"
#include "QListWidgetItem"
#include "QTimer"

BoardGui::BoardGui(MainWindow * parent,
                   ControllerGui * controller)
    : QWidget{parent}, _controller{controller}, _timer{new QTimer}
{
    QSizePolicy policy{QSizePolicy::Maximum, QSizePolicy::Maximum};
    setSizePolicy(policy);

    setMinimumHeight(500);
    setMinimumWidth(500);

    setAcceptDrops(true);
    _hideRed.load(":/images/allPawns/red/12.png");
    _hideBlue.load(":/images/allPawns/blue/12.png");
    connect(_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(_timer, SIGNAL(timeout()), parent, SLOT(displayCurrentPlayer()));
}

void BoardGui::mousePressEvent(QMouseEvent * event)
{
    int start = (event->position().y() / getPawnSize()) + 1;
    int dest = (event->position().x() / getPawnSize()) + 1;
    if (_controller->getState() == PICK_PAWN && !_timer->isActive() && _controller->canBeMoved(start, dest))
    {
        _firstPos = new Position(start, dest);

        QRect square = targetPawn(event->position().toPoint());
        const int found = findPawn(square);

        if (found == -1)
            return;

        PawnGui piece = pawns.takeAt(found);

        update(square);

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << piece.pixmap  << piece.id <<
                   piece.inDeck << piece.team;

        QMimeData * mimeData = new QMimeData;
        mimeData->setData(DeckGui::pawnMimeType(), itemData);

        QDrag * drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setHotSpot(event->position().toPoint() - square.topLeft());
        drag->setPixmap(piece.pixmap);

        if (drag->exec(Qt::MoveAction) != Qt::MoveAction)
        {
            pawns.insert(found, piece);
            update(targetPawn(event->position().toPoint()));
        }
    }
    else
    {
        event->ignore();
    }

}

void BoardGui::dragEnterEvent(QDragEnterEvent * event)
{
    if (_controller->getState() == PICK_PAWN)
    {
        _controller->canBeMoved(_firstPos->getX(), _firstPos->getY());
    }

    if (event->mimeData()->hasFormat(DeckGui::pawnMimeType()))
    {
        event->accept();
    }
    else
        event->ignore();
}

void BoardGui::dragLeaveEvent(QDragLeaveEvent * event)
{
    QRect updateRect = _highlightedRect;
    _highlightedRect = QRect();
    update(updateRect);

    if (_controller->getState() == MOVE_PAWN)
    {
        _controller->isSamePosition(Position(_firstPos->getX(),
                                             _firstPos->getY()));
    }
}

void BoardGui::dragMoveEvent(QDragMoveEvent * event)
{
    QRect updateRect = _highlightedRect.united(targetPawn(
                           event->position().toPoint()));
    PawnGui piece;
    piece.rect = targetPawn(event->position().toPoint());

    auto loc = piece.rect.topLeft() / getPawnSize();

    if (_controller->getState() == SET_UP)
    {
        QByteArray pieceData = event->mimeData()->data(
                                   DeckGui::pawnMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        dataStream >> piece.pixmap  >> piece.id >>
                   piece.inDeck >> piece.team;
    }

    if (_controller->getState() == SET_UP &&
            _controller->canBePut(_controller->getPawnInDeckAt(
                                      piece.id), loc.y() + 1,
                                  loc.x() + 1))
    {
        _highlightedRect = targetPawn(event->position().toPoint());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else if (_controller->getState() == MOVE_PAWN &&
             _controller->isCorrectMove(Position(loc.y() + 1, loc.x() + 1)))
    {
        _highlightedRect = targetPawn(event->position().toPoint());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
    update(updateRect);
}

void BoardGui::dropEvent(QDropEvent * event)
{
    QByteArray pieceData = event->mimeData()->data(
                               DeckGui::pawnMimeType());

    QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

    PawnGui piece;
    piece.rect = targetPawn(event->position().toPoint());

    dataStream >> piece.pixmap  >> piece.id >>
               piece.inDeck >> piece.team;
    pawns.append(piece);

    _highlightedRect = QRect();
    update(piece.rect);

    auto loc = piece.rect.topLeft() / getPawnSize();

    if (_controller->getState() == SET_UP)
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
        _controller->putPawnAt(loc.y() + 1, loc.x() + 1, piece.id);
    }
    else if (_controller->getState() == MOVE_PAWN &&
             _controller->isCorrectMove(Position(loc.y() + 1, loc.x() + 1)))
    {
        _controller->movePawnGui(Position(loc.y() + 1, loc.x() + 1));
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void BoardGui::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPixmap map;

    map.load(":/images/lignes.png");
    painter.fillRect(event->rect(), map.scaled(width(), height()));

    if (_highlightedRect.isValid())
    {
        QColor color = QColor("#ffcccc");
        color.setAlphaF(0.5);
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(_highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (const PawnGui & pawn : pawns)
    {
        auto loc = pawn.rect.topLeft() / getPawnSize();
        painter.drawPixmap(pawn.rect,
                           findPixmap(_controller->getCurrentPlayer(),  Position(loc.y() + 1,
                                      loc.x() + 1), pawn));
    }
}


void BoardGui::updateDuel(const Position pos, const int duelResult)
{
    int x = pos.getY() - 1;
    int y = pos.getX() - 1;

    QPoint destPos(x * getPawnSize(), y * getPawnSize());
    PawnGui pawnGui;

    if (duelResult != 2)
    {
        int found = 0;
        if (duelResult == -1)
        {
            pawnGui = deletePawnGui(pos);
            deletePawnGui(pos);
            pawns.insert(found, pawnGui);
            _timer->start(2000);
        }
        else if (duelResult == 1)
        {
            deletePawnGui(pos);
        }
        else
        {
            deletePawnGui(pos);
            deletePawnGui(pos);
            repaint();
        }
    }else {
        repaint();
    }
}

BoardGui::PawnGui BoardGui::deletePawnGui(const Position & dest)
{
    int x = dest.getY() - 1;
    int y = dest.getX() - 1;
    PawnGui pawn;
    QPoint destPos(x * getPawnSize(), y * getPawnSize());

    QRect square = targetPawn(destPos);
    int found = findPawn(square);
    if (!(found == -1))
    {
        pawn =  pawns.takeAt(found); // DELETE
    }
    return pawn;
}

void BoardGui::updateView(Model * m)
{
    if(!_timer->isActive())
    {
        switch (m->getState())
        {
        case SET_UP: case PICK_PAWN:
            repaint();
            break;
        case END_FILE_SET_UP:
            setupBoardForFile();
            repaint();
            break;
        case END_SET_UP:
            repaint();
            break;
        case MOVE_PAWN:
            updateDuel(m->getDestinationPosition(), m->getDuelResult());
            break;
        case END_TURN:
            repaint();
            break;
        }
    }
}

QPixmap BoardGui::findPixmap(const Team currentPlayer, const Position pos,
                             const PawnGui pawn) const
{
    if (!_controller->getPawnAtPos(pos).isVisible() &&
            currentPlayer != pawn.team)
    {
        if (currentPlayer == 1)
        {
            return _hideBlue;
        }
        else if (currentPlayer == 0)
        {
            return _hideRed;
        }
    }
    return pawn.pixmap;
}

void BoardGui::placePawnFile(int x, int y, QPixmap pixmap, int team)
{
    QPoint pos(x * getPawnSize(), y * getPawnSize());

    PawnGui piece;

    piece.rect = targetPawn(pos);
    piece.pixmap = pixmap;
    piece.team = team;

    pawns.append(piece);
}

const QRect BoardGui::targetPawn(const QPoint & position) const
{
    QPoint topLeft = QPoint(position.x() / getPawnSize(),
                            position.y() / getPawnSize()) * getPawnSize();

    return QRect(topLeft, QSize(getPawnSize(), getPawnSize()));
}

int BoardGui::findPawn(const QRect & pieceRect) const
{
    for (int i = 0, size = pawns.size(); i < size; ++i)
    {
        if (pawns.at(i).rect == pieceRect)
            return i;
    }
    return -1;
}

void BoardGui::refresh()
{
    _timer->stop();
    repaint();
}

void BoardGui::clear()
{
    pawns.clear();
    repaint();
}

int BoardGui::getPawnSize() const
{
    return width() / 10;
}

void BoardGui::setupBoardForFile()
{
    int currentPlayer = _controller->getCurrentPlayer();
    QPixmap pixMap;
    int begin {};

    (_controller->getCurrentPlayer() == 0) ? begin = 6 : begin = 0;

    for (int x = begin; x <= (begin+3); ++x)
    {
        for (int y = 0; y < _controller->getBoardSize(); ++y)
        {
            pixMap.load(imagePixmap(_controller->getPawnAtPos(Position(x+1, y+1)).getRole(),_controller->getPawnAtPos(Position(x+1, y+1)).getTeam()));


            pixMap = pixMap.copy((pixMap.width()),(pixMap.height()), pixMap.width(),pixMap.height()).scaled(this->width() / _controller->getBoardSize(),
                                                       this->height() / _controller->getBoardSize(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);

            placePawnFile(y, x, pixMap, currentPlayer);
        }
    }
}

QString BoardGui::imagePixmap(const Role role, const Team team)
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
        default:
            s+= "/blue/";
            break;
    }
    QString roleString = QString::number(role);
    s += roleString;
    s += ".png";
    return s;
}




