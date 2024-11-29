#include "Mago.h"


Mago::Mago()
{
    vidasMago = 10;
    _texture_Mago.loadFromFile("Resourses/Mago_spritever2.png");
    _spriteMago.setTexture(_texture_Mago);
    _spriteMago.setPosition(12550,465);
    _spriteMago.setScale(sf::Vector2f(-1.4,1.4));
    _state=STATES::STILL_LEFT;
    speed=2.f;

    _attackCooldownTime = sf::seconds(1.f);

    initVariables();
    _spriteMago.setTextureRect(_current_frame);

    shooting = new Shots(STYLE::SPELL, sf::Vector2f(0, 0), true);
    yaAtaco=false;
    dying=false;

}

Mago::~Mago()
{
    //dtor
}

void Mago::limitePantalla(){
    if (_spriteMago.getPosition().x<11180){
        _spriteMago.setPosition (11180,getPosition().y);

    }
    if (_spriteMago.getPosition().x>13250){
        _spriteMago.setPosition (13250,getPosition().y);

    }
}



void Mago::update(const sf::Vector2f& heroPosition, sf::Time deltaTime)
{
    limitePantalla();

    float positionX = _spriteMago.getPosition().x;
    float positionY = _spriteMago.getPosition().y;
    _time_shoot=_shoot_timer.getElapsedTime();

    if (_state == STATES::WALKING_LEFT || _state == STATES::WALKING_RIGHT) {
        TiempoCambioDireccion += deltaTime.asMilliseconds();

        if (TiempoCambioDireccion >= 200) {
            randomDirection = (rand() % 6 != 0) ? 1.0f : -1.0f;
            TiempoCambioDireccion = 0; //reinicia el tiempo
        }
    }

    distanciaPersonajes=heroPosition.x-_spriteMago.getPosition().x;


    switch (_state)
    {
    case STILL_RIGHT:
        _width_texture=70;
        _spriteMago.setScale(sf::Vector2f(1.4,1.4));
        _spriteMago.setTextureRect(sf::IntRect(14, 154, _width_texture, 104));
        break;
    case STILL_LEFT:
        _width_texture=70;
        _spriteMago.setScale(sf::Vector2f(-1.4,1.4));
        _spriteMago.setTextureRect(sf::IntRect(14, 154, _width_texture, 104));
        break;
    case WALKING_LEFT:
        _width_texture = 70;
        _xtexture = (int)_spriteMago.getPosition().x / 8 % 6;
        _xtexture = _xtexture * 75;
        _spriteMago.setScale(sf::Vector2f(-1.4, 1.4));
        _spriteMago.setTextureRect(sf::IntRect(_xtexture, 154, _width_texture, 104));

        _spriteMago.move(-speed * randomDirection, 0); // -speed para la izquierda, speed para la derecha
        _state = STATES::STILL_LEFT;
        break;

    case WALKING_RIGHT:
        _width_texture = 70;
        _xtexture = (int)_spriteMago.getPosition().x / 8 % 6;
        _xtexture = _xtexture * 75;
        _spriteMago.setScale(sf::Vector2f(1.4, 1.4));
        _spriteMago.setTextureRect(sf::IntRect(_xtexture, 154, _width_texture, 104));

        _spriteMago.move(speed * randomDirection, 0); // speed para la derecha, -speed para la izquierda
        _state = STATES::STILL_RIGHT;
        break;
    case SHOOTING_RIGHT:
        updateAnimation();
            if (_time_shoot.asSeconds() >= 4.0f )  //dispara si está en el rango
            {
                    positionX+=60;
                    positionY+=30;
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::SPELL, sf::Vector2f(positionX, positionY), true));
                    _shoot_timer.restart();

                }

        break;
    case SHOOTING_LEFT:
        updateAnimation();
            if (_time_shoot.asSeconds() >= 4.0f)
                {
                    positionX-=60;
                    positionY+=30;
                    _shots_array.push_back(std::make_unique<Shots>(STYLE::SPELL, sf::Vector2f(positionX, positionY), false));
                    _shoot_timer.restart();
                }
        break;
    case ATTACK_RIGHT:
        updateAnimation();
        break;
    case ATTACK_LEFT:
        updateAnimation();
        break;

   case ATTACKED_RIGHT:
        updateAnimation();
        break;
    case ATTACKED_LEFT:
        updateAnimation();
        break;

    case DEATH_RIGHT:
        updateAnimation();
        break;
    case DEATH_LEFT:
        updateAnimation();
        break;

    case DEATH:
        _spriteMago.setScale(sf::Vector2f(0, 0));
        break;
    }

    for (auto& shot : _shots_array)
    {
        shot->update();
    }
    _spriteMago.move(0,-_jump_force);
}

