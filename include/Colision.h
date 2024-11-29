#pragma once
#include <SFML/Graphics.hpp>
/*#include "Anillos.h"
#include "Hero_1.h"
#include "Items.h"
#include "Colisionables.h"*/

class Colision
{
    public:
        virtual sf::FloatRect getBounds() const=0;
        virtual ~Colision() {};
        bool isColision(Colision& col)const;


    protected:

    private:
};


