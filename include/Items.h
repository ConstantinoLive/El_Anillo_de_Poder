#ifndef ITEMS_H
#define ITEMS_H
#include <SFML/Graphics.hpp>
#include "Colision.h"


class Items: public sf::Drawable, public Colision{


    public:
        bool obtenido = false;
    sf::Sprite _sprite_items;
    sf::Texture _texture_items;

    // Métodos públicos
    Items();  // Constructor
    //void update(int n);
    void respawn(int n);
    sf::Sprite getDraw() const;
    sf::FloatRect getBounds() const override;

    void recoger() {
        obtenido = true;
    }

    std::vector<bool> isObtenido={false,false,false, false};
    size_t current_position;
    std::vector<sf::Vector2f> posiciones;
    int i;
    int j;
    virtual void update(int n) = 0;  // Función pura virtual




private:

};

#endif // ITEMS_H
