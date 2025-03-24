#include "Hero_1.h"
#include "Items.h"
#include "Colision.h"
#include <ctime>
#include <stdlib.h>
#include "Shots.h"


Hero_1::Hero_1()
{
    vida = 3;
    energia = 100;
    _texture_hero.loadFromFile("Resourses/Legolas_sprite_3.png");
    _texture_hero.setSmooth(true);
    _sprite_hero.setTexture(_texture_hero);
    _sprite_hero.setPosition(250, 465); // Posición inicial
    _sprite_hero.setScale(sf::Vector2f(1.5, 1.5));
    _state = STATES::STILL_RIGHT; // Estado inicial
    _jump_force = 0; // Fuerza de salto inicial


    shootig = new Shots(STYLE::ARROW, sf::Vector2f(0, 0), true);
    shootig->setArrow(15);


}

void Hero_1::update()
{
    // Lógica normal de actualización del personaje
    float positionX = _sprite_hero.getPosition().x;
    float positionY = _sprite_hero.getPosition().y;
    _time_shoot = _shoot_timer.getElapsedTime();

    switch (_state)
    {
    case STILL_RIGHT:
        _width_texture = 44;
        _sprite_hero.setScale(sf::Vector2f(1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(8, 16, _width_texture, 86));
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width / 2, 0);
        break;
    case STILL_LEFT:
        _width_texture = 44;
        _sprite_hero.setScale(sf::Vector2f(-1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(8, 16, _width_texture, 86));
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width / 2, 0);
        break;
    case WALKING_RIGHT:
        _width_texture = 70.58;
        _xtexture = (int)_sprite_hero.getPosition().x / 12 % 10;
        _xtexture = _xtexture * 70.58;
        _sprite_hero.setScale(sf::Vector2f(1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(_xtexture, 782, _width_texture, 88));
        _sprite_hero.move(4, 0);
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width / 2, 0);
        _state = STATES::STILL_RIGHT;
        break;
    case WALKING_LEFT:
        _width_texture = 70.58;
        _xtexture = (int)_sprite_hero.getPosition().x / 12 % 10;
        _xtexture = _xtexture * 70.58;
        _sprite_hero.setScale(sf::Vector2f(-1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(_xtexture, 782, _width_texture, 88));
        _sprite_hero.move(-4, 0);
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width / 2, 0);
        _state = STATES::STILL_LEFT;
        break;
    case JUMPING:
        break;
    case WALKING_RIGHT_JUMPING:
        _width_texture = 58;
        _sprite_hero.setScale(sf::Vector2f(1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(76, 116, _width_texture, 82));
        _sprite_hero.move(4, 0);
        _sprite_hero.move(0, -16);
        _jump_force += 4.5;
        _state = STATES::STILL_RIGHT;
        break;
    case WALKING_LEFT_JUMPING:
        _width_texture = 58;
        _sprite_hero.setScale(sf::Vector2f(-1.5, 1.5));
        _sprite_hero.setTextureRect(sf::IntRect(76, 116, _width_texture, 82));
        _sprite_hero.move(-4, 0);
        _sprite_hero.move(0, -16);
        _jump_force += 4.5;
        _state = STATES::STILL_LEFT;
        break;
    case SHOOTING_RIGHT:
        updateAnimation();
        if (!yaDisparo)
        {
            if (_time_shoot.asSeconds() >= 0.5)
            {
                if (Hero_1::shootig->getArrow() > 0)
                {
                    positionX += 60;
                    positionY += 60;
                    Hero_1::shootig->setArrow(-1);
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::ARROW, sf::Vector2f(positionX, positionY), true));
                    std::cout << Hero_1::shootig->getArrow() << std::endl;
                    yaDisparo = true;
                    _shoot_timer.restart();
                }
            }
        }
        break;
    case SHOOTING_LEFT:
        updateAnimation();
        if (!yaDisparo)
        {
            if (_time_shoot.asSeconds() >= 0.5)
            {
                if (Hero_1::shootig->getArrow() > 0)
                {
                    positionX -= 60;
                    positionY += 60;
                    Hero_1::shootig->setArrow(-1);
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::ARROW, sf::Vector2f(positionX, positionY), false));
                    std::cout << Hero_1::shootig->getArrow() << std::endl;
                    yaDisparo = true;
                    _shoot_timer.restart();
                }
            }

        }
        break;
    case ATTACK_RIGHT:
        updateAnimation();
        break;
    case ATTACK_LEFT:
        updateAnimation();
        break;
    case DEATH:
        updateAnimation();
        break;
    }

    for (auto& shot : _shots_array)
    {
        shot->update();
    }
    _jump_force -= 5; // Fuerza de gravedad
    _sprite_hero.move(0, -_jump_force);
}


