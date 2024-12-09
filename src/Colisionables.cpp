#include "Colisionables.h"
#include <vector>
#include "Hero_1.h"
#include "Background.h"
#include "Shots.h"
#include "Items.h"
#include "Colision.h"
#include "Mago.h"
#include "Sauron.h"
#include "Anillos.h"
#include "Manager_wolf.h"
#include "Enemy_wolf.h"


void Colisionables::anillosColision(Hero_1& Hro, Anillos& anillos)
{
    if(anillos._state==Anillos::STATES::APPEARED_SILVER)
    {
        if (Hro.getBounds().intersects(anillos.getBounds())&&!anillos.isObtenido()&&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            anillos.obtenido = true;
            std::cout << "Se obtubo un anillo dorado" << std::endl;
            Hro.porcentajeVida+=20;
        }
    }

    if(anillos._state==Anillos::STATES::APPEARED_GOLD)
    {
        if (Hro.getBounds().intersects(anillos.getBounds())&&!anillos.isObtenido()&&sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            anillos.obtenido = true;
            std::cout << "Se obtubo un anillo plateado" << std::endl;
            Hro.vida+=1;
        }
    }
    if(anillos._state==Anillos::STATES::DISAPPEARED)
    {
        anillos.obtenido =false;
    }
}
void Colisionables::colisionFlechasConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2,bool& death, bool& dying)
{
    //COLISION DE LAS FLECHAS

    for (auto& shot : Hro._shots_array)
    {
        if (shot->isAlive && shot->getBounds().intersects(Villano_2.getBounds()))
        {
            std::cout << "¡Colision detectada!" << std::endl;

            Hro.actualizarEstado();
            //std::cout<<"Energia % " <<Hro.energia << std::endl;
            Villano_2.restarVida(2);
            std::cout << "Vida de Sauron: " << Villano_2.vidas << std::endl;


            shot->setAlive(false);

            if (Villano_2.vidas <= 0 && !death)
            {
                death = true;
                Villano_2.isAlive = false;
                std::cout << "Sauron ha muerto!" << std::endl;
            }

        }
    }

    for (auto& shot : Hro._shots_array)
    {
        if (shot->isAlive && shot->getBounds().intersects(Villano_1.getBounds()))
        {
            std::cout << "¡Colision detectada!" << std::endl;

            Hro.actualizarEstado();
            Villano_1.restarVida(2);
            std::cout << "Vida de Mago: " << Villano_1.vidasMago << std::endl;

            shot->setAlive(false);

            if (Villano_1.vidasMago <= 0)
            {
                dying=true;
                Villano_1.isAlive = false;
                std::cout << "Mago ha muerto!" << std::endl;
            }

        }
    }

    Hro.actualizarEstado();
}
void Colisionables::colisionHeroConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2, bool& death, bool& dying, bool& attack)
{
    //GOLPE CUERPO A CUERPO DEL HERO A SAURON

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(Hro._state==Hero_1::STATES::ATTACK_RIGHT||Hro._state==Hero_1::STATES::ATTACK_LEFT)
        {
            if (Hro.getBounds().intersects(Villano_2.getBounds()))
            {
                std::cout << "¡Golpe a Sauron!" << std::endl;

                attack = true;
                Hro.actualizarEstado();
                Villano_2.restarVida(2);
                std::cout << "Vida de Sauron: " << Villano_2.vidas << std::endl;

                if (Villano_2.vidas <= 0 && !dying)
                {
                    dying = true;
                    Villano_2.isAlive = false;
                    std::cout << "Sauron ha muerto!" << std::endl;
                }
            }
        }
    }
    //GOLPE CUERPO A CUERPO DEL HERO AL MAGO
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(Hro._state==Hero_1::STATES::ATTACK_RIGHT||Hro._state==Hero_1::STATES::ATTACK_LEFT)
        {
            if (Hro.getBounds().intersects(Villano_1.getBounds()))
            {
                std::cout << "¡Golpe al Mago!" << std::endl;

                attack = true;

                Villano_1.restarVida(2);
                std::cout << "Vida de Mago: " << Villano_1.vidasMago << std::endl;


                if (Villano_1.vidasMago <= 0 && !dying)
                {
                    dying=true;
                    Villano_1.isAlive = false;
                    std::cout << "Mago ha muerto!" << std::endl;
                }
            }
        }
    }

    Hro.actualizarEstado();
}

