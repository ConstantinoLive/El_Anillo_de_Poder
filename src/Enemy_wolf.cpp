#include "Enemy_wolf.h"

Enemy_wolf::Enemy_wolf()
{
    vidaW = 10;
    death = false;
     initTexture();
    // _sprite_wolf.setPosition(pos.x,pos.y);
    //_sprite_wolf.setPosition(4150,485); // posicion inicial  //1998
    //_sprite_wolf.setOrigin({_sprite_wolf.getGlobalBounds().width/2.f,_sprite_wolf.getGlobalBounds().height/2.f});
    //_sprite_wolf.setScale(sf::Vector2f(1.5,1.5));
    _state=STATES::W_STILL_LEFT; //estado inicial
    _jump_force=0; //Fuerza de salto inicial

    op_dir=getRandom();
}

Enemy_wolf::~Enemy_wolf()
{
    //dtor
}

void Enemy_wolf::update()
{
    switch (_state)
    {
    case W_STILL_RIGHT:
        _width_texture=103;
        _sprite_wolf.setScale(sf::Vector2f(1.5,1.5));
        _sprite_wolf.setTextureRect(sf::IntRect(12, 31, _width_texture, 97));//x,y,w,h
        break;
    case W_STILL_LEFT:
        _width_texture=103;
        _sprite_wolf.setScale(sf::Vector2f(-1.5,1.5));
        _sprite_wolf.setTextureRect(sf::IntRect(12, 31, _width_texture, 97));//x,y,w,h
        break;
    case W_WALKING_RIGHT:
        updateAnimation();
        _sprite_wolf.move(5,0);
        break;
    case W_WALKING_LEFT:
        updateAnimation();
        _sprite_wolf.move(-5,0);
        break;
    case W_ATTACK_RIGHT:
        updateAnimation();
        break;
    case W_ATTACK_LEFT:
        updateAnimation();
        break;
    case W_ATTACK_WOLF_RIGHT:
        updateAnimation();
        break;
    case W_ATTACK_WOLF_LEFT:
        updateAnimation();
        break;
    case W_DEATH_RIGHT:
        updateAnimation();
        break;
    case W_DEATH_LEFT:
        updateAnimation();
        break;
    case W_WALKING_RIGHT_JUMPING:
        updateAnimation();
        _jump_force += 4.5;
        _sprite_wolf.move(5,-20);
        break;
    case W_WALKING_LEFT_JUMPING:
        updateAnimation();
        _jump_force += 4.5;
        _sprite_wolf.move(-5,-20);
        break;
        /*case W_INTERSECTION_RIGHT:
            updateAnimation();
            _jump_force += 4.5;
            _sprite_wolf.move(3,-10);
            break;
        case W_INTERSECTION_LEFT:
            updateAnimation();
            _jump_force += 4.5;
            _sprite_wolf.move(-3,-10);
            break;*/
    }
    _jump_force-=5; //fuerza de gravedad. Se ejerse siempre
    _sprite_wolf.move(0,-_jump_force);

}

