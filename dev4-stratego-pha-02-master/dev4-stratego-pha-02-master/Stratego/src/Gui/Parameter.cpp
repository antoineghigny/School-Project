#include <Parameter.h>

Parameter::Parameter(QWidget * parent, ControllerGui * ctrl) : QWidget{parent}, _ctrl{ctrl}
{
    setUpLayout();
}

void Parameter::setUpLayout()
{
    QLabel * question = new QLabel("Do you want to play the game in easy mode ?");
    QPushButton * easyMode = new QPushButton("Easy Mode");
    QPushButton * normalMode = new QPushButton("Normal Mode");

    //Connect the button start to the slots startGame that launch the game
    connect(easyMode, SIGNAL(clicked()), this, SLOT(startEasyGame()));
    connect(normalMode, SIGNAL(clicked()), this, SLOT(startNormalGame()));

    //Create the layout for the button, checkBox and title
    QVBoxLayout * centralLayout = new QVBoxLayout;
    QHBoxLayout * vboxLayout = new QHBoxLayout();
    vboxLayout->addWidget(normalMode);
    vboxLayout->addWidget(easyMode);

    QGroupBox * horizontalGroupBox = new QGroupBox();
    horizontalGroupBox->setLayout(vboxLayout);

    // Set the central layout
    centralLayout->addWidget(question);
    centralLayout->addWidget(horizontalGroupBox);

    centralLayout->setSpacing(20);
    centralLayout->setContentsMargins(10, 10, 10, 10);
    centralLayout->setAlignment(Qt::AlignCenter);
    setLayout(centralLayout);
}

void Parameter::startNormalGame()
{
    _ctrl->startGame(false);
}

void Parameter::startEasyGame()
{
    _ctrl->startGame(true);
}
