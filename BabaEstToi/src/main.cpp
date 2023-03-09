#include <iostream>
#include "model/filemanager.h"
#include "model/level.h"
using namespace std;

int main()
{
    model::Level l {FileManager::getLevel(0)};
    std::cout << l.getState();
    return 0;
}
