#include "Platforms_rectangle_shape.h"

Platforms_rectangle_shape::Platforms_rectangle_shape(float base, float x, float y)
{
    _rec.setPosition(x,y);
    _rec.setSize(sf::Vector2f(base,10.f));
    _rec.setFillColor(sf::Color(100, 250, 50,0));
}

Platforms_rectangle_shape::~Platforms_rectangle_shape()
{
    //dtor
}

sf::RectangleShape& Platforms_rectangle_shape::getDraw()
{
    return _rec;
}