void Enemy_wolf::mobility(const sf::Vector2f& heroPosition)
{
    _distance=_sprite_wolf.getPosition().x-heroPosition.x;

    int op_attack=getRandom();
    //std::cout<<_jump_timer.getElapsedTime().asSeconds()<<std::endl;
    if(_state==STATES::W_STILL_RIGHT||_state==STATES::W_STILL_LEFT)
    {
        //Avance de derecha a izquierda hasta el encuento
        if(_state==STATES::W_STILL_LEFT&&heroPosition.x<_sprite_wolf.getPosition().x&&_distance>300&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_WALKING_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        //Cambio de direccion
        if(_state==STATES::W_STILL_LEFT&&heroPosition.x>_sprite_wolf.getPosition().x&&_distance<-20&&op_dir%5==0&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_STILL_RIGHT;
        }
        //Mantiene direccion si no es multiplo de 5
        if(_state==STATES::W_STILL_LEFT&&heroPosition.x>_sprite_wolf.getPosition().x&&_distance<-20&&op_dir%5!=0&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_WALKING_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        if(_state==STATES::W_STILL_RIGHT&&heroPosition.x<_sprite_wolf.getPosition().x&&_distance>120&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_STILL_LEFT;
        }
        if(_state==STATES::W_STILL_RIGHT&&heroPosition.x>_sprite_wolf.getPosition().x&&_distance>-300&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_STILL_RIGHT;
        }
        //Cambio de direccion hacia la derecha (multiplo de 5)
        if(_state==STATES::W_STILL_RIGHT&&heroPosition.x>_sprite_wolf.getPosition().x&&op_dir%5==0&&_distance<-200&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_WALKING_RIGHT;
            initVariables();
            _jump_timer.restart();
        }
        //Ataque con espada hacia la izquierda
        if (_state==STATES::W_STILL_LEFT&&_distance<250&&_distance>100&&op_attack%2==0&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_ATTACK_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        //Ataque con lobo hacia la izquierda
        if (_state==STATES::W_STILL_LEFT&&_distance<250&&_distance>100&&op_attack%2==1&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_ATTACK_WOLF_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        //Ataque con lobo hacia la derecha
        if (_state==STATES::W_STILL_RIGHT&&_distance<-50&&_distance>-200&&op_dir%5==0&&heroPosition.y==_sprite_wolf.getPosition().y)
        {
            _state=STATES::W_ATTACK_WOLF_RIGHT;
            initVariables();
            _jump_timer.restart();
        }
        //Lobo sigue caminando cuando personaje salta
        if(_state==STATES::W_STILL_LEFT&&heroPosition.y<_sprite_wolf.getPosition().y&&heroPosition.x<=_sprite_wolf.getPosition().x)
        {
            _state=STATES::W_WALKING_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        if(_state==STATES::W_STILL_RIGHT&&heroPosition.y<_sprite_wolf.getPosition().y&&heroPosition.x>=_sprite_wolf.getPosition().x)
        {
            _state=STATES::W_WALKING_RIGHT;
            initVariables();
            _jump_timer.restart();
        }
        //Lobo sigue caminando cuando salta
        if(_state==STATES::W_STILL_LEFT&&heroPosition.y>_sprite_wolf.getPosition().y&&heroPosition.x<=_sprite_wolf.getPosition().x)
        {
            _state=STATES::W_WALKING_LEFT;
            initVariables();
            _jump_timer.restart();
        }
        if(_state==STATES::W_STILL_RIGHT&&heroPosition.y>_sprite_wolf.getPosition().y&&heroPosition.x>=_sprite_wolf.getPosition().x)
        {
            _state=STATES::W_WALKING_RIGHT;
            initVariables();
            _jump_timer.restart();
        }
        //Salto
        if((_state==STATES::W_STILL_RIGHT&&_jump_timer.getElapsedTime().asSeconds()>=1.5)||
                (_state==STATES::W_STILL_LEFT&&_jump_timer.getElapsedTime().asSeconds()>=1.5&&heroPosition.y<_sprite_wolf.getPosition().y&& heroPosition.x>_sprite_wolf.getPosition().x)||
                (_state==STATES::W_STILL_LEFT&&_jump_timer.getElapsedTime().asSeconds()>=1.5&&heroPosition.y>_sprite_wolf.getPosition().y&& heroPosition.x>_sprite_wolf.getPosition().x))
        {
            _state=STATES::W_WALKING_RIGHT_JUMPING;
            initVariables();
        }
        if((_state==STATES::W_STILL_LEFT&&_jump_timer.getElapsedTime().asSeconds()>=1.5)||
                (_state==STATES::W_STILL_RIGHT&&_jump_timer.getElapsedTime().asSeconds()>=1.5&&heroPosition.y<_sprite_wolf.getPosition().y&& heroPosition.x<_sprite_wolf.getPosition().x)||
                (_state==STATES::W_STILL_RIGHT&&_jump_timer.getElapsedTime().asSeconds()>=1.5&&heroPosition.y>_sprite_wolf.getPosition().y&& heroPosition.x<_sprite_wolf.getPosition().x))
        {
            _state=STATES::W_WALKING_LEFT_JUMPING;
            initVariables();
        }
        if(_state==STATES::W_WALKING_LEFT_JUMPING&&_jump_timer.getElapsedTime().asSeconds()>=2.5)
        {
            _state=STATES::W_STILL_RIGHT;
        }
        if(_state==STATES::W_WALKING_RIGHT_JUMPING&&_jump_timer.getElapsedTime().asSeconds()>=2.5)
        {
            _state=STATES::W_STILL_LEFT;
        }
        //Interseccion
        /* if (_state==STATES::W_WALKING_RIGHT&&heroPosition.x>=_sprite_wolf.getPosition().x)
         {
             _state=STATES::W_INTERSECTION_RIGHT;
             initVariables();
         }
         if (_state==STATES::W_STILL_LEFT&&heroPosition.x<=_sprite_wolf.getPosition().x)
         {
             _state=STATES::W_INTERSECTION_LEFT;
             initVariables();
         }*/
        if(_state==STATES::W_STILL_RIGHT&&sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            _state=STATES::W_DEATH_RIGHT;
            initVariables();
        }
        if(_state==STATES::W_STILL_LEFT&&sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            _state=STATES::W_DEATH_LEFT;
            initVariables();
        }
        if(_state==STATES::W_STILL_RIGHT&&sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            _state=STATES::W_WALKING_RIGHT_JUMPING;
            initVariables();
        }
        if(_state==STATES::W_STILL_LEFT&&sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            _state=STATES::W_WALKING_LEFT_JUMPING;
            initVariables();
        }


    }

}
/*
sf::Sprite& Enemy_wolf::getDraw()
{
    return _sprite_wolf;
}*/
void Enemy_wolf::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite_wolf, states);
}

void Enemy_wolf::updateAnimation()
{
    if (_animationTimer.getElapsedTime().asSeconds() >= 0.11f)
    {
        // Avanzar al siguiente frame
        _current_frame.left += _width_texture;

        // Verificar si llegamos al final de la secuencia de animación
        if (_current_frame.left >= _end_of_frames_sheet)
        {
            // Volver al primer frame de la secuencia
            _current_frame.left = _first_frame_of_sheet.left;

            // Si completamos la animación de disparo, volvemos al estado de quietud
            if (_state == STATES::W_WALKING_RIGHT)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_WALKING_LEFT)
            {
                _state = STATES::W_STILL_LEFT;
            }
            if (_state == STATES::W_ATTACK_RIGHT)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_ATTACK_LEFT)
            {
                _state = STATES::W_STILL_LEFT;
            }
            if (_state == STATES::W_ATTACK_WOLF_RIGHT)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_ATTACK_WOLF_LEFT)
            {
                _state = STATES::W_STILL_LEFT;
            }
            if (_state == STATES::W_DEATH_RIGHT)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_DEATH_LEFT)
            {
                _state = STATES::W_STILL_LEFT;
            }
            /*if (_state == STATES::W_INTERSECTION_RIGHT)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_INTERSECTION_LEFT)
            {
                _state = STATES::W_STILL_LEFT;
            }*/
            if (_state == STATES::W_WALKING_RIGHT_JUMPING)
            {
                _state = STATES::W_STILL_RIGHT;
            }
            else if (_state == STATES::W_WALKING_LEFT_JUMPING)
            {
                _state = STATES::W_STILL_LEFT;
            }
        }
        // Actualizar el rectángulo de la textura
        _sprite_wolf.setTextureRect(_current_frame);

        // Reiniciar el temporizador
        _animationTimer.restart();
    }

}

