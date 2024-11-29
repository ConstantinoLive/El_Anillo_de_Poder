#include "Hero_1.h"
#include "Items.h"
#include "Colision.h"
#include <ctime>
#include <stdlib.h>
#include "Shots.h"

Hero_1::Hero_1()
{
    vida = 3;
    porcentajeVida = 100;
    energia = 100;
    isAlive = true;
    murio = false;
    _texture_hero.loadFromFile("Resourses/Legolas_sprite.png");
    //_sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width/2,0);//Para que se de vuelta
    _sprite_hero.setTexture(_texture_hero);
    _sprite_hero.setPosition(250,465); // posicion inicial
    _sprite_hero.setScale(sf::Vector2f(1.5,1.5));//

    _state=STATES::STILL_RIGHT; //estado inicial

    _jump_force=0; //Fuerza de salto inicial

    shootig = new Shots(STYLE::ARROW, sf::Vector2f(0, 0), true);
    shootig->setArrow(15);
    _death_frame_index = 0; // Índice inicial para animación de muerte
    _death_frames =
    {
        sf::IntRect(471, 887, 98, 87), // Primer cuadro (izquierda)
        sf::IntRect(575, 887, 98, 87), // Segundo cuadro
        sf::IntRect(670, 887, 75, 87), // Tercer cuadro
        sf::IntRect(740, 887, 67, 87), // Cuarto cuadro
        sf::IntRect(810, 887, 55, 87),
    };

}

/*Hero_1::~Hero_1()
{
    //dtor
}*/

void Hero_1::update()
{

    float positionX = _sprite_hero.getPosition().x;
    float positionY = _sprite_hero.getPosition().y;
    _time_shoot=_shoot_timer.getElapsedTime();

    switch (_state)
    {
    case STILL_RIGHT:
        _width_texture=44;
        _sprite_hero.setScale(sf::Vector2f(1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(8, 16, _width_texture, 86));
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width/2,0);//Para que se de vuelta
        break;
    case STILL_LEFT:
        _width_texture=44;
        _sprite_hero.setScale(sf::Vector2f(-1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(8, 16, _width_texture, 86));
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width/2,0);//Para que se de vuelta
        break;
    case WALKING_RIGHT:
        _width_texture=70.58;
        _xtexture=(int)_sprite_hero.getPosition().x/12 % 10;
        _xtexture=_xtexture*70.58;
        _sprite_hero.setScale(sf::Vector2f(1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(_xtexture,782,_width_texture,88));
        _sprite_hero.move(4,0);
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width/2,0);//Para que se de vuelta
        _state=STATES::STILL_RIGHT;
        break;
    case WALKING_LEFT:
        _width_texture=70.58;
        _xtexture=(int)_sprite_hero.getPosition().x/12 % 10;
        _xtexture=_xtexture*70.58;
        _sprite_hero.setScale(sf::Vector2f(-1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(_xtexture,782,_width_texture,88));
        _sprite_hero.move(-4,0);
        _sprite_hero.setOrigin(_sprite_hero.getGlobalBounds().width/2,0);//Para que se de vuelta
        _state=STATES::STILL_LEFT;
        break;
    case JUMPING:
        //Eliminar la gravedad

        break;
    case WALKING_RIGHT_JUMPING:
        _width_texture=58;
        _sprite_hero.setScale(sf::Vector2f(1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(76,116,_width_texture,82));
        _sprite_hero.move(4,0);
        _sprite_hero.move(0,-20);
        _jump_force += 4.5;
        _state=STATES::STILL_RIGHT;
        break;
    case WALKING_LEFT_JUMPING:
        _width_texture=58;
        _sprite_hero.setScale(sf::Vector2f(-1.5,1.5));
        _sprite_hero.setTextureRect(sf::IntRect(76,116,_width_texture,82));
        _sprite_hero.move(-4,0);
        _sprite_hero.move(0,-20);
        _jump_force += 4.5;
        _state=STATES::STILL_LEFT;

        break;
    case SHOOTING_RIGHT:
        updateAnimation();
        if(!yaDisparo)
        {
            if(_time_shoot.asSeconds() >= 0.5 )
            {
                if(Hero_1::shootig->getArrow()>0)
                {
                    positionX+=60;
                    positionY+=60;
                    Hero_1::shootig->setArrow(-1);
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::ARROW, sf::Vector2f(positionX, positionY), true));
                    std::cout<<Hero_1::shootig->getArrow()<<std::endl;
                    yaDisparo = true;
                    _shoot_timer.restart();

                }
            }

        }

        break;
    case SHOOTING_LEFT:
        updateAnimation();
        if(!yaDisparo)
        {
            if(_time_shoot.asSeconds() >= 0.5 )
            {
                if(Hero_1::shootig->getArrow()>0)
                {
                    positionX-=60;
                    positionY+=60;
                    Hero_1::shootig->setArrow(-1);
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::ARROW, sf::Vector2f(positionX, positionY), false));
                    std::cout<<Hero_1::shootig->getArrow()<<std::endl;
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

        if (_death_frame_index < _death_frames.size())
        {
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.2f)   // Intervalo más pequeño
            {
                _sprite_hero.setTextureRect(_death_frames[_death_frame_index]);
                _death_frame_index++;
                _animationTimer.restart();

            }
        }
        else
        {

            _sprite_hero.setTextureRect(_death_frames.back());
            _death_frame_index = 0;
        }
        return;

        break;

    }


    for (auto& shot : _shots_array)
    {
        shot->update();
    }
    _jump_force-=5; //fuerza de gravedad. Se ejerse siempre
    _sprite_hero.move(0,-_jump_force);
}

