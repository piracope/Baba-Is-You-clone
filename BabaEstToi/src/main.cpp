#include <iostream>
#include "model/baba.h"
using namespace std;

int main()
{
    model::Baba baba;
    baba.move(model::Direction::UP);
    baba.move(model::Direction::UP);
    baba.move(model::Direction::RIGHT);
    baba.move(model::Direction::RIGHT);
    baba.move(model::Direction::RIGHT);
    std::cout << "=========================================\n" << baba.getState();
    baba.move(model::Direction::DOWN);
    std::cout << "=========================================\n" << baba.getState();

    baba.save();
    return 0;
}
