#include "Colision.h"
#include <SFML/Graphics.hpp>


//PARA QUE SE DE CUANTA CUANDO CHOCA CONTRA UN OBJETO
bool Colision::isColision(Colision& obj)const{
        return getBounds().intersects(obj.getBounds());
}
/*Colision::~Colision()
{
    //dtor
}*/



