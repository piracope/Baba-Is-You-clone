#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/baba.h"
#include "../view/view.h"
// TODO : document controller
namespace controller
{
class Controller
{
    model::Baba baba;
    view::ViewConsole view;

public:
    Controller();
    void play();
};

}
#endif // CONTROLLER_H
