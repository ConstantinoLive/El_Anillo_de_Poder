#ifndef PLATFORMS_RECTANGLE_SHAPE_H
#define PLATFORMS_RECTANGLE_SHAPE_H
#include <SFML/Graphics.hpp>

class Platforms_rectangle_shape
{
public:
    Platforms_rectangle_shape() : _rec(sf::Vector2f(0.f, 0.f)) { }
    Platforms_rectangle_shape(float base, float x, float y);
    virtual ~Platforms_rectangle_shape();
    sf::RectangleShape& getDraw();


private:
    sf::RectangleShape _rec;
};

#endif // PLATFORMS_RECTANGLE_SHAPE_H
