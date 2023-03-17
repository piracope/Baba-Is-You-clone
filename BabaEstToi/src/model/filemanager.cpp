#include <algorithm>
#include <fstream>
#include <sstream>

#include "filemanager.h"

std::string FileManager::getLevel(unsigned nb)
{
    std::stringstream path;
    path << START_OF_PATH << nb << ".txt";

    std::ifstream lvl {path.str()};
    lvl.exceptions(std::ios::failbit); // throws if bad file

    std::stringstream ret;
    std::transform(std::istreambuf_iterator<char>(lvl), // stolen from stackoverflow
                   std::istreambuf_iterator<char>(),
                   std::ostreambuf_iterator<char>(ret),
                   [](int ch) { return toupper(ch);});

    lvl.close();
    return ret.str();
}

void FileManager::writeSave(std::string lvl)
{
    std::stringstream path;
    path << START_OF_PATH << "S.txt"; // FIXME : se mettre d'accord là-dessus

    std::ofstream save {path.str()};
    save.exceptions(std::ios::failbit);

    save << lvl;
    save.close();
}