void Hero_1::mobility()
{
    if(_state==STATES::STILL_RIGHT||_state==STATES::STILL_LEFT)
    {
        yaDisparo=false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _state=STATES::WALKING_RIGHT;
            n=_state;
            setEstado(n);
            std::cout<<"x "<<_sprite_hero.getPosition().x<<std::endl;
            std::cout<<"y "<<_sprite_hero.getPosition().y<<std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _state=STATES::WALKING_LEFT;
            n=_state;
            setEstado(n);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _state=STATES::WALKING_RIGHT_JUMPING;
            n=_state;
            setEstado(n);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _state=STATES::WALKING_LEFT_JUMPING;
            n=_state;
            setEstado(n);
        }
        if (_state==STATES::STILL_RIGHT&&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _state=STATES::STILL_RIGHT;
        }
        if (_state==STATES::STILL_LEFT&&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _state=STATES::STILL_LEFT;

        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _state=STATES::WALKING_RIGHT_JUMPING;
        }*/
        if (_state==STATES::STILL_RIGHT&&sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _state=STATES::ATTACK_RIGHT;
            initVariables();
            attack=true;
            n=_state;
            setEstado(n);
        }
        if (_state==STATES::STILL_LEFT&&sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _state=STATES::ATTACK_LEFT;
            initVariables();
            attack=true;
            n=_state;
            setEstado(n);
        }
        if(_state==STATES::STILL_RIGHT&&sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& !isDPressed)
        {
            isAlive=true;
            isDPressed = true;
            _state=STATES::SHOOTING_RIGHT;
            initVariables();
            n=_state;
            setEstado(n);
        }
        else if (_state==STATES::STILL_LEFT&&sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& !isDPressed)
        {
            isAlive=true;
            isDPressed = true;
            _state=STATES::SHOOTING_LEFT;
            initVariables();
            n=_state;
            setEstado(n);
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            isDPressed =false;
            //yaDisparo =false;
        }
        if (_state == STATES::DEATH)   // Si el héroe está muerto, no se mueve
        {
            return;
        }


        /*
            if(_sprite_hero.getPosition().x<100)
            {
                _sprite_hero.setPosition(100,_sprite_hero.getPosition().y);
            }
            if(_sprite_hero.getPosition().y<0)
            {
                _sprite_hero.setPosition(_sprite_hero.getPosition().x,0);
            }


        /////////////////////////level 2
            if(_sprite_hero.getPosition().y>600){
                caida=true;
            }

            if(_sprite_hero.getPosition().y<800&&caida==true)
            {
                _sprite_hero.setPosition(_sprite_hero.getPosition().x,800);
            }

            else if(_sprite_hero.getPosition().y<0)
            {
                _sprite_hero.setPosition(_sprite_hero.getPosition().x,0);
            }*/

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
    if(_state==STATES::STILL_RIGHT||_state==STATES::STILL_LEFT||_state==STATES::SHOOTING_RIGHT||_state==STATES::SHOOTING_LEFT||_state==STATES::ATTACK_RIGHT||_state==STATES::ATTACK_LEFT||_state==STATES::COLISION_LEFT||_state==STATES::COLISION_RIGHT)
    {
        _jump_force=0;
        _sprite_hero.setPosition(x,y);
    }
}

sf::Vector2f Hero_1::getPosition()
{
    return _sprite_hero.getPosition();
}

void Hero_1::setPosition(float x, float y)
{
    _sprite_hero.setPosition(x,y);
}

void Hero_1::setEstado(int n)
{
    Estado=n;
}

