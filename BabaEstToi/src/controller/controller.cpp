#include "controller.h"

namespace controller
{
Controller::Controller():
    baba {model::Baba{}}, view {view::ViewConsole(&baba)}
{
    view.update(&baba);
}


void Controller::play()
{
    std::string line = view.askLine();
    while (line != "exit")
    {
        if(line == "z")
        {
            this->baba.move(model::Direction::UP);
        }
        else if (line == "s")
        {
            this->baba.move(model::Direction::DOWN);
        }
        else if(line == "q")
        {
            this->baba.move(model::Direction::LEFT);
        }
        else if(line == "d")
        {
            this->baba.move(model::Direction::RIGHT);
        }
        else if(line == "save")
        {
            this->baba.save();
        }
        else if(line == "load")
        {
            this->baba.load();
        }
        else if(line == "r")
        {
            this->baba.restart();
        }
        line = view.askLine();
    }
}
}
