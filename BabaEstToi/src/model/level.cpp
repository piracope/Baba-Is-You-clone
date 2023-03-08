#include <string>
#include <sstream>

#include "level.h"

Level::Level(std::string lvl)
{
    std::istringstream str {lvl};

    /* getting the dimensions */
    std::string tmp;
    std::getline(str, tmp);

    size_t pos = 0;
    width = std::stoi(tmp, &pos);
    height = std::stoi(tmp, &pos + 1);

    while(std::getline(str, tmp))
    {
        std::istringstream line {tmp};
        std::string tmp2;
        std::getline(line, tmp2, ' ');
        // TODO : tile = first, etc.
    }
    // TODO : strtok pour scanner les differents mots
}
