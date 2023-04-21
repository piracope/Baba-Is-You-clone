#include "view.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <iomanip>

namespace view
{


ViewConsole::ViewConsole(model::Baba * baba) :
    baba_ {baba} //changer ça doit être le controller
{
    baba_->registerObserver(this);
    ViewConsole::update(baba);
}


ViewConsole::~ViewConsole()
{
    baba_->unregisterObserver(this);
}


std::string ViewConsole::askLine()
{
    std::string line;
    std::cin >> line;
    return line;
}


void ViewConsole::printError(const std::string& e)
{
    std::cerr << e << std::endl;
}

/**
 * @brief convert a type to the right string to display
 * @param type to convert
 */
void typeToCout(const std::string& type){
    if (type == "TEXT_ROCK"){
        std::cout << std::setw(6) << "TROCK";
    }  else if (type == "TEXT_WALL"){
        std::cout << std::setw(6) << "TWALL";
    }  else if (type == "TEXT_FLAG"){
        std::cout << std::setw(6) << "TFLAG";
    }  else if (type == "TEXT_METAL"){
        std::cout << std::setw(6) << "TMETAL";
    }  else if (type == "TEXT_GRASS"){
        std::cout << std::setw(6) << "TGRASS";
    }  else if (type == "TEXT_WATER"){
        std::cout << std::setw(6) << "TWATER";
    }  else if (type == "TEXT_BABA"){
        std::cout << std::setw(6) << "TBABA";
    }  else if (type == "TEXT_LAVA"){
        std::cout << std::setw(6) << "TLAVA";
    }  else
    {
        std::cout << std::setw(6) << type;
    }
}

void ViewConsole::update(const Subject * subject)
{
    model::Position dim {baba_->getDimensions()};
    const auto map {baba_->getState()};
    int height {dim.x};
    int width {dim.y};
    std::string arr[width][height];

    for(int y {0}; y < height; y++)
    {
        for (int x {0}; x < width; x++)
        {
            auto toShow {map.find({x, y})};
            if(toShow != map.end())
            {
                typeToCout(model::to_string(toShow->second.getType()));
            }
            else
            {
                std::cout << std::setw(6) << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
}
