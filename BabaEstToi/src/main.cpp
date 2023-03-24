#include <iostream>
#include "model/baba.h"
#include "view/view.h"
using namespace std;

int main()
{
    model::Baba baba;
    view::ViewConsole v {&baba};
    baba.move(model::Direction::UP);
    return 0;
}

//faire un run terminal
