#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
    inline static const std::string START_OF_PATH {"levels/level_"};
public:
    static std::string getLevel(unsigned);
    // TODO : writeLevel -> save and getLevel(path) -> save
};

#endif // FILEMANAGER_H
