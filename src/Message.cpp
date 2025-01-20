#include "Message.h"

Message::Message()
{
    _message.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");
    _sprite_msj.setFont(_message);
    _sprite_msj.setCharacterSize(20);
    _sprite_msj.setFillColor(sf::Color(223,223,223,100));

}

Message::~Message()
{
    //dtor
}

void Message::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    if (_1up || _energy)
    {
        target.draw(_sprite_msj, states);
    }

}

void Message::mobility(const sf::Vector2f& RingPosition,bool isSilver)
{
    if (isSilver)
    {
        set_1up(true);
        _sprite_msj.setString("1 Up");
        _sprite_msj.setPosition(RingPosition);
        _1up_timer.restart(); // Reinicia el temporizador

    }
    else
    {
        set_energy(true);
        _sprite_msj.setString("+20 Energia");
        _sprite_msj.setPosition(RingPosition);
        _energy_timer.restart();  // Reinicia el temporizador

    }
}

void Message::update()
{
    if (get_energy())
    {
        //_energy_message.move(0, -3);
        _sprite_msj.move(0, -3);
        if (_energy_timer.getElapsedTime().asSeconds() > 1.0f) // Desaparece tras 2 segundos
        {
            set_energy(false);
            set_1up(false);
        }
    }

    if (get_1up())
    {
       // _1up_message.move(0, -3);
       _sprite_msj.move(0, -3);
        if (_1up_timer.getElapsedTime().asSeconds() > 1.0f) // Desaparece tras 2 segundos
        {
            set_1up(false);
            set_energy(false);
        }
    }
}

bool Message::get_1up() const
{
    return _1up;
}

bool Message::get_energy() const
{
    return _energy;
}

void Message::set_1up(bool a)
{
    _1up=a;
}

void Message::set_energy(bool a)
{
    _energy=a;
}
