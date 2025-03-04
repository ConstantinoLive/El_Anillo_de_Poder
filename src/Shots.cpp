#include "Shots.h"
#include "Sauron.h"

Shots::Shots()
{
    initTexture();
    initVariables();
    initAnimation();
}
Shots::Shots(STYLE style,sf::Vector2f pos, bool right)
{

    _style=style;
    _position=pos;
    _right=right;
    initTexture();
    initVariables();
    initAnimation(); //usar en otros disparos

}

Shots::~Shots()
{

}


sf::Sprite& Shots::getDraw()
{
    return _sprite_shot;
}

void Shots::initVariables()
{
    switch(_style)
    {
    case ARROW:
        _width_texture=35;
        _height_texture=10;
        _sprite_shot.setTextureRect(sf::IntRect(197, 409, _width_texture, _height_texture)); //reemplaza a las dos lineas anteriores. Usara esas lineas para otros disparos
        _damage_shoot=3;
        break;
    case SPELL:
        _width_texture=30;
        _height_texture=35;
        _sprite_shot.setTextureRect(sf::IntRect(930, 577, _width_texture, _height_texture));
        _damage_shoot=5;
        break;
    }
}

void Shots::initAnimation() //usar en otros disparos
{
    _animationTimer.restart();
}

void Shots::initTexture()
{
    switch(_style)
    {
    case STYLE::ARROW:
        _texture_shot.loadFromFile("Resourses/Legolas_sprite.png");
        _sprite_shot.setTexture(_texture_shot);
        _sprite_shot.setPosition(_position.x,_position.y);
        _sprite_shot.setOrigin(_width_texture/2,0);
        break;
    case STYLE::SPELL:
        _texture_shot.loadFromFile("Resourses/Mago_spritever2.png");
        _sprite_shot.setTexture(_texture_shot);
        _sprite_shot.setPosition(_position.x,_position.y);
        _sprite_shot.setOrigin(_width_texture/2,0);
        break;
    }
}

int Shots::getDamage()
{
    return _damage_shoot;
}

void Shots::mobility()
{
    if(_right)
    {
        _sprite_shot.setScale(sf::Vector2f(1.2,1.2));
        _sprite_shot.move(15,-0.5);
    }
    else
    {
        _sprite_shot.setScale(sf::Vector2f(-1.2,1.2));
        _sprite_shot.move(-15,-0.5);
    }
}

void Shots::updateAnimation() //usar en otros disparos
{
    ///cada 0.1 seg cambio la animacion
    if(_animationTimer.getElapsedTime().asSeconds() >= 0.1)
    {
        _current_frame.left += _width_texture;
        if(_current_frame.left>=_end_of_frames_sheet)
        {
            _current_frame.left=_first_frame_of_sheet.left;
        }
        _animationTimer.restart();
        _sprite_shot.setTextureRect(_current_frame);
    }

    //ahora invierto o no, segun la direccion

    if(_right)  //va a la derecha
    {
        _sprite_shot.setScale(sf::Vector2f(0.9,0.9));
    }
    else  //va a la izquierda
    {
        _sprite_shot.setScale(sf::Vector2f(-0.9,0.9));
    }
}

void Shots::update()
{
    mobility();

}

STYLE Shots::getStyle()
{
    return _style;
}

int Shots::getArrow()
{
    return _cant_arrow;
}

void Shots::setArrow(int a)
{
    _cant_arrow+=a;
}
sf::FloatRect Shots::getBounds() const
{
    return _sprite_shot.getGlobalBounds();
}

