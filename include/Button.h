#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class Button: public sf::Drawable
{
public:
    Button(const std::string& t, sf::Vector2f p, sf::Vector2f s);
    Button();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void activeButton();
    void desactiveButton();
    sf::FloatRect getBounds() const;

    virtual ~Button();

protected:

private:
    sf::Sprite _sprite_button;
    sf::Texture _texture_button;
    sf::Text _text_button;
    sf::Font _font_button;

    sf::Vector2f _scale;
   // int click=255;

};

#endif // BUTTON_H
