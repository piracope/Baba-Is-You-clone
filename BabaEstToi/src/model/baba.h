#ifndef BABA_H
#define BABA_H

#include <ostream>

class Baba{
    unsigned lvlNumber;

    Baba();
    void restart();
    void save();
    void load();
    void move();
    std::string getState();
    private:
    void createLevel(unsigned);

};

#endif // BABA_H
