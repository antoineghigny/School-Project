#ifndef DROPFILE_H
#define DROPFILE_H

#include <QLabel>
#include "controllergui.h"


QT_BEGIN_NAMESPACE
class QMimeData;
QT_END_NAMESPACE

/**
 * @brief The DropFile class is a label where the player can drop a file that put automaticaly all pawn on the board.
 */
class DropFile : public QLabel
{
    Q_OBJECT

  public:

    explicit DropFile(QWidget * parent = nullptr, ControllerGui * controllerGui = nullptr);

  public slots:

    /**
     * @brief clear delete the contain of the label?
     */
    void clear();

  protected:
    /**
     * @brief dragEnterEvent If we enter with a file on the QLabel, the text changes to ask to put the board here.
     * @param event which is sent to a widget when a drag and drop action enters it
     */
    void dragEnterEvent(QDragEnterEvent * event) override;

    /**
     * @brief dragMoveEvent Propose to drop if we move a file on the QLabel.

     * @param event which is sent while a drag and drop action is in progress
     */
    void dragMoveEvent(QDragMoveEvent * event) override;

    /**
     * @brief dragLeaveEvent If we leave the zone, we clear the zone.

     * @param event that is sent to a widget when a drag and drop action leaves it
     */
    void dragLeaveEvent(QDragLeaveEvent * event) override;

    /**
     * @brief dropEvent
     * @param event
     */
    void dropEvent(QDropEvent * event) override;

  private:
    ControllerGui * _controller;
    QLabel * label;
};

#endif // DROPFILE_H
