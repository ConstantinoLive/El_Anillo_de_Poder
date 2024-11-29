#include <stdlib.h>
#include "Hero_1.h"
#include "Items.h"
Items::Items()
{
    obtenido = false;
    _texture_items.loadFromFile("Resourses/flechas.png");
    _sprite_items.setOrigin(_sprite_items.getGlobalBounds().width / 2, _sprite_items.getGlobalBounds().height / 2);  // Para que se de vuelta
    _sprite_items.setTexture(_texture_items);
    i=0;

}
void Items::update(int n)
{
    respawn(n);
}

sf::FloatRect Items::getBounds()const
{
    return _sprite_items.getGlobalBounds();
}


sf::Sprite Items::getDraw()const
{
    return _sprite_items;
}

void Items::respawn(int n)
{
    int positionsX[] = {3500, 6600, 9300,10500,3500,6650,8300,10500};
    int positionsY[]= {500,230,230,300,1230,970,900,970};

    _sprite_items.setPosition(positionsX[n], positionsY[n]);

}

