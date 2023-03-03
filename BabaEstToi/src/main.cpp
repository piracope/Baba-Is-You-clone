#include <iostream>
#include "../BabaEstToi/model/gameobject.h"
#include "../BabaEstToi/model/text.h"

using namespace std;

int main()
{
    GameObject truc{ObjectType::BABA,Categorie::ELEM,0};
    cout << truc << endl;
    Text foo{ObjectType::TEXT_WALL,Categorie::ELEM,0};
    cout << foo << endl;
    return 0;
}
