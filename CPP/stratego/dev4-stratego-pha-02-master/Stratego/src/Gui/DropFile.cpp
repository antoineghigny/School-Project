#include "DropFile.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include "iostream"
#include "controllergui.h"

//#include <filesystem> // C++17
//namespace fs = std::filesystem;

DropFile::DropFile(QWidget * parent, ControllerGui * controllerGui)
    : QLabel{parent}, _controller{controllerGui}
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    clear();
}


void DropFile::dragEnterEvent(QDragEnterEvent * event)
{
    setText(tr("Drop your board"));
    setBackgroundRole(QPalette::Highlight);

    event->acceptProposedAction();
}

void DropFile::dragMoveEvent(QDragMoveEvent * event)
{
    event->acceptProposedAction();
}

void DropFile::dropEvent(QDropEvent * event)
{
    const QMimeData * mimeData = event->mimeData();

    if (mimeData->hasText())
    {
        std::string text = mimeData->text().toStdString();
        text = text.substr(text.find("file:///") + 8);

        _controller->loadFile(text);
    }else{
        setText(tr("You must made a mistake, please retry"));
    }
    setBackgroundRole(QPalette::Dark);
    event->acceptProposedAction();
}

void DropFile::dragLeaveEvent(QDragLeaveEvent * event)
{
    setText(tr("Drag your board here"));
    clear();
    event->accept();
}

void DropFile::clear()
{
    setText(tr("Drag your board here"));
    setBackgroundRole(QPalette::Dark);
}
