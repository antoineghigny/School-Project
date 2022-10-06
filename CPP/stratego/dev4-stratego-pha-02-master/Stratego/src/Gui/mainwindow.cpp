#include "mainwindow.h"
#include "Model.h"

#include "BoardGui.h"
#include "leftWidget.h"

#include <QtWidgets>
#include <stdlib.h>

#include "QPushButton"

#include "QCheckBox"
#include "QVBoxLayout"
#include "QLabel"
#include "GraveyardsGui.h"
#include "DropFile.h"
#include "controllergui.h"

#include "Rules.h"
#include "thread"

MainWindow::MainWindow(QWidget * parent, ControllerGui * controller)
    : QMainWindow{parent}, _controller{controller}, _boardGui{new BoardGui{this, _controller}},
      _leftWidget{new LeftWidget{this, controller}}, _currentPlayer{new QLabel}
{
    controller->addObserver(_leftWidget);
    setupMenus();
    setupWidgets();
    QSizePolicy policy{QSizePolicy::Minimum, QSizePolicy::Minimum};
    _currentPlayer->setSizePolicy(policy);

    setWindowTitle(tr("Stratego"));
    QIcon icon = QIcon(":/images/logo.png");
    setWindowIcon(icon);
}

void MainWindow::updateView(Model * m)
{
    switch (m->getState())
    {
        case SET_UP: case PICK_PAWN:
            displayCurrentPlayer();
            break;
        case MOVE_PAWN:
            if (m->getDuelResult() != 2)
            {
                this->_leftWidget->fillGraveyard(m->getDuelResult(), _boardGui->width());
            }
            break;
        case END_TURN:
            if(m->getDuelResult() != -1)
            {
                displayCurrentPlayer();
            }
            break;
        default:
            break;
    }
}

void MainWindow::displayCurrentPlayer()
{
    int currentPlayer = _controller->getCurrentPlayer();
    QString player;
    if (currentPlayer == 0)
    {
        player = "BLUE";
        _currentPlayer->setStyleSheet("QLabel { color : #6666ff; }");
    }
    else
    {
        player = "RED";
        _currentPlayer->setStyleSheet("QLabel { color : #ff5050; }");

    }
    this->_currentPlayer->setText("Player : " + player + "");
}

void MainWindow::setupMenus()
{
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));

    QAction * exitAction = fileMenu->addAction(tr("E&xit"), qApp,
                           &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu * gameMenu = menuBar()->addMenu(tr("&Help"));

    gameMenu->addAction(tr("&Rules"), this,
                        &MainWindow::help);
}

void MainWindow::setupWidgets()
{
    QFrame * frame = new QFrame;
    QVBoxLayout * vboxLayout = new QVBoxLayout(frame);
    QHBoxLayout * frameLayout = new QHBoxLayout();
    _currentPlayer->setMaximumHeight(100);
    QGroupBox * horizontalGroupBox = new QGroupBox();

    this->_currentPlayer->setAlignment(Qt::AlignCenter);

    QFont f( "Arial", 16, QFont::Bold);
    _currentPlayer->setFont(f);
    _currentPlayer->setText("Welcome to Stratego");

    frameLayout->addWidget(_leftWidget);
    frameLayout->addWidget(_boardGui);

    vboxLayout->addWidget(_currentPlayer, Qt::AlignHCenter);
    horizontalGroupBox->setLayout(frameLayout);
    vboxLayout->addWidget(horizontalGroupBox);
    _controller->addObserver(_boardGui);

    setCentralWidget(frame);
}

void MainWindow::help()
{
    _rules = new Rules(this);
    _rules->show();
}

void MainWindow::exit()
{
    qApp->exit();
}

void MainWindow::clearBoard()
{
    _boardGui->clear();
}

