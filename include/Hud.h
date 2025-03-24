#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>



class Hud: public sf::Drawable
{
public:
    Hud();
    virtual ~Hud();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void mobility(const sf::Vector2f& heroPosition,const sf::Vector2f& camaraPosition);
    void update(const std::string& n, int e, int v, int p, int a);
    void lifeBar_update(int l);
    void lifeBar_initTexture();



private:
    sf::Sprite _sprite_name;
    sf::Texture _texture_name;
    sf::Sprite _sprite_arrow;
    sf::Texture _texture_arrow;
    sf::Sprite _sprite_energyBar;
    sf::Texture _texture_energyBar;
    sf::Sprite _sprite_paper;
    sf::Texture _texture_paper;

    sf::Font _font;
    sf::Text _text_name;
    sf::Text _text_score;
    sf::Text _text_score_n;
    sf::Text _text_lives;
    sf::Text _text_lives_n;
    sf::Text _text_arrow;

    sf::IntRect _current_frame;
    int score;
    int lives;
    int arrow;
    int energy;
    std::string name;



};

#endif // HUD_H