void Mago::mobility(const sf::Vector2f& heroPosition)
{
    arranqueNivel_1=false;
    distanciaPersonajes=_spriteMago.getPosition().x-heroPosition.x;

    if (distanciaPersonajes<800&&!dying){
        arranqueNivel_1=true;}

    if (_attackCooldown.getElapsedTime() < _attackCooldownTime) {

    return;
    }

    if(arranqueNivel_1==true){
    if (estaAtacando==false&&estaDisparando==false)
    {
        if (heroPosition.x>= _spriteMago.getPosition().x)
        {
        if (distanciaPersonajes>=-150&&distanciaPersonajes<=-50&&rand()%10!=0)
        {
            estaAtacando=true;
            _state=STATES::ATTACK_RIGHT;
            initVariables();
            _attackCooldown.restart();
            estaAtacando=false;
        }
        else if(distanciaPersonajes <= -110 && distanciaPersonajes >= -500&&_time_shoot.asSeconds() >= 4.0f )
        {
            estaDisparando==true;
            _state=STATES::SHOOTING_RIGHT;
            initVariables();
            _attackCooldown.restart();
            estaDisparando==false;
        }
        else{
        _state = STATES::WALKING_RIGHT;
        }
        }
        if (heroPosition.x < _spriteMago.getPosition().x)
        {
             if (distanciaPersonajes<=120&&distanciaPersonajes>=-50&&rand()%10!=0)
        {
            estaAtacando=true;
            _state=STATES::ATTACK_LEFT;
            initVariables();
            _attackCooldown.restart();
            estaAtacando=false;
        }
        else if(distanciaPersonajes >= 110 && distanciaPersonajes <= 500&&_time_shoot.asSeconds() >= 4.0f )
        {
            estaDisparando==true;
            _state=STATES::SHOOTING_LEFT;
            initVariables();
            _attackCooldown.restart();
            estaDisparando==false;
        }
        else{
        _state = STATES::WALKING_LEFT;
        }
        }
        }

    if(heroPosition.x>_spriteMago.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            _state=STATES::ATTACKED_RIGHT;
            initVariables();
        }
        else if (heroPosition.x<_spriteMago.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            _state=STATES::ATTACKED_LEFT;
            initVariables();
        }

   if(heroPosition.x>_spriteMago.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            _state=STATES::DEATH_RIGHT;
            initVariables();
            dying=true;
        }
        else if (heroPosition.x<_spriteMago.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            _state=STATES::DEATH_LEFT;
            initVariables();
            dying=true;
        }


    if(_spriteMago.getPosition().x<100)
    {
        _spriteMago.setPosition(100,_spriteMago.getPosition().y);
    }
    if(_spriteMago.getPosition().y<0)
    {
        _spriteMago.setPosition(_spriteMago.getPosition().x,0);
    }
}
}

sf::Sprite& Mago::getDraw()
{
    return _spriteMago;
}


sf::Vector2f Mago::getPosition()
{
    return _spriteMago.getPosition();
}

void Mago::setPosition(float x, float y)
{
    _spriteMago.setPosition(x,y);
}

void Mago::updateAnimation()
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
            }
            else if (_state == STATES::SHOOTING_LEFT)
            {
                _state = STATES::STILL_LEFT;
            }
            if (_state == STATES::ATTACK_RIGHT)
            {
                _state = STATES::STILL_RIGHT;
            }
            else if (_state == STATES::ATTACK_LEFT)
            {
                _state = STATES::STILL_LEFT;
            }
            if (_state == STATES::ATTACKED_RIGHT)
            {
                _state = STATES::STILL_RIGHT;
            }
            else if (_state == STATES::ATTACKED_LEFT)
            {
                _state = STATES::STILL_LEFT;
            }
            if (_state == STATES::DEATH_RIGHT)
            {
                _state = STATES::DEATH;
            }
            else if (_state == STATES::DEATH_LEFT)
            {
                _state = STATES::DEATH;
            }

        }
        // Actualizar el rectángulo de la textura
        _spriteMago.setTextureRect(_current_frame);

        // Reiniciar el temporizador
        _animationTimer.restart();
    }

}

void Mago::initVariables()
{

    switch (_state)
    {
    case SHOOTING_RIGHT:

        _width_texture = 72;
        _height_texture = 114;
        _end_of_frames_sheet = 411;
        _spriteMago.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 415, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case SHOOTING_LEFT:

        _width_texture = 72;
        _height_texture = 114;
        _end_of_frames_sheet = 411;
        _spriteMago.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 415, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_RIGHT:

        _width_texture = 97;
        _height_texture = 104;
        _end_of_frames_sheet = 571;
        _spriteMago.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 821, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_LEFT:

        _width_texture = 97;
        _height_texture = 104;
        _end_of_frames_sheet = 571;
        _spriteMago.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 821, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case ATTACKED_RIGHT:

        _width_texture = 102;
        _height_texture = 103;
        _end_of_frames_sheet = 655;
        _spriteMago.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(50, 1253, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case ATTACKED_LEFT:

        _width_texture = 102;
        _height_texture = 103;
        _end_of_frames_sheet = 655;
        _spriteMago.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(50, 1253, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case DEATH_RIGHT:

        _width_texture = 86;
        _height_texture = 116;
        _end_of_frames_sheet = 702;
        _spriteMago.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(7, 1093, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case DEATH_LEFT:

        _width_texture = 86;
        _height_texture = 116;
        _end_of_frames_sheet = 702;
        _spriteMago.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(7, 1093, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    }

}
sf::FloatRect Mago::getBounds() const {
    return _spriteMago.getGlobalBounds();  // Devuelve el rectángulo de colisión del sprite
}
void Mago::restarVida(int cantidad) {
    vidasMago -= cantidad;
    if (vidasMago < 0)
    {
    vidasMago = 0;  // No permitir vida negativa
    std::cout << "Vida de Mago: " << vidasMago << std::endl;
    isAlive=true;
    if(vidasMago==0){
       _state= STATES::DEATH_LEFT;
       _state= STATES::DEATH_RIGHT;
        _state= STATES::DEATH;
       dying=true;
    }
    }
}

