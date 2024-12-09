#ifndef SAURON_H_INCLUDED
#define SAURON_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Colision.h"
#include "Hero_1.h"

class Sauron
{
public:
    Sauron();
    virtual ~Sauron();
    enum STATES
    {
        STILL_RIGHT,
        STILL_LEFT,
        APPEAR_RIGHT,
        APPEAR_LEFT,
        DISAPPEARED,
        DISAPPEAR_RIGHT,
        DISAPPEAR_LEFT,
        ATTACK_RIGHT,
        ATTACK_LEFT,
        ATTACKED_RIGHT,
        ATTACKED_LEFT,
        DEATH_RIGHT,//11
        DEATH_LEFT,//12
    };

    void update(const sf::Vector2f& heroPosition, sf::Time deltaTime);
    void updateAnimation();
    void updateMuerte(const sf::Vector2f& heroPosition);
    void mobility(const sf::Vector2f& heroPosition,int heroState);
    sf::Sprite& getDraw();
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void initVariables();
    void initAnimation();
    void limitePantalla();
    bool HERO_LEFT = true;
    bool estaAtacando;
    bool arranqueNivel_2 = false;
    float distanciaPersonajes_X;
    float distanciaPersonajes_Y;
    float PosicionInicio;
    float PosicionLimite;
    float nuevoX;
    bool beingAttacked;
    bool dying;
    bool death=false;
    void restarVida(int cantidad);
    sf::FloatRect getBounds() const;
    int vidas;
    bool isAlive=true;
    STATES _state;
    void _setVidas(int n);
    int _getVidas();
    int n;
    int numEstado;
    int Estado;
    void setEstado(int numEstado);
    int getEstado();


protected:

private:
    sf::Sprite _spriteSauron;
    sf::Texture _texture_Sauron;

    //STATES _state;
    float _jump_force;
    int _xtexture=0;
    float _width_texture;
    bool WALK_LEFT;

    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    int _height_texture;


    sf::Clock _attackCooldown;
    sf::Clock _disappearCooldown;

    sf::Clock _appearCooldown;
    bool _isDisappearing;
    bool _Desaparecido;
    bool volverAPegar;
    float tiempoDesaparecer;




};

#endif // SAURON_H_INCLUDED
