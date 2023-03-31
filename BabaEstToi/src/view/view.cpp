#include "view.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <iomanip>

namespace view
{

ViewConsole::ViewConsole(model::Baba * baba) :
    baba_ {baba}
{
    baba_->registerObserver(this);
    ViewConsole::update(baba);
}

ViewConsole::~ViewConsole()
{
    baba_->unregisterObserver(this);
}

void typeToCout(std::string type){

    if (type == "WALL"){
        std::cout << std::setw(6) << "WALL";
    } else if (type == "ROCK"){
        std::cout << std::setw(6) << "ROCK";
    } else if (type == "FLAG"){
        std::cout << std::setw(6) << "FLAG";
    } else if (type == "METAL"){
        std::cout << std::setw(6) << "METAL";
    } else if (type == "GRASS"){
        std::cout << std::setw(6) << "GRASS";
    } else if (type == "WATER"){
        std::cout << std::setw(6) << "WATER";
    } else if (type == "BABA"){
        std::cout << std::setw(6) << "BABA";
    }  else if (type == "IS"){
        std::cout << std::setw(6) << "IS";
    }  else if (type == "TEXT_ROCK"){
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
    }  else if (type == "KILL"){
        std::cout << std::setw(6) << "KILL";
    }  else if (type == "PUSH"){
        std::cout << std::setw(6) << "PUSH";
    }  else if (type == "STOP"){
        std::cout << std::setw(6) << "STOP";
    }  else if (type == "WIN"){
        std::cout << std::setw(6) << "WIN";
    }  else if (type == "SINK"){
        std::cout << std::setw(6) << "SINK";
    }  else if (type == "YOU"){
        std::cout << std::setw(6) << "YOU";
    } else if (type == "LAVA"){
        std::cout << std::setw(6) << "LAVA";
    } else if (type == "TEXT_LAVA"){
        std::cout << std::setw(6) << "TLAVA";
    }

    //std::cout << std::setw(6) << type;
}

void ViewConsole::update(const Subject * subject)
{
    //std::cout<<baba_->getState()<<std::endl;
    std::string board = baba_->getState();
    model::Position dim {baba_->getDimensions()};
    int height {dim.x};
    int width {dim.y};
    std::istringstream stream(board);
    bool truc{true};
    std::string arr[width][height];
    int row = 0;
    int col = 0;
    std::map<model::Position,std::string> list;
    while(std::getline(stream, board))
    {
        if (truc)
        {
            truc = false;
        }
        else
        {

            //Cut "function"
            int x;
            int y;
            int step = 0;
            std::string gameObject;
            int end = board.find(' '); // stolen from the internet
                while (end != -1)
                { // Loop until no delimiter is left in the string.
                    if (step == 0)
                    {
                        gameObject = board.substr(0, end);
                        ++step;
                    }
                    else if (step == 1)
                    {
                        x = std::stoi(board.substr(0, end));
                        ++step;
                    }
                   board.erase(board.begin(), board.begin() + end + 1);
                   end = board.find(' ');
                }
            // This step is put there because in the while loop it does not do the last iteration
            y = std::stoi(board.substr(0, end));
            ++step;
            //end of the cut "function"

            //std::cout << gameObject << x << y <<std::endl;
            list.insert_or_assign(model::Position{x,y},gameObject);
            //std::cout<<board<<std::endl;
        }
    }
    auto it = list.begin();
    model::Position pos {0,0};
    model::Position ancienPos {pos};
    for (int i = 0; i<width;++i) {
        for (int j = 0; j<height;++j) {
            ancienPos = pos;
            pos = {j,i};
            if(pos.x == it->first.x && pos.y == it->first.y)
            {
                typeToCout(it->second);
                ++it;
            }
            else if (ancienPos.x == it->first.x && ancienPos.y == it->first.y)
            {
                typeToCout(it->second);
                ++it;
                j--;
            }
            else
            {
                pos = {j,i};
                std::cout << std::setw(6) << '.';
            }
        }
        std::cout << '\n';
    }
}
}
