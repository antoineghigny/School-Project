#include "leftWidget.h"
#include "ControllerGui.h"
#include "qwidget.h"
#include "QGridLayout"
#include "QListWidget"
#include "QVBoxLayout"
#include "QPushButton"
#include "QLabel"
#include "QGroupBox"

LeftWidget::LeftWidget(MainWindow * parent,
                       ControllerGui * controller): QWidget(parent), _controller{controller}, _stack{new QStackedLayout}
{
    setMinimumSize(500, 500);
    Parameter * param = new Parameter{this, controller}; //0
    _stack->addWidget(param);
    setUpPlacementWidget(); //1
    DeckGui * deck = new DeckGui{500, controller, this}; //2
    _stack->addWidget(deck);
    FileDropArea * fileDropArea = new FileDropArea{this, _controller}; //3
    _stack->addWidget(fileDropArea);
    GraveyardArea * graveyardArea = new GraveyardArea{this, controller}; //4
    _stack->addWidget(graveyardArea);
    setUpWinScreenWidget(parent, controller); //5
    setLayout(_stack);
}

void LeftWidget::setUpPlacementWidget()
{
    PlacementChoice * placement = new PlacementChoice{this}; //1
    QPushButton * importFile = new QPushButton("Import a file");
    QPushButton * manualPlacement = new QPushButton("Manual placement");
    connect(manualPlacement, SIGNAL(clicked()), this, SLOT(setDeck()));
    connect(importFile, SIGNAL(clicked()), this, SLOT(setDropFile()));
    placement->setupUpPlacementChoice(manualPlacement, importFile);
    _stack->addWidget(placement);
}

void LeftWidget::setUpWinScreenWidget(MainWindow * mw, ControllerGui * ctrl)
{
    WinScreen * winScreen = new WinScreen{this, ctrl}; //5
    QPushButton * replay = new QPushButton("YES");
    QPushButton * exit = new QPushButton("NO");
    connect(replay, SIGNAL(clicked()), this, SLOT(setParameter()));
    connect(replay, SIGNAL(clicked()), mw, SLOT(clearBoard()));
    connect(exit, SIGNAL(clicked()), mw, SLOT(exit()));
    winScreen->setUpLayout(replay, exit);
    _stack->addWidget(winScreen);
}

void LeftWidget::setParameter()
{
    _stack->setCurrentIndex(0);
}

void LeftWidget::setDeck()
{
    _controller->generateDeck();
    _stack->setCurrentIndex(2);
    DeckGui * deck = dynamic_cast<DeckGui*>(_stack->currentWidget());
    deck->displayPawn();
}

void LeftWidget::setDropFile()
{
    _stack->setCurrentIndex(3);
}

void LeftWidget::setPlacementChoice()
{
    _stack->setCurrentIndex(1);
}

void LeftWidget::setGraveyardArea()
{
    _stack->setCurrentIndex(4);
    GraveyardArea * graveyardArea = dynamic_cast<GraveyardArea*>(_stack->currentWidget());
    graveyardArea->clear();
}

void LeftWidget::setWinScreen()
{
    _stack->setCurrentIndex(5);
    WinScreen * winScreen = dynamic_cast<WinScreen*>(_stack->currentWidget());
    winScreen->displayWinner();
}


QString LeftWidget::imagePixmap(const Role role, const Team team)
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

void LeftWidget::fillGraveyard(const int duelResult, const int boardSize)
{
    GraveyardArea * g = dynamic_cast<GraveyardArea*>(_stack->currentWidget());
    g->fillGraveyards(duelResult, boardSize);
}

void LeftWidget::updateView(Model * m)
{
    switch (m->getState())
    {
        case SET_UP:
            setPlacementChoice();
            break;
        case END_SET_UP:
            setGraveyardArea();
            break;
        case GAME_OVER:
            setWinScreen();
            break;
    }
}

