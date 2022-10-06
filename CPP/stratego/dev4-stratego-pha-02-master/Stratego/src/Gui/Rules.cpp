#include <QApplication>
#include <QWidget>
#include <iostream>

#include "Rules.h"
#include "QLabel"
#include "QScrollArea"

Rules::Rules(QWidget *parent)
    : QMainWindow(parent){
    this->setWindowTitle("Stratego's rules");
    setMinimumSize(830, 1200);
    setMaximumSize(2000, 2000);

    QLabel * imageLabel = new QLabel;
        imageLabel->setBackgroundRole(QPalette::Base);
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imageLabel->setScaledContents(true);
        imageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


        QPixmap _img;
        _img.load(":/images/help.png");

        /*!
           Source : \l https://www.ultraboardgames.com/stratego/game-rules.php
        */

        imageLabel->setPixmap(_img);
        QScrollArea * scrollArea = new QScrollArea;
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imageLabel);
        setCentralWidget(scrollArea);
}
