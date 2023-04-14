#include <algorithm>
#include <fstream>
#include <sstream>

#include "filemanager.h"

std::string FileManager::getFile(const std::string& path)
{
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

void FileManager::writeFile(const std::string& path, const std::string& text)
{
    std::ofstream save {path, std::ios_base::trunc | std::ios_base::out};
    save.exceptions(std::ios::failbit);

    save << text;
    save.close();
}