void Colisionables::colisionSauronConHro(Sauron& Villano_2, Hero_1& Hro, bool& death)
{
    //GOLPE DE SAURON AL HERO
    if (!Hro.isAlive)
    {
        return;
    }
    if (Villano_2.getEstado()==7||Villano_2.getEstado()==8)
    {
        if (!Villano_2.estaAtacando)
        {
            if (Villano_2.getBounds().intersects(Hro.getBounds()))
            {
                if (Hro.isAlive)
                {
                    std::cout << "Sauron golpeo al heroe. Pierdes porcentaje de vida." << std::endl;
                    Hro.porcentajeVida -= 2; // Reducir porcentaje de vida
                    Hro.actualizarEstado();
                    std::cout << "Porcentaje de vida del héroe: " << Hro.porcentajeVida << "%" << std::endl;
                }
            }
        }
    }
}
void Colisionables::colisionMagoConHero(Mago& Villano_1, Hero_1& Hro, bool& death)
{
    if (!Hro.isAlive)
    {
        return;
    }
    if (Villano_1._state)
    {
        if (Villano_1.getBounds().intersects(Hro.getBounds()))
        {
            if (Villano_1.getEstado()==6 ||Villano_1.getEstado()==7)
            {
                if (Hro.isAlive)
                {
                    std::cout << "Mago golpeo al heroe. Pierdes 1 vida." << std::endl;
                    Hro.porcentajeVida-=2;
                    Hro.actualizarEstado();
                    std::cout << "VIDAS HRO: " << Hro.vida << std::endl;
                }
            }
        }
    }
    for (auto& shot : Villano_1._shots_array)
    {
        if (shot->isAlive && shot->getBounds().intersects(Hro.getBounds()))
        {
            std::cout << "¡Colision detectada!" << std::endl;

            if (Hro.isAlive)
            {
                std::cout << "Mago golpeo al heroe. Pierdes 1 vida." << std::endl;
                Hro.porcentajeVida-=10;
                Hro.actualizarEstado();
                std::cout << "VIDAS HRO: " << Hro.vida << std::endl;
            }

            shot->setAlive(false);



        }
    }

}


void Colisionables::colisionHeroConWolf(Hero_1& Hro, Manager_wolf& _Wolf_manager, bool& attack, bool& dying)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (Hro._state == Hero_1::STATES::ATTACK_RIGHT || Hro._state == Hero_1::STATES::ATTACK_LEFT)
        {

            for (auto& Enemy_wolf : _Wolf_manager._array_wolf)
            {
                if (Hro.getBounds().intersects(Enemy_wolf->getBounds())&&(Hro._state == Hero_1::STATES::ATTACK_LEFT||Hro._state == Hero_1::STATES::ATTACK_RIGHT))
                {
                    Enemy_wolf->setEnergy(20);
                    std::cout<<"Energia: " <<Enemy_wolf->getEnergy() << std::endl;
                }
            }
        }
    }

    Hro.actualizarEstado();

}
void Colisionables::colisionFlechasWolf(Hero_1& Hro, Manager_wolf& _Wolf_manager, bool& dying)
{
    //COLISION DE LAS FLECHAS

    for (auto& Enemy_wolf : _Wolf_manager._array_wolf)
    {
        for (auto& shot : Hro._shots_array)
        {
            if (shot->isAlive && shot->getBounds().intersects(Enemy_wolf->getBounds()))
            {
                std::cout << "¡Colision detectada!" << std::endl;


                Hro.actualizarEstado();
                //std::cout<<"Energia % " <<Hro.energia << std::endl;
//                    Hro.puntos+=100;
//                    std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                Enemy_wolf->restarVidas(5);
                std::cout << "Vida de Wolf: " << Enemy_wolf->vidaW << std::endl;


                shot->setAlive(false);

                if (Enemy_wolf->vidaW <= 0 && !death)
                {
                    death = true;
                    std::cout << "Wolf ha muerto!" << std::endl;
                }

            }
        }
    }
    Hro.actualizarEstado();

}
void Colisionables::colisionWolfConHero(Hero_1& Hro,Manager_wolf& _Wolf_manager, bool& dying)
{
    if (!Hro.isAlive)
    {
        return; // El héroe esta muerto, no aplicar más daño
    }
    for (auto& Enemy_wolf : _Wolf_manager._array_wolf)
    {
        if (Enemy_wolf->getBounds().intersects(Hro.getBounds()))
        {
            if (Enemy_wolf->_state == Enemy_wolf::STATES::W_ATTACK_WOLF_RIGHT ||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_WOLF_RIGHT||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_RIGHT||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_LEFT)
            {

                if (Hro.isAlive)
                {
                    std::cout << "Lobo ataco al heroe. Pierdes porcentaje de vida." << std::endl;
                    Hro.porcentajeVida -=1; // Reducir porcentaje de vida
                    Hro.actualizarEstado();
                    std::cout << "Porcentaje de vida del héroe: " << Hro.porcentajeVida << "%" << std::endl;
                }
            }
        }
    }
}
Colisionables::~Colisionables()
{

}
Colisionables::Colisionables()
{

}


