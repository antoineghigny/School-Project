#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo> // pour bad_cast

#include "Model.h"
#include "Game.h"
#include "Controller.h"
#include "ViewConsole.h"


using namespace std;

int main()
{
    Controller ctrl;
    ctrl.play();
    return 0;
}