int Hero_1::getEstado()
{
    return Estado;
}

void Hero_1::updateAnimation()
{
    if (_animationTimer.getElapsedTime().asSeconds() >= 0.09f)
    {
        // Avanzar al siguiente frame
        _current_frame.left += _width_texture;

        // Verificar si llegamos al final de la secuencia de animación
        if (_current_frame.left >= _end_of_frames_sheet)
        {
            // Volver al primer frame de la secuencia
            _current_frame.left = _first_frame_of_sheet.left;

            // Si completamos la animación de disparo, volvemos al estado de quietud
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
            if(_state==STATES::DEATH)
            {

            }
        }
        // Actualizar el rectángulo de la textura
        _sprite_hero.setTextureRect(_current_frame);

        // Reiniciar el temporizador
        _animationTimer.restart();
    }




}

void Hero_1::initVariables()
{

    switch (_state)
    {
    case SHOOTING_RIGHT:

        _width_texture = 81.30;  // Ancho de cada frame de la animación de disparo
        _height_texture = 114;   // Altura de cada frame de la animación de disparo
        _end_of_frames_sheet = 571.0; // Posición final de los frames de la hoja de sprites
        _sprite_hero.setScale(sf::Vector2f(1.4, 1.4));  // Escala para disparar hacia la derecha
        _first_frame_of_sheet = sf::IntRect(0, 250, _width_texture, _height_texture); // Primer frame del disparo hacia la derecha
        _current_frame = _first_frame_of_sheet;  // Inicializar el frame actual
        break;
    case SHOOTING_LEFT:

        _width_texture = 81.30;
        _height_texture = 114;
        _end_of_frames_sheet = 571.0;
        _sprite_hero.setScale(sf::Vector2f(-1.4, 1.4));  // Escala negativa para disparar hacia la izquierda
        _first_frame_of_sheet = sf::IntRect(0, 250, _width_texture, _height_texture); // Primer frame del disparo hacia la izquierda
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_RIGHT:

        _width_texture = 80.2;  // Ancho de cada frame de la animación de disparo
        _height_texture = 98;   // Altura de cada frame de la animación de disparo
        _end_of_frames_sheet = 638; // Posición final de los frames de la hoja de sprites
        _sprite_hero.setScale(sf::Vector2f(1.4, 1.4));  // Escala para disparar hacia la derecha
        _first_frame_of_sheet = sf::IntRect(0, 503, _width_texture, _height_texture); // Primer frame del disparo hacia la derecha
        _current_frame = _first_frame_of_sheet;  // Inicializar el frame actual
        break;
    case ATTACK_LEFT:

        _width_texture = 80.2;
        _height_texture = 98;
        _end_of_frames_sheet = 638;
        _sprite_hero.setScale(sf::Vector2f(-1.4, 1.4));  // Escala negativa para disparar hacia la izquierda
        _first_frame_of_sheet = sf::IntRect(0, 503, _width_texture, _height_texture); // Primer frame del disparo hacia la izquierda
        _current_frame = _first_frame_of_sheet;
        break;
    case COLISION_RIGHT:

        break;
    case COLISION_LEFT:

        break;
    case DEATH:
        _end_of_frames_sheet = 868;
        _sprite_hero.setScale(sf::Vector2f(1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(471, 887, _width_texture, 88);
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
    if (vida > 0)   // Si todavía tiene vidas restantes
    {
        isAlive = true;
        porcentajeVida = 100; // Restaurar porcentaje de vida
        energia = 100;        // Restaurar energía
        std::cout << "Perdiste una vida. Vidas restantes: " << vida << std::endl;
        std::cout << "Porcentaje de vida y energía restaurados: " << porcentajeVida << ", " << energia << std::endl;
    }
    else     // Si ya no tiene vidas restantes
    {
        vida = 0;
        isAlive = false;
        _state = STATES::DEATH;
        murio = true;
        _animationTimer.restart();
        std::cout << "El héroe ha muerto. VIDAS: " << vida << std::endl;
    }
}
void Hero_1::actualizarEstado()
{
    if (!isAlive)
    {
        porcentajeVida = 0;
        energia = 0;
        return;
    }
    if (porcentajeVida > 100)
    {
        porcentajeVida = 100;
    }
    if (energia > 100)
    {
        energia = 100;
    }
    if (porcentajeVida <= 0 || energia <= 0)
    {
        porcentajeVida = 0;
        energia = 0;
        std::cout << "Porcentaje de vida o energia agotados. Pierdes 1 vida." << std::endl;
        restarVidas(1);
    }
}
