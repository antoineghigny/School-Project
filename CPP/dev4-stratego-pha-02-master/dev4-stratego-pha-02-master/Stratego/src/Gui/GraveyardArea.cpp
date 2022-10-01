#include "GraveyardArea.h"

GraveyardArea::GraveyardArea(QWidget * parent, ControllerGui * ctrl) : QWidget{parent}, _ctrl{ctrl},
    _blueGraveyards{new GraveyardsGui{500 / 10, this}}, _redGraveyards{new GraveyardsGui{500 / 10, this}}
{
    setUpGraveyardArea();
}

void GraveyardArea::setUpGraveyardArea()
{
    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(_blueGraveyards);
    centralLayout->addWidget(_redGraveyards);
    setLayout(centralLayout);
}

void GraveyardArea::clear()
{
    _blueGraveyards->clear();
    _redGraveyards->clear();
}

void GraveyardArea::fillGraveyards(int duelResult, int boardSize)
{
    std::vector<std::pair<Role, Team>> listDeadPawns = {};
    QPixmap pixMap;

    if(duelResult == -1){
         listDeadPawns.push_back(_ctrl->getLastDeadPawn(
                            _ctrl->getCurrentPlayer()));
    }else if(duelResult == 1){

        listDeadPawns.push_back(_ctrl->getLastDeadPawn(
                            (_ctrl->getCurrentPlayer()+1) % 2));
    }else{
        listDeadPawns.push_back(_ctrl->getLastDeadPawn(
                                    _ctrl->getCurrentPlayer())); // 1 et // 0
        listDeadPawns.push_back(_ctrl->getLastDeadPawn( // 0 et //1
                            (_ctrl->getCurrentPlayer()+1) % 2));
    }
    for(auto deadPawn : listDeadPawns){
        pixMap.load(imagePixmap(deadPawn.first, deadPawn.second));
        pixMap = pixMap.copy((pixMap.width()),(pixMap.height()), pixMap.width(),pixMap.height()).scaled(boardSize / _ctrl->getBoardSize(),
                                                       boardSize / _ctrl->getBoardSize(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
        if (deadPawn.second == 0)
        {
            _blueGraveyards->addPawn(pixMap);
        }
        else
        {
            _redGraveyards->addPawn(pixMap);
        }
    }
}

QString GraveyardArea::imagePixmap(const Role role, const Team team)
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
