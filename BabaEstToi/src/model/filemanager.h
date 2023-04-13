#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
public:
    static std::string getFile(std::string);
    static void writeFile(std::string, std::string);
};

#endif // FILEMANAGER_H
