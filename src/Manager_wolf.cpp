#include "Manager_wolf.h"

Manager_wolf::Manager_wolf()
{
    //ctor
}

Manager_wolf::~Manager_wolf()
{
    //dtor
}

void Manager_wolf::Add_wolf(Enemy_wolf* w)
{
    _array_wolf.push_back(w);
}