void Enemy_wolf::initVariables()
{

    switch (_state)
    {
    case W_WALKING_RIGHT:
        _width_texture=138;
        _height_texture = 97;
        _end_of_frames_sheet = 962;
        _sprite_wolf.setScale(sf::Vector2f(1.5,1.5));
        _first_frame_of_sheet = sf::IntRect(sf::IntRect(0,160,_width_texture,_height_texture));
        _current_frame = _first_frame_of_sheet;
        break;
    case W_WALKING_LEFT:
        _width_texture=138;
        _height_texture = 97;
        _end_of_frames_sheet = 962;
        _sprite_wolf.setScale(sf::Vector2f(-1.5,1.5));
        _first_frame_of_sheet = sf::IntRect(sf::IntRect(0,160,_width_texture,_height_texture));
        _current_frame = _first_frame_of_sheet;
        break;
    case W_ATTACK_RIGHT:
        _width_texture = 143.16;  // Ancho de cada frame de la animación de disparo
        _height_texture = 112;   // Altura de cada frame de la animación de disparo
        _end_of_frames_sheet = 715.84; // Posición final de los frames de la hoja de sprites
        _sprite_wolf.setScale(sf::Vector2f(1.5, 1.5));  // Escala para disparar hacia la derecha
        _first_frame_of_sheet = sf::IntRect(0, 400, _width_texture, _height_texture); // Primer frame del disparo hacia la derecha
        _current_frame = _first_frame_of_sheet;  // Inicializar el frame actual
        break;
    case W_ATTACK_LEFT:
        _width_texture = 143.16;
        _height_texture = 112;
        _end_of_frames_sheet = 715.84;
        _sprite_wolf.setScale(sf::Vector2f(-1.5, 1.5));  // Escala negativa para disparar hacia la izquierda
        _first_frame_of_sheet = sf::IntRect(0, 400, _width_texture, _height_texture); // Primer frame del disparo hacia la izquierda
        _current_frame = _first_frame_of_sheet;
        break;
    case W_ATTACK_WOLF_RIGHT:
        _width_texture = 133;  //132.33 Ancho de cada frame de la animación de disparo
        _height_texture = 102;   // Altura de cada frame de la animación de disparo
        _end_of_frames_sheet = 661.67; // Posición final de los frames de la hoja de sprites
        _sprite_wolf.setScale(sf::Vector2f(1.5, 1.5));  // Escala para disparar hacia la derecha
        _first_frame_of_sheet = sf::IntRect(0, 275, _width_texture, _height_texture); // Primer frame del disparo hacia la derecha
        _current_frame = _first_frame_of_sheet;  // Inicializar el frame actual
        break;
    case W_ATTACK_WOLF_LEFT:
        _width_texture = 133;
        _height_texture = 102;
        _end_of_frames_sheet = 661.67;
        _sprite_wolf.setScale(sf::Vector2f(-1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(0, 275, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case W_DEATH_RIGHT:
        _width_texture = 138;
        _height_texture = 106;
        _end_of_frames_sheet = 700;
        _sprite_wolf.setScale(sf::Vector2f(1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(0, 957, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case W_DEATH_LEFT:
        _width_texture = 138;
        _height_texture = 106;
        _end_of_frames_sheet = 700;
        _sprite_wolf.setScale(sf::Vector2f(-1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(0, 957, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case W_WALKING_RIGHT_JUMPING:
        _width_texture = 146;
        _height_texture = 118;
        _end_of_frames_sheet = 709;
        _sprite_wolf.setScale(sf::Vector2f(1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(0, 531, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
    case W_WALKING_LEFT_JUMPING:
        _width_texture = 146;
        _height_texture = 118;
        _end_of_frames_sheet = 709;
        _sprite_wolf.setScale(sf::Vector2f(-1.5, 1.5));
        _first_frame_of_sheet = sf::IntRect(0, 531, _width_texture, _height_texture);
        _current_frame = _first_frame_of_sheet;
        break;
        /*case W_INTERSECTION_RIGHT:
            _width_texture = 145.5;
            _height_texture = 144;
            _end_of_frames_sheet = 727.5;
            _sprite_wolf.setScale(sf::Vector2f(1.5, 1.5));
            _first_frame_of_sheet = sf::IntRect(0, 668, _width_texture, _height_texture);
            _current_frame = _first_frame_of_sheet;
            break;
        case W_INTERSECTION_LEFT:
            _width_texture = 145.5;
            _height_texture = 144;
            _end_of_frames_sheet = 727.5;
            _sprite_wolf.setScale(sf::Vector2f(-1.5, 1.5));
            _first_frame_of_sheet = sf::IntRect(0, 668, _width_texture, _height_texture);
            _current_frame = _first_frame_of_sheet;
            break;*/
    }

}

void Enemy_wolf::floor(float x, float y)
{
    if(_state==STATES::W_STILL_RIGHT||_state==STATES::W_STILL_LEFT||_state==STATES::W_ATTACK_RIGHT||
            _state==STATES::W_ATTACK_LEFT||_state==STATES::W_ATTACK_WOLF_RIGHT||_state==STATES::W_ATTACK_WOLF_LEFT||
            _state==STATES::W_WALKING_RIGHT||_state==STATES::W_WALKING_LEFT||_state==STATES::W_DEATH_RIGHT||
            _state==STATES::W_DEATH_LEFT||_state==STATES::W_WALKING_RIGHT_JUMPING||_state==STATES::W_WALKING_LEFT_JUMPING)//||_state==STATES::W_INTERSECTION_RIGHT||_state==STATES::W_INTERSECTION_LEFT)
    {
        _jump_force=0;
        _sprite_wolf.setPosition(x,y);
    }
}

sf::Vector2f Enemy_wolf::getPosition()
{
    return _sprite_wolf.getPosition();
}

void Enemy_wolf::setPosition(float x, float y)
{
    _sprite_wolf.setPosition(x,y);
}

int Enemy_wolf::getRandom()
{
    static bool seed_initialized = false;
    if (!seed_initialized)
    {
        srand(static_cast<unsigned>(time(nullptr)));
        seed_initialized = true;
    }
    return rand() % 51;
}

float Enemy_wolf::getJump_force()
{
    return _jump_force;
}

sf::FloatRect Enemy_wolf::getBounds()const
{
    return _sprite_wolf.getGlobalBounds();
}
void Enemy_wolf::initTexture()
{
    _texture_wolf.loadFromFile("Resourses/Wolf.png");
    _sprite_wolf.setTexture(_texture_wolf);
    _current_frame=sf::IntRect(_first_frame_of_sheet.left,_first_frame_of_sheet.top,_width_texture,_height_texture);
    _sprite_wolf.setTextureRect(_current_frame);
    _sprite_wolf.setOrigin(_width_texture/2, 0.f);   //desplazo el origen al medio del sprite para que al rotar quede ok


}
/*bool Enemy_wolf::isAlives() const {
    return isAlives; // O la lógica que determines
}*/
void Enemy_wolf::restarVidas(int cantidad) {
    vidaW -= cantidad;
    if (vidaW < 0)
    {
    vidaW = 0;  // No permitir vida negativa
    std::cout << "Vida del Hero: " << vidaW << std::endl;
    if(vidaW==0){
        _state= STATES::W_DEATH_LEFT;
        _state= STATES::W_DEATH_RIGHT;
        //isAlives= false;
        death=true;

    }
    }
}
