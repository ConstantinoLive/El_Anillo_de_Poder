#include "Sauron.h"


Sauron::Sauron()
{
    vidas = 10;
    srand(time(nullptr));
    _texture_Sauron.loadFromFile("Resourses/Sauron_sprite.png");
    _spriteSauron.setTexture(_texture_Sauron);
    _spriteSauron.setPosition(5050,1175); // posicion inicial
    _spriteSauron.setScale(sf::Vector2f(-1.4,1.4));
    _state=STATES::STILL_LEFT; //estado inicial

    _isDisappearing = false;
    estaAtacando=false;
    beingAttacked=false;
    dying=false;
    _Desaparecido=false;
    volverAPegar=true;
}
Sauron::~Sauron()
{
    //dtor
}

void Sauron::limitePantalla(){
    if (_spriteSauron.getPosition().x<150){
        _spriteSauron.setPosition (150,getPosition().y);

    }
    if (_spriteSauron.getPosition().x>13250){
        _spriteSauron.setPosition (12250,getPosition().y);

    }
}


void Sauron::update(const sf::Vector2f& heroPosition, sf::Time deltaTime)
{
    limitePantalla();

    switch (_state)
    {
    case STILL_RIGHT:
        _width_texture=45;
        _spriteSauron.setScale(sf::Vector2f(1.4,1.4));
        _spriteSauron.setTextureRect(sf::IntRect(340, 13, _width_texture, 123));//x,y,w,h
        break;
    case STILL_LEFT:
        _width_texture=45;
        _spriteSauron.setScale(sf::Vector2f(-1.4,1.4));
        _spriteSauron.setTextureRect(sf::IntRect(340, 13, _width_texture, 123));
        break;

    case APPEAR_LEFT:
        updateAnimation();
        break;
    case APPEAR_RIGHT:
        updateAnimation();
        break;

    case DISAPPEARED:
        _width_texture=45;
        _spriteSauron.setScale(sf::Vector2f(0,0));
        _spriteSauron.setTextureRect(sf::IntRect(340, 13, _width_texture, 123));//x,y,w,h
        break;

    case DISAPPEAR_LEFT:
        updateAnimation();
        break;
    case DISAPPEAR_RIGHT:
        updateAnimation();
        break;

    case ATTACK_RIGHT:
        updateAnimation();
        break;
    case ATTACK_LEFT:
        updateAnimation();

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
    }

}

void Sauron::mobility(const sf::Vector2f& heroPosition,int heroState) {
    arranqueNivel_2 = false;
    distanciaPersonajes_X = _spriteSauron.getPosition().x-heroPosition.x;


    if (distanciaPersonajes_X < 500&&heroPosition.y==1210) {
        arranqueNivel_2 = true;
    }

 if(estaAtacando==true&&volverAPegar==false){
    if(_attackCooldown.getElapsedTime()>=sf::seconds(3.f)){
        volverAPegar=true;
        estaAtacando=false;
    }
 }

    if (arranqueNivel_2 == true&&!dying) {
        if (_isDisappearing==false&&estaAtacando==false&&_Desaparecido==false) {

            if (heroPosition.x > _spriteSauron.getPosition().x + 2) {
                    if((rand() % 30 == 0)&&_disappearCooldown.getElapsedTime()>=sf::seconds(4.f)) {
                    _state=STATES::DISAPPEAR_RIGHT;
                    initVariables();
                    _isDisappearing = true;

                    }
                else{
                    _state==STATES::STILL_RIGHT;
                }
            }


            if (heroPosition.x < _spriteSauron.getPosition().x - 2) {
                if((rand() % 30 == 0)&&_disappearCooldown.getElapsedTime()>=sf::seconds(4.f)) {
                    _state=STATES::DISAPPEAR_LEFT;
                    initVariables();
                    _isDisappearing = true;

                    }
                else{
                    _state==STATES::STILL_LEFT;
                }
            }

        }

        if (_isDisappearing==true&&_Desaparecido==false&&estaAtacando==false) {
            _state=STATES::DISAPPEARED;
            _Desaparecido=true;
            _appearCooldown.restart();
        }

        if (_isDisappearing==true&&_Desaparecido==true&&estaAtacando==false){
                // Asignar el estado
                if (_appearCooldown.getElapsedTime() >= sf::seconds(3.f)) {

                PosicionInicio = heroPosition.x-500;
                float nuevoX = static_cast<float>(PosicionInicio+(rand() % 1000));

                _Desaparecido=false;

                if (nuevoX >= heroPosition.x) {
                     _spriteSauron.setPosition(nuevoX, 1175);
                    _state = STATES::APPEAR_LEFT; // Cambiar a APPEAR_RIGHT
                    initVariables();

                } else {
                    _spriteSauron.setPosition(nuevoX, 1175);
                    _state = STATES::APPEAR_RIGHT; // Cambiar a APPEAR_LEFT
                    initVariables();
                }
                _disappearCooldown.restart();
                _isDisappearing = false;
            }

        }

    if (distanciaPersonajes_X < 250&&distanciaPersonajes_X >= 0&&(_state==STATES::STILL_LEFT||_state==STATES::STILL_RIGHT)&&volverAPegar==true)
    {
        std::cout<<"ATACANDO";
    volverAPegar==false;
    estaAtacando=true;
    _state =STATES::ATTACK_LEFT;

    initVariables();
    _attackCooldown.restart();
    }

    if (distanciaPersonajes_X >= -250&&distanciaPersonajes_X <0&&(_state==STATES::STILL_LEFT||_state==STATES::STILL_RIGHT)&&volverAPegar==true)
    {
        std::cout<<"ATACANDO";
    volverAPegar==false;
    estaAtacando=true;
    _state =STATES::ATTACK_RIGHT;
    initVariables();
    _attackCooldown.restart();

    }
if(heroState==10&&!estaAtacando){
        if (distanciaPersonajes_X >= -450&&distanciaPersonajes_X <0&&!beingAttacked)
    {
    _state =STATES::ATTACKED_RIGHT;
    std::cout << "esta siento atacado right" << std::endl;
    beingAttacked=true;
    initVariables();
    beingAttacked=false;
    }
}

if(heroState==9&&!estaAtacando)
{
        if (distanciaPersonajes_X < 250&&distanciaPersonajes_X >= -100&&!beingAttacked)
    {
    _state =STATES::ATTACKED_LEFT;
    std::cout << "esta siento atacado left" << std::endl;
    beingAttacked=true;
    initVariables();
    beingAttacked=false;
    }
}


    if (heroPosition.x>_spriteSauron.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::N)&&!dying)
    {
    _state =STATES::DEATH_RIGHT;
    dying=true;
    initVariables();
}
        if (heroPosition.x>_spriteSauron.getPosition().x&&sf::Keyboard::isKeyPressed(sf::Keyboard::N)&&!dying)
    {
    _state =STATES::DEATH_LEFT;
    dying=true;
    initVariables();
}

}}


