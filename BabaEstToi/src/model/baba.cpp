#include "baba.h"
#include "filemanager.h"

namespace model
{

void Baba::createLevel(unsigned nb)
{
    lvl_ = FileManager::getLevel(nb);
    lvlNumber_ = nb;
}

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
