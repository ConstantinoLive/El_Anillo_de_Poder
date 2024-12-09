#ifndef MAGO_H
#define MAGO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Colision.h"
#include "Hero_1.h"

class Mago
{
public:
    Mago();
    virtual ~Mago();
    enum STATES
    {
        STILL_RIGHT,
        STILL_LEFT,
        WALKING_RIGHT,
        WALKING_LEFT,
        SHOOTING_RIGHT,
        SHOOTING_LEFT,
        ATTACK_RIGHT,
        ATTACK_LEFT,
        WAITING,
        ATTACKED_RIGHT,
        ATTACKED_LEFT,
        DEATH_RIGHT,//11
        DEATH_LEFT,//12
        DEATH,

    };
    void update(const sf::Vector2f& heroPosition, sf::Time deltaTime);
    void updateMuerte(const sf::Vector2f& heroPosition);
    void updateAnimation();
    void mobility(const sf::Vector2f& heroPosition, int heroState);
    sf::Sprite& getDraw();
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void initVariables();
    void initAnimation();
    void limitePantalla();
    Shots* shooting;
    std::vector<std::unique_ptr<Shots>> _shots_array;
    bool yaDisparo = false;
    bool yaAtaco = false;
    bool HERO_LEFT = true;
    bool arranqueNivel_1=false;
    int TiempoCambioDireccion;
    int CambioDireccion;
    float speed;
    float distanciaPersonajes;
    bool dying=false;
    void restarVida(int cantidad);
    sf::FloatRect getBounds() const;
    int vidasMago;
    bool isAlive=true;
    STATES _state;
    bool estaDisparando;
    int numEstado;
    int Estado;
    void setEstado(int num);
    int getEstado();

protected:

private:
    sf::Sprite _spriteMago;
    sf::Texture _texture_Mago;
    //STATES _state;
    float _jump_force;
    int _xtexture=0;
    float _width_texture;
    bool WALK_LEFT;
    float randomDirection;

    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    int _height_texture;

    sf::Clock _shoot_timer;
    sf::Time _time_shoot;


    sf::Clock _attackCooldown; // Temporizador para el ataque
    sf::Time _attackCooldownTime; // Tiempo entre ataques


    bool estaAtacando;

};

#endif // MAGO_H
