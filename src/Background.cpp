#include "Background.h"

Background::Background()
{
    _texture_fondo.loadFromFile("Resourses/background_1.png");
    _sprite_fondo.setTexture(_texture_fondo);
    _sprite_fondo.setPosition(-650,-170);

    _sprite_fondo.scale(sf::Vector2f(2.6f,2.6f));//(2.7f,2.7f)


}

Background::~Background()
{
    //dtor
}

void Background::update()
{

}

sf::Sprite& Background::getDraw()
{
    return _sprite_fondo;
}

