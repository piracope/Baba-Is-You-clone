#include <iostream>
#include "model/level.h"
using namespace std;

int main()
{
    Level l {"18 24\nTEXT_WALL 14 14\nBABA 6 8 2"};

    cout << l.getDimensions().x << " " << l.getDimensions().y << endl;
    return 0;
}
