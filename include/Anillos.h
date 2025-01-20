#ifndef ANILLOS_H_INCLUDED
#define ANILLOS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Anillos
{
public:
    Anillos();
    virtual ~Anillos();

    enum STATES
    {
        APPEARED_GOLD,
        APPEARED_SILVER,
        DISAPPEARED,
    };

    void limitePantalla(const sf::Vector2f& heroPosition);
    void update(const sf::Vector2f& heroPosition);
    void updateAnimation();
    void mobility(const sf::Vector2f& heroPosition);
    sf::Sprite& getDraw();
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    void initVariables();
    sf::Time _visibleTime; // Tiempo que el anillo está visible
    sf::Time _invisibleTime; // Tiempo que el anillo está invisible
    sf::Clock _timer; // Temporizador para controlar el tiempo
    bool _isVisible;
    int EstadoAnterior;
    float offset;
    sf::FloatRect getBounds() const;
    bool obtenido;
    //void recoger(bool a) {obtenido = a;}
    STATES _state;
    bool isObtenido() const {return obtenido;}


protected:

private:
    sf::Sprite _spriteAnillos;
    sf::Texture _texture_anillos;
    int _xtexture = 0;
    float _width_texture;
    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    int _end_of_frames_sheet;   // Límite de cada sprite
    int _height_texture;
    sf::Clock _attackCooldown; // Temporizador para el ataque
    sf::Time _attackCooldownTime; // Tiempo entre ataques
    // Variable para controlar la animación
    float _animationSpeed; // Velocidad de la animación
};

#endif // ANILLOS_H_INCLUDED
