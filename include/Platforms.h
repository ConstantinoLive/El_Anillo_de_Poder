#ifndef PLATFORMS_H
#define PLATFORMS_H
#include <SFML/Graphics.hpp>

class Platforms
{
public:
    Platforms();
    virtual ~Platforms();
    void update();
    sf::Sprite& getDraw();

private:
    sf::Sprite _sprite_platform;
    sf::Texture _texture_platform;
};

#endif // PLATFORMS_H
