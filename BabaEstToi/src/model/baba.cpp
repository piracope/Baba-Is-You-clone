#include "baba.h"

namespace model
{

// GETTERS

std::string Baba::getState() const { return lvl_.getState(); }
Position Baba::getDimensions() const { return lvl_.getDimensions(); }

}
