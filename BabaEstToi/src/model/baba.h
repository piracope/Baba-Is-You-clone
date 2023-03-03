#ifndef BABA_H
#define BABA_H

#include <ostream>

class Baba{
    unsigned lvlNumber;
    void createLevel(unsigned);

public:
    Baba();
    void restart();
    void save();
    void load();
    void move();
    std::string getState();
};

#endif // BABA_H
