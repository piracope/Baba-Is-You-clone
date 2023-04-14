#include <sstream>

#include "baba.h"
#include "filemanager.h"

namespace model
{

Baba::Baba() : lvl_ {FileManager::getFile(START_OF_PATH + "0.txt")}, lvlNumber_ {0}
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
void Baba::save() const
{
    std::stringstream savefile;
    savefile << lvlNumber_ << "\n" << lvl_.getState();
    FileManager::writeFile(START_OF_PATH + "S.txt", savefile.str());
}

void Baba::load()
{
    std::istringstream savefile {FileManager::getFile(START_OF_PATH + "S.txt")};
    std::string lvl;
    savefile >> lvlNumber_; // first line : number
    savefile.ignore(99999, '\n'); // we go to the next line

    // thanks ChatGPT
    std::string line;
    while (std::getline(savefile, line)) {
        lvl += line + "\n"; // we construct the level string
    }

    lvl_ = lvl; // and we pass that to the constr
    notifyObservers();
}

void Baba::move(Direction dir) {
    lvl_.movePlayer(dir);
    if(lvl_.isWon()) {
        try {
            createLevel(lvlNumber_ + 1);
        } catch (const std::ios_base::failure&) {
            createLevel(0); // we go back to first level when won
        }
    }
    else notifyObservers();
}

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
