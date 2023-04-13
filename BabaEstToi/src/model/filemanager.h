#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

/**
 * @brief An I/O utility class
 *
 * Permits reading/writing to a given path. Any exception thrown during I/O operation is not caught.
 */
class FileManager
{
public:
    /**
     * @brief Reads a file and returns its contents
     *
     * @param path the file's path
     * @return the contents of a given file
     * @throws std::ios_base::failure if the file couldn't be found or insufficient rights
     */
    static std::string getFile(const std::string& path);

    /**
     * @brief Writes a string to a file.
     *
     * This method overwrites any file at the given path.
     *
     * @param path the output file's path
     * @param text the text to write
     * @throws std::ios_base::failure if writing is impossible due to insufficient rights, no disk space or other...
     */
    static void writeFile(const std::string& path, const std::string& text);
};

#endif // FILEMANAGER_H