sf::Sprite& Sauron::getDraw()
{
    return _spriteSauron;
}


sf::Vector2f Sauron::getPosition()
{
    return _spriteSauron.getPosition();
}

void Sauron::setPosition(float x, float y)
{
    _spriteSauron.setPosition(x, y);
}


void Sauron::updateAnimation()
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


            if (_state == STATES::APPEAR_RIGHT)
            {
                _state = STATES::STILL_RIGHT;
            }
            else if (_state == STATES::APPEAR_LEFT)
            {
                _state = STATES::STILL_LEFT;
            }
            if (_state == STATES::DISAPPEAR_RIGHT)
            {
                _state = STATES::DISAPPEARED;
            }
            else if (_state == STATES::DISAPPEAR_LEFT)
            {
                _state = STATES::DISAPPEARED;
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
                _state = STATES::DISAPPEARED;
            }
            else if (_state == STATES::DEATH_LEFT)
            {
                _state = STATES::DISAPPEARED;
            }
        }
        // Actualizar el rectángulo de la textura
        _spriteSauron.setTextureRect(_current_frame);

        // Reiniciar el temporizador
        _animationTimer.restart();
    }

}

void Sauron::initVariables()
{
    switch (_state)
    {

    case DISAPPEAR_RIGHT:

        _width_texture = 116;
        _height_texture = 179;
        _end_of_frames_sheet = 1626;
        _spriteSauron.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 164, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case DISAPPEAR_LEFT:

        _width_texture = 116;
        _height_texture = 179;
        _end_of_frames_sheet = 1626;
        _spriteSauron.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 164, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case APPEAR_RIGHT:
        _width_texture = 96;
        _height_texture = 155;
        _end_of_frames_sheet = 1389;
        _spriteSauron.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(450, 350, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case APPEAR_LEFT:
        _width_texture = 96;
        _height_texture = 155;
        _end_of_frames_sheet = 1389;
        _spriteSauron.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(450, 350, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case ATTACK_RIGHT:
        _width_texture = 146;
        _height_texture = 152;
        _end_of_frames_sheet = 1167;
        _spriteSauron.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 894, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case ATTACK_LEFT:

        _width_texture = 146;
        _height_texture = 152;
        _end_of_frames_sheet = 1167;
        _spriteSauron.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(0, 894, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case ATTACKED_RIGHT:

        _width_texture = 97;
        _height_texture = 112;
        _end_of_frames_sheet = 602;
        _spriteSauron.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(19, 599, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;


    case ATTACKED_LEFT:

        _width_texture = 97;
        _height_texture = 112;
        _end_of_frames_sheet = 602;
        _spriteSauron.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(19, 599, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;

    case DEATH_RIGHT:

        _width_texture = 100;
        _height_texture = 143;
        _end_of_frames_sheet = 1467;
        _spriteSauron.setScale(sf::Vector2f(1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(639, 572, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        death=true;
        break;

    case DEATH_LEFT:

        _width_texture = 100;
        _height_texture = 143;
        _end_of_frames_sheet = 1467;
        _spriteSauron.setScale(sf::Vector2f(-1.4, 1.4));
        _first_frame_of_sheet = sf::IntRect(639, 572, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        death=true;
        break;
    }

}
sf::FloatRect Sauron::getBounds() const {
    return _spriteSauron.getGlobalBounds();  // Devuelve el rectángulo de colisión del sprite
}
void Sauron::restarVida(int cantidad) {
    vidas -= cantidad;
    if (vidas < 0)
    {
    vidas = 0;  // No permitir vida negativa
    std::cout << "Vida de Sauron: " << vidas << std::endl;
    if(vidas==0){
        _state= STATES::DEATH_LEFT;
        _state= STATES::DEATH_RIGHT;
        death=true;
    }
    }
}
