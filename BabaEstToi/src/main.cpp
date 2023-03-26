#include <iostream>
#include "model/baba.h"
#include "view/view.h"
using namespace std;

int main()
{
    model::Baba baba;
    view::ViewConsole v {&baba};
    string line;
    baba.move(model::Direction::UP);
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
        cin >> line;
    }
    return 0;
}
