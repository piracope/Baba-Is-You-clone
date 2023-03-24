#ifndef BABA_H
#define BABA_H

#include <string>

#include "level.h"
#include "../observer/subject.h"

namespace model
{

class Baba : public Subject
{
    unsigned lvlNumber_;
    Level lvl_;

    void createLevel(unsigned);

public:
    Baba();
    void restart();
    void save() const; // FIXME : handle lvlNumber
    void load(); // TODO
    void move(Direction); // TODO
    std::string getState() const;
    Position getDimensions() const;
};

}

#endif // BABA_H
