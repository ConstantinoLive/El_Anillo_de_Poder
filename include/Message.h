#ifndef MESSAGE_H
#define MESSAGE_H

#include "Anillos.h"

class Message: public sf::Drawable
{
public:
    Message();
    virtual ~Message();

    void mobility(const sf::Vector2f& RingPosition, bool isSilver);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


protected:

private:
    sf::Text _sprite_msj;
    sf::Font _message;

    sf::Clock _energy_timer;
    sf::Clock _1up_timer;

    void set_1up(bool a);
    void set_energy(bool a);
    bool get_1up() const;
    bool get_energy() const;


    bool _1up=false;
    bool _energy=false;

    //Anillos Ring;

};

#endif // MESSAGE_H
