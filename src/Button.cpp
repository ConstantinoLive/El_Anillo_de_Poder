#include "Button.h"

Button::Button(const std::string& t, sf::Vector2f p, sf::Vector2f s)
{
    _texture_button.loadFromFile("Resourses/button.png");
    _texture_button.setSmooth(true);
    _sprite_button.setTexture(_texture_button);
    _sprite_button.setPosition(p);
    _sprite_button.setScale(s);


    _font_button.loadFromFile("Resourses/Font/CELTG___.TTF");
    if (!_font_button.loadFromFile("Resourses/Font/CELTG___.TTF"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _text_button.setFont(_font_button);
    _text_button.setString(t);
    _text_button.setCharacterSize(20);
    _text_button.setFillColor(sf::Color(245,178,94));
    //_text_button.setPosition({p.x+10,p.y+3});

    sf::FloatRect textBounds = _text_button.getLocalBounds();
    _text_button.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    _text_button.setPosition(p.x + _sprite_button.getGlobalBounds().width / 2.0f, p.y + _sprite_button.getGlobalBounds().height / 2.0f);


}

Button::~Button()
{
    //dtor
}

void Button::setScale(sf::Vector2f s)
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite_button, states);
    target.draw(_text_button, states);
}

sf::FloatRect Button::getBounds() const
{
    return _sprite_button.getGlobalBounds();
}
