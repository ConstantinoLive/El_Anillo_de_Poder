#ifndef MANAGER_WOLF_H
#define MANAGER_WOLF_H
#include <vector>
#include "Enemy_wolf.h"

class Manager_wolf
{
public:
    Manager_wolf();
    virtual ~Manager_wolf();

    void Add_wolf(Enemy_wolf* w);

    std::vector<Enemy_wolf*>  _array_wolf;


};

#endif // MANAGER_WOLF_H
