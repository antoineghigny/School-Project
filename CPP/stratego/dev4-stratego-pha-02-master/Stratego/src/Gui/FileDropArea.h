#ifndef FILEDROPAREA_H
#define FILEDROPAREA_H

#include <QWidget>
#include <ControllerGui.h>
#include <QPushButton>
#include <QVBoxLayout>
#include "DropFile.h"

/**
 * @brief The FileDropArea class the area where the player can drop his file.
 */
class FileDropArea : public QWidget
{
    Q_OBJECT

   public:

    explicit FileDropArea(QWidget * parent, ControllerGui * ctrl);

   private:

    /**
     * @brief setDropFileLayout it simply set up the layout for the file if the player use one
     *
     * The controller is needed because this fucntion will create a DropFile object that need a controller.
     *
     * @param ctrl the controller.
     */
    void setDropFileLayout(ControllerGui * ctrl);
};

#endif // FILEDROPAREA_H
