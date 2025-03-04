#include "Button.h"

Button::Button(const std::string& t, sf::Vector2f p, sf::Vector2f s)
{
    _scale= {s};
    _texture_button.loadFromFile("Resourses/button.png");
    _texture_button.setSmooth(true);
    _sprite_button.setTexture(_texture_button);
    _sprite_button.setPosition(p);
    _sprite_button.setScale(s);
    _sprite_button.setOrigin(_texture_button.getSize().x / 2.0f,_texture_button.getSize().y / 2.0f);


    _font_button.loadFromFile("Resourses/Font/CELTG___.TTF");
    if (!_font_button.loadFromFile("Resourses/Font/CELTG___.TTF"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _text_button.setFont(_font_button);
    _text_button.setString(t);
    _text_button.setCharacterSize(20);
    _text_button.setFillColor(sf::Color(245,178,94));

    sf::FloatRect textBounds = _text_button.getLocalBounds();
    _text_button.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    _text_button.setPosition(_sprite_button.getPosition());

}

Button::~Button()
{
    //dtor
}

void Button::activeButton()
{
    _sprite_button.setScale(_scale.x+0.03,_scale.y+0.03);
    _text_button.setCharacterSize(23);
    _text_button.setPosition(_sprite_button.getPosition());

}

void Button::desactiveButton()
{
    _sprite_button.setScale({_scale});
    _text_button.setCharacterSize(20);
    _text_button.setPosition(_sprite_button.getPosition());
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
