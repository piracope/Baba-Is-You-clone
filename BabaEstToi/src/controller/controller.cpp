#include "controller.h"

namespace controller
{
Controller::Controller():
    baba {model::Baba{}}, view {view::ViewConsole(&baba)}
{
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
            try
            {
                this->baba.save();
            }
            catch(const std::ios_base::failure&)
            {
                // TODO : print error --> coulnd't write
            }

        }
        else if(line == "load")
        {
            try
            {
                this->baba.load();
            }
            catch(const std::ios_base::failure&)
            {
                // TODO : print error --> couldn't find save
            }
            catch (...)
            {
                // TODO: print error --> couldn't process save file
            }
        }
        else if(line == "r")
        {
            this->baba.restart();
        }
        line = view.askLine();
    }
}
}
