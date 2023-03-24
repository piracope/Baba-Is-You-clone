#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
    inline static const std::string START_OF_PATH {"levels/level_"};
public: // FIXME : this should be low level file reading, remove "level" abstraction
    static std::string getLevel(unsigned);
    static void writeSave(std::string);
    static std::string readSave(); // TODO : also save lvlNumber
};

#endif // FILEMANAGER_H
