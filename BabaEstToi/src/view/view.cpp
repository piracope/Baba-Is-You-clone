#include "view.h"
#include <iostream>
#include <sstream>
namespace view
{

ViewConsole::ViewConsole(model::Baba * baba) :
    baba_ {baba}
{
    baba_->registerObserver(this);
}

ViewConsole::~ViewConsole()
{
    baba_->unregisterObserver(this);
}

void ViewConsole::update(const Subject * subject)
{
    //std::cout<<baba_->getState()<<std::endl;
    std::string board = baba_->getState();
    model::Position dim {baba_->getDimensions()};
    int height {dim.x};
    int width {dim.y};
    std::istringstream f(board);
    bool truc{true};
    std::string arr[width][height];
    while(std::getline(f, board))
    {
        if (truc){
            truc = false;
        } else {
            char *ptr;
            ptr = strtok(board," ");
            std::cout<<board<<std::endl;
        }
    }
}
}
