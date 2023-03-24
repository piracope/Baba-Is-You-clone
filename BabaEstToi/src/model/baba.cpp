#include "baba.h"
#include "filemanager.h"

namespace model
{

Baba::Baba() : lvl_ {FileManager::getLevel(0)}, lvlNumber_ {0}
{}

void Baba::createLevel(unsigned nb)
{
    lvl_ = FileManager::getLevel(nb);
    lvlNumber_ = nb;
}

void Baba::restart() { lvl_ = FileManager::getLevel(lvlNumber_); }
void Baba::save() const { FileManager::writeSave(lvl_.getState());}

void Baba::move(Direction dir) { lvl_.movePlayer(dir); }

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
