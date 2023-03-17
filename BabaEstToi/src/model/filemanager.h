#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
    inline static const std::string START_OF_PATH {"levels/level_"};
public:
    static std::string getLevel(unsigned);
    static void writeSave(std::string);
    static std::string readSave(); // TODO : penser au fait que y a le n° de fichier à gérer
};

#endif // FILEMANAGER_H
