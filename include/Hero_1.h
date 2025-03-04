#ifndef HERO_1_H
#define HERO_1_H
#include <SFML/Graphics.hpp>
#include "Shots.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Colision.h"


class Hero_1
{
public:
    Hero_1();
    //virtual ~Hero_1();
    enum STATES
    {
        STILL_RIGHT,
        STILL_LEFT,
        WALKING_RIGHT,
        WALKING_LEFT,
        JUMPING,
        WALKING_RIGHT_JUMPING,
        WALKING_LEFT_JUMPING,
        SHOOTING_RIGHT,
        SHOOTING_LEFT,
        ATTACK_RIGHT,
        ATTACK_LEFT,
        DEATH

    };
    STATES _state;
    void update();
    void updateAnimation();
    void mobility();
    sf::Sprite& getDraw();
    void floor(float x, float y);
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void initVariables();
    void initAnimation();
    float getJump_force();
    Shots* shootig;
    std::vector<std::unique_ptr<Shots>> _shots_array;
    bool isDPressed = false;
    bool yaDisparo = false;
    sf::FloatRect getBounds() const;
    bool isAlive=true;

    void setEstado(int numE);
    int getEstado();
    int getVida(){return vida;};
    void SumarVida(int v){vida+=v;};
    void setVida(int v){vida=v;};
    int getEnergia(){return energia;};
    void setEnergia(int e){energia=e;};
    void RestarEnergia(int e){energia-=e;};
    void SumarEnergia(int e){energia+=e;};
    bool attack=false;
    void restarVidas(int cantidad);
    void actualizarEstado();
    void updateReborn();
    sf::Vector2f getLastPosition(){return lastPosition;};
    void setLastPosition();
    bool isFallen=false;
    bool getd_r(){return d_r;};



protected:

private:
    sf::Sprite _sprite_hero;
    sf::Texture _texture_hero;

    float _jump_force;
    int _xtexture=0;
    float _width_texture;
    int vida;
    int energia;
    int numEstado;
    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    sf::Sprite _sprite_shot;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    int _height_texture;
    sf::Clock _shoot_timer;
    sf::Time _time_shoot;
    sf::Clock deathTimer;
    bool d_r=false;
    sf::Vector2f lastPosition;

};

#endif // HERO_1_H
