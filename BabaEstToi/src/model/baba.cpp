#include <sstream>

#include "baba.h"
#include "filemanager.h"

namespace model
{

Baba::Baba() : lvl_ {FileManager::getFile(START_OF_PATH + "3.txt")}, lvlNumber_ {0}
{
    notifyObservers();
}

void Baba::createLevel(unsigned nb)
{
    std::stringstream path;
    path << START_OF_PATH << nb << ".txt";
    lvl_ = FileManager::getFile(path.str());
    lvlNumber_ = nb;
    notifyObservers();
}

void Baba::restart() { createLevel(lvlNumber_); }
void Baba::save() const { FileManager::writeFile(START_OF_PATH + "S.txt", lvl_.getState());}

void Baba::move(Direction dir) {
    lvl_.movePlayer(dir);
    if(lvl_.isWon()) {
        try {
            createLevel(lvlNumber_ + 1);
        } catch (const std::ios_base::failure&) {
            createLevel(0);
        }
    }
    notifyObservers();
}

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
