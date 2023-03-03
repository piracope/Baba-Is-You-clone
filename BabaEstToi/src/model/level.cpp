#include <string>
#include <sstream>

#include "level.h"

Level::Level(std::string lvl)
{

    std::stringstream str {lvl};

    std::string tmp;
    std::getline(str, tmp);

    width = std::stoi(tmp);
    // TODO : strtok pour scanner les differents mots
}
