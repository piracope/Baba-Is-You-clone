#include <iostream>
#include "model/baba.h"
using namespace std;

int main()
{
    model::Baba baba;
    std::cout << baba.getState();

    baba.save();
    return 0;
}
