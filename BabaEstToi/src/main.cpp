#include <iostream>
#include "model/baba.h"
#include "view/view.h"
#include "controller/controller.h"
using namespace std;

int main()
{
    controller::Controller c {};
    string line;
    cin >> line;
    while (line != "exit")
    {
        c.play(line);
        cin >> line;
    }
    return 0;
}
