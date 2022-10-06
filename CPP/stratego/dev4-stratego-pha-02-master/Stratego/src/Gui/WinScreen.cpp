#include "WinScreen.h"

WinScreen::WinScreen(QWidget * parent, ControllerGui * ctrl) : _ctrl{ctrl}, _winner{new QLabel}
{}

void WinScreen::setUpLayout(QPushButton * replay, QPushButton * exit)
{
    QLabel * question = new QLabel("Do you want to play another game ?");

    QVBoxLayout * centralLayout = new QVBoxLayout;
    QHBoxLayout * vboxLayout = new QHBoxLayout();

    vboxLayout->addWidget(replay);
    vboxLayout->addWidget(exit);

    QGroupBox * horizontalGroupBox = new QGroupBox();
    horizontalGroupBox->setLayout(vboxLayout);

    centralLayout->addWidget(_winner);
    centralLayout->addWidget(question);
    centralLayout->addWidget(horizontalGroupBox);

    centralLayout->setSpacing(20);
    centralLayout->setContentsMargins(10, 10, 10, 10);
    centralLayout->setAlignment(Qt::AlignCenter);
    setLayout(centralLayout);
}

void WinScreen::displayWinner() const
{
    QFont f( "Arial", 16, QFont::Bold);
    if(_ctrl->getGameResult() != GameResult::EGALITY)
    {
        Team winner = _ctrl->getWinner();
        QString player;
        if (winner == 0)
        {
            player = "BLUE";
            _winner->setStyleSheet("QLabel { color : #6666ff; }");
        }
        else
        {
            player = "RED";
            _winner->setStyleSheet("QLabel { color : #ff5050; }");
        }
        this->_winner->setText("GREAT ! Player : " + player + "  you win !");
        _winner->setFont(f);
    }else
    {
        this->_winner->setText("EQUALITY ! No winner for this game.");
        _winner->setFont(f);
    }
}