void Hero_1::mobility()
{
    if ((_state == STATES::STILL_RIGHT || _state == STATES::STILL_LEFT)&&isAlive)
    {
        yaDisparo = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _state = STATES::WALKING_RIGHT;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _state = STATES::WALKING_LEFT;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _state = STATES::WALKING_RIGHT_JUMPING;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _state = STATES::WALKING_LEFT_JUMPING;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (_state == STATES::STILL_RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _state = STATES::STILL_RIGHT;
        }
        if (_state == STATES::STILL_LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _state = STATES::STILL_LEFT;
        }
        if (_state == STATES::STILL_RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _state = STATES::ATTACK_RIGHT;
            initVariables();
            attack = true;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (_state == STATES::STILL_LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _state = STATES::ATTACK_LEFT;
            initVariables();
            attack = true;
            numEstado = _state;
            setEstado(numEstado);
        }
        if (_state == STATES::STILL_RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isDPressed)
        {
            isDPressed = true;
            _state = STATES::SHOOTING_RIGHT;
            initVariables();
            numEstado = _state;
            setEstado(numEstado);
        }
        else if (_state == STATES::STILL_LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isDPressed)
        {
            isDPressed = true;
            _state = STATES::SHOOTING_LEFT;
            initVariables();
            numEstado = _state;
            setEstado(numEstado);
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            isDPressed = false;
        }
        if (_sprite_hero.getPosition().x < 100)
        {
            _sprite_hero.setPosition(100, _sprite_hero.getPosition().y);
        }
        if  (_sprite_hero.getPosition().x > 13250)
        {
            _sprite_hero.setPosition(13250, _sprite_hero.getPosition().y);
        }
    }
    else if((_state == STATES::STILL_RIGHT || _state == STATES::STILL_LEFT|| _state == STATES::ATTACK_LEFT|| _state == STATES::ATTACK_RIGHT|| _state == STATES::SHOOTING_LEFT||
             _state == STATES::SHOOTING_RIGHT|| _state == STATES::WALKING_LEFT|| _state == STATES::WALKING_RIGHT|| _state == STATES::WALKING_LEFT_JUMPING||
             _state == STATES::WALKING_RIGHT_JUMPING)&&!isAlive)
    {
        //deathTimer.restart();
        if(!isFallen&&!isAlive)
        {
            std::cout<<"sin caida"<<std::endl;
            _state = STATES::DEATH;
            initVariables();
            numEstado = _state;
            setEstado(numEstado);
            deathTimer.restart();
        }
        if(isFallen==true&&!isAlive)
        {
            std::cout<<"con caida"<<std::endl;
            _state = STATES::DEATH;
            numEstado = _state;
            setEstado(numEstado);
            //restarVidas(1);
            //actualizarEstado();
            d_r=true;
        }
    }
}

sf::Sprite& Hero_1::getDraw()
{
    return _sprite_hero;
}

sf::FloatRect Hero_1::getBounds() const
{
    return _sprite_hero.getGlobalBounds();
}

void Hero_1::floor(float x, float y)
{
    if (_state == STATES::STILL_RIGHT || _state == STATES::STILL_LEFT || _state == STATES::SHOOTING_RIGHT ||
            _state == STATES::SHOOTING_LEFT || _state == STATES::ATTACK_RIGHT || _state == STATES::ATTACK_LEFT ||
            _state == STATES::DEATH)
    {
        _jump_force = 0;
        _sprite_hero.setPosition(x, y);
    }

}

sf::Vector2f Hero_1::getPosition()
{
    return _sprite_hero.getPosition();
}

void Hero_1::setPosition(float x, float y)
{
    _sprite_hero.setPosition(x, y);
}

void Hero_1::setLastPosition()
{
    lastPosition = getPosition();
}

void Hero_1::setEstado(int numE)
{
    numEstado = numE;
}

int Hero_1::getEstado()
{
    return numEstado;
}

void Hero_1::updateReborn()
{
    //std::cout<<"1"<<std::endl;
    if(!isFallen&&isAlive==false)
    {
        std::cout<<"1"<<std::endl;
        //isAlive = true;
        _state = STATES::STILL_RIGHT;
        numEstado = _state;
        setEstado(numEstado);
        setLastPosition();
        if(getVida()>0)
        {
            setEnergia(100);

        }
        else
        {
            setEnergia(0);
        }
        isFallen=false;
        isAlive = true;
    }
    else if(isFallen==true&&isAlive==false)
    {
        _state = STATES::STILL_RIGHT;
        numEstado = _state;
        setEstado(numEstado);

        if(_sprite_hero.getPosition().x>4160&&_sprite_hero.getPosition().x<4755&&isAlive==false)
        {
            _sprite_hero.setPosition(_sprite_hero.getPosition().x-855,485);
            //isFallen=false;
           // isAlive = true;
            std::cout<<"2"<<std::endl;
            std::cout<<_sprite_hero.getPosition().x<<std::endl;
        }
        if(_sprite_hero.getPosition().x>=4755&&isAlive==false)
        {
            _sprite_hero.setPosition(_sprite_hero.getPosition().x-220,485);
            //isFallen=false;
            //isAlive = true;
            std::cout<<"3"<<std::endl;
            std::cout<<_sprite_hero.getPosition().x<<std::endl;
        }
        restarVidas(1);
        actualizarEstado();
        setLastPosition();
        if(getVida()>0)
        {
            setEnergia(100);

        }
        else
        {
            setEnergia(0);
        }
        //isFallen=false;
        //isAlive = true;
    }
    isFallen=false;
    isAlive = true;

}

void Hero_1::updateAnimation()
{
    if (_animationTimer.getElapsedTime().asSeconds() >= 0.09f)
    {
        _current_frame.left += _width_texture;

        if (_current_frame.left >= _end_of_frames_sheet)
        {
            _current_frame.left = _first_frame_of_sheet.left;

            if (_state == STATES::SHOOTING_RIGHT)
            {
                _state = STATES::STILL_RIGHT;
                yaDisparo = false;
            }
            else if (_state == STATES::SHOOTING_LEFT)
            {
                _state = STATES::STILL_LEFT;
                yaDisparo = false;
            }
            if (_state == STATES::ATTACK_RIGHT)
            {
                _state = STATES::STILL_RIGHT;
            }
            else if (_state == STATES::ATTACK_LEFT)
            {
                _state = STATES::STILL_LEFT;
            }
            if (_state == STATES::DEATH)
            {
                if(!isFallen)
                {
                    d_r = true;
                    if (deathTimer.getElapsedTime().asSeconds() > 3.f)
                    {
                        d_r = false;
                        updateReborn();
                    }
                }
                else
                {
                    d_r = false;
                    updateReborn();
                }
            }
        }
        _sprite_hero.setTextureRect(_current_frame);
        _animationTimer.restart();
    }
}

void Hero_1::initVariables()
{
    switch (_state)
    {
    case SHOOTING_RIGHT:
        _width_texture = 81.30;
        _height_texture = 114;
        _end_of_frames_sheet = 571.0;
        _sprite_hero.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 250, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case SHOOTING_LEFT:
        _width_texture = 81.30;
        _height_texture = 114;
        _end_of_frames_sheet = 571.0;
        _sprite_hero.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 250, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_RIGHT:
        _width_texture = 80.2;
        _height_texture = 98;
        _end_of_frames_sheet = 638;
        _sprite_hero.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 503, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_LEFT:
        _width_texture = 80.2;
        _height_texture = 98;
        _end_of_frames_sheet = 638;
        _sprite_hero.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 503, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case DEATH:
        _width_texture = 87;
        _height_texture = 90;
        _end_of_frames_sheet = 593;
        _sprite_hero.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 885, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    }
}

float Hero_1::getJump_force()
{
    return _jump_force;
}

void Hero_1::restarVidas(int cantidad)
{
    vida -= cantidad;
    isAlive = false;
    if (vida <= 0)
    {
        setVida(0);
    }
}

void Hero_1::actualizarEstado()
{
    if (!isAlive)
    {
        setEnergia(0);
        return;
    }
    if (getEnergia() > 100)
    {
        setEnergia(100);
    }
    if (getEnergia() <= 0)
    {
        setEnergia(0);
        restarVidas(1);
    }
}


