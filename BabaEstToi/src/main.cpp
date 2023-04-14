#include <iostream>
#include "model/baba.h"
#include "view/view.h"
using namespace std;

int main()
{
    model::Baba baba;
    view::ViewConsole v {&baba};
    string line;
    cin >> line;
    while (line != "exit")
    {
        if(line == "z")
        {
            baba.move(model::Direction::UP);
        }
        else if (line == "s")
        {
            baba.move(model::Direction::DOWN);
        }
        else if(line == "q")
        {
            baba.move(model::Direction::LEFT);
        }
        else if(line == "d")
        {
            baba.move(model::Direction::RIGHT);
        }
        else if(line == "restart")
        {
            baba.restart();
        }
        else if(line == "save")
        {
            try {
                baba.save();
                std::cout << "Saved!" << std::endl;
            } catch (...) {
                std::cerr << "Couldn't save." << std::endl;
            }

        }
        cin >> line;
    }
    return 0;
}
