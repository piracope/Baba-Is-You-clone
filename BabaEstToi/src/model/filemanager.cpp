#include <algorithm>
#include <fstream>
#include <sstream>

#include "filemanager.h"

std::string FileManager::getFile(std::string path)
{
    // TODO : use resource from qrc instead

    std::ifstream lvl {path};
    lvl.exceptions(std::ios::failbit); // throws if bad file

    std::stringstream ret;
    std::transform(std::istreambuf_iterator<char>(lvl), // stolen from stackoverflow
                   std::istreambuf_iterator<char>(),
                   std::ostreambuf_iterator<char>(ret),
                   [](int ch) { return toupper(ch);});

    lvl.close();
    return ret.str();
}

void FileManager::writeFile(std::string path, std::string lvl)
{
    std::ofstream save {path};
    save.exceptions(std::ios::failbit);

    save << lvl;
    save.close();
}
