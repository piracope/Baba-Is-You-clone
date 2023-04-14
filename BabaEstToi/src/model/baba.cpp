#include "baba.h"
#include "filemanager.h"

namespace model
{

Baba::Baba() : lvl_ {FileManager::getLevel(999)}, lvlNumber_ {0}
{}

void Baba::createLevel(unsigned nb)
{
    lvl_ = FileManager::getLevel(nb);
    lvlNumber_ = nb;
}

void Baba::restart() {
    lvl_ = FileManager::getLevel(lvlNumber_);
    notifyObservers();
}
void Baba::save() const { FileManager::writeSave(lvl_.getState());}

void Baba::load() {
    notifyObservers();
}

void Baba::move(Direction dir) {
    lvl_.movePlayer(dir);
    notifyObservers();
}

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
