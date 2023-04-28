#include "consolecontroller.h"

namespace controller
{
ConsoleController::ConsoleController():
    baba {model::Baba{}}, view {view::ViewConsole(&baba)}
{
}


void ConsoleController::play()
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
                view.printError("couldn't save");
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
                view.printError("couldn't find save");
            }
            catch (...)
            {
                view.printError("couldn't process save file");
            }
        }
        else if(line == "r")
        {
            this->baba.restart();
        }
        else if(line == "help")
        {
            view.printHelp();
        }
        line = view.askLine();
    }
}
}
