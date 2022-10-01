#include "PlacementChoice.h"

PlacementChoice::PlacementChoice(QWidget * parent) : QWidget{parent}
{}

void PlacementChoice::setupUpPlacementChoice(QPushButton * manual, QPushButton * file)
{
    QLabel * question = new
    QLabel("Do you want to import a text file including your Board or manually place your pawns?");
    question->setAlignment(Qt::AlignHCenter);

    QVBoxLayout * centralLayout = new QVBoxLayout;
    QHBoxLayout * vboxLayout = new QHBoxLayout();

    vboxLayout->addWidget(file);
    vboxLayout->addWidget(manual);

    QGroupBox * horizontalGroupBox = new QGroupBox();
    horizontalGroupBox->setLayout(vboxLayout);

    centralLayout->addWidget(question);
    centralLayout->addWidget(horizontalGroupBox);

    centralLayout->setSpacing(20);
    centralLayout->setContentsMargins(10, 10, 10, 10);
    centralLayout->setAlignment(Qt::AlignCenter);
    setLayout(centralLayout);
}
