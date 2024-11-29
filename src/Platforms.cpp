#include "Platforms.h"

Platforms::Platforms()
{
    _texture_platform.loadFromFile("Resourses/Plataformas.png");
    _sprite_platform.setTexture(_texture_platform);
    _sprite_platform.setPosition(-650,-10);

    _sprite_platform.scale(sf::Vector2f(2.6f,2.6f));//(2.7f,2.7f)
}

Platforms::~Platforms()
{
    //dtor
}

sf::Sprite& Platforms::getDraw()
{
    return _sprite_platform;
}
