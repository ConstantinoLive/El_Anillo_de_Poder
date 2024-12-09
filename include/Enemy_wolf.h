#ifndef ENEMY_WOLF_H
#define ENEMY_WOLF_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Hero_1.h"
#include "Platforms.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


class Enemy_wolf: public sf::Drawable
{
public:
    Enemy_wolf();
    virtual ~Enemy_wolf();

enum STATES
    {
        W_STILL_RIGHT,
        W_STILL_LEFT,
        W_WALKING_RIGHT,
        W_WALKING_LEFT,
        W_ATTACK_RIGHT,
        W_ATTACK_LEFT,
        W_ATTACK_WOLF_RIGHT,
        W_ATTACK_WOLF_LEFT,
        W_WALKING_RIGHT_JUMPING,
        W_WALKING_LEFT_JUMPING,
        W_DEATH_RIGHT,
        W_DEATH_LEFT,
    };
   STATES _state;
    void update();
    void updateAnimation();
    void mobility(const sf::Vector2f& heroPosition);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void floor(float x, float y);
    sf::Vector2f getPosition();
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    float getJump_force();
    void initVariables();
    void initAnimation();
    void initTexture();
    int getRandom();
    int vidaW;
    void restarVidas(int cantidad);
    bool death=false;
    bool isDying = false;
    sf::Clock deathTimer;
    int getEnergy();
    void setEnergy(int n);
    void updateDeath();

private:
    sf::Sprite _sprite_wolf;
    sf::Texture _texture_wolf;
    float _jump_force;
    int _xtexture=0;
    float _width_texture;
    float _distance=0;
    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    int _height_texture;
    sf::Clock _jump_timer;
    int random=0;
    int op_dir;
    float _energy=60;


};

#endif // ENEMY_WOLF_H
