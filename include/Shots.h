#ifndef SHOTS_H
#define SHOTS_H
#include <SFML/Graphics.hpp>

enum STYLE
    {
        ARROW,
        SPELL
    };

class Shots
{
public:
    Shots();
    Shots(STYLE style,sf::Vector2f pos, bool right);

    virtual ~Shots();

    sf::Sprite _spriteSauron;
    void update();
    void updateAnimation();
    void mobility();
    int getDamage();
    sf::Sprite& getDraw();
    sf::Vector2f getPosition();
    void initVariables();
    void initAnimation();
    void initTexture();
    STYLE getStyle();
    STYLE setStyle();
    int getArrow();
    void setArrow(int a);
    sf::FloatRect getBounds() const;
    bool isAlive;
    bool getAlive() const { return isAlive; }
    void setAlive(bool alive) { isAlive = alive; }


protected:

private:
    sf::Sprite _sprite_shot;
    sf::Texture _texture_shot;
    STYLE _style;
    float _width_texture;
    bool _right;
    sf::Vector2f _position;
    int _damage_shoot;
    int _cant_arrow=0;
    sf::Clock _animationTimer;
    sf::IntRect _current_frame;
    sf::IntRect _first_frame_of_sheet;      //me sirve para saber las coordenadas donde arranca el frame de cada tipo de disparo
    int _end_of_frames_sheet;               //me sirve para saber hasta donde va cada sprite en los distintos tipos de disparos
    int _height_texture;


};

#endif // SHOTS_H

