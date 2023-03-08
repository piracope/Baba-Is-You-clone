#ifndef BABA_H
#define BABA_H

#include <string>

namespace model {
class Baba{
    unsigned lvlNumber_;
    void createLevel(unsigned);

public:
    Baba();
    void restart();
    void save();
    void load();
    void move();
    std::string getState();
};
}

#endif // BABA_H
