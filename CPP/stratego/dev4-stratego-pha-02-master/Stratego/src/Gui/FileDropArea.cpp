#include "FileDropArea.h"

FileDropArea::FileDropArea(QWidget * parent, ControllerGui * ctrl) : QWidget{parent}
{
    setDropFileLayout(ctrl);
}

void FileDropArea::setDropFileLayout(ControllerGui * ctrl)
{
    QLabel * title = new
    QLabel{"Please Drag & Drop your file containing the board just bellow"};
    DropFile * dropFile = new DropFile{this, ctrl};
    QVBoxLayout * centralLayout = new QVBoxLayout;
    title->setMaximumHeight(60);
    title->setAlignment(Qt::AlignCenter);
    dropFile->setAlignment(Qt::AlignCenter);

    centralLayout->addWidget(title);
    centralLayout->addWidget(dropFile);

    setLayout(centralLayout);
}
