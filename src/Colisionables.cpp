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

void Colisionables::itemsColision(Hero_1& Hro, Items*& items) {
    static int j = 0;

    if (!items) {
        //Items* items = new ConcreteItem();
        std::cerr << "Error: items no est� inicializado." << std::endl;
        return;
    }

    if (j >= items->isObtenido.size()) {
        std::cerr << "�ndice 'j' fuera de los l�mites de 'isObtenido'." << std::endl;
        return;
    }

    if (j == 0 && Hro.getPosition().y <= 500) {
        items->update(0);
    }

    if (j == 0 && Hro.getPosition().y > 600) {
        j = 4;
        items->update(4);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (Hro.getBounds().intersects(items->getBounds())) {
            if (!items->isObtenido[j]) {
                std::cout << "Se sumaron 10 flechas" << std::endl;
                items->isObtenido[j] = true; // Marcar como obtenido
            }
            if (items->isObtenido[j]) {
                j++;
                items->update(j); // Actualizar estado del item
                Hro.shootig->setArrow(10); // Agregar flechas
            }
        }
    }
}
void Colisionables::anillosColision(Hero_1& Hro, Anillos& anillos){
    if(anillos._state==Anillos::STATES::APPEARED_SILVER){
        if (Hro.getBounds().intersects(anillos.getBounds())&&!anillos.isObtenido()) {
            anillos.obtenido = true;
            std::cout << "Se obtubo un anillo dorado" << std::endl;
            Hro.porcentajeVida+=20;
            std::cout<<"PORCENTAJE VIDA % " <<Hro.vida << std::endl;


        }
    }
    if(anillos._state==Anillos::STATES::APPEARED_GOLD){
        if (Hro.getBounds().intersects(anillos.getBounds())&&!anillos.isObtenido()) {
            anillos.obtenido = true;
            std::cout << "Se obtubo un anillo plateado" << std::endl;
            Hro.energia+=20;
            std::cout<<"Energia % " <<Hro.energia << std::endl;


        }
    }

}
void Colisionables::colisionFlechasConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2,bool& death, bool& dying){
    //COLISION DE LAS FLECHAS

        for (auto& shot : Hro._shots_array) {
            if (shot->isAlive && shot->getBounds().intersects(Villano_2.getBounds())) {
                std::cout << "�Colision detectada!" << std::endl;

                Hro.puntos+=500;
                std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                Hro.energia-=2;
                Hro.actualizarEstado();
                //std::cout<<"Energia % " <<Hro.energia << std::endl;
                Villano_2.restarVida(2);
                std::cout << "Vida de Sauron: " << Villano_2.vidas << std::endl;


                shot->setAlive(false);

                    if (Villano_2.vidas <= 0 && !death) {
                        death = true;
                        Villano_2.isAlive = false;
                        std::cout << "Sauron ha muerto!" << std::endl;
                    }

            }
        }

        for (auto& shot : Hro._shots_array) {
            if (shot->isAlive && shot->getBounds().intersects(Villano_1.getBounds())) {
                std::cout << "�Colision detectada!" << std::endl;

                Hro.puntos+=500;
                std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                Hro.energia-=2;
               // std::cout<<"Energia % " <<Hro.energia << std::endl;
                Hro.actualizarEstado();
                Villano_1.restarVida(2);
                std::cout << "Vida de Mago: " << Villano_1.vidasMago << std::endl;

                shot->setAlive(false);

                    if (Villano_1.vidasMago <= 0 && !dying) {
                        dying=true;
                        Villano_1.isAlive = false;
                        std::cout << "Mago ha muerto!" << std::endl;
                    }

            }
        }

     Hro.actualizarEstado();
}
void Colisionables::colisionHeroConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2, bool& death, bool& dying, bool& attack){
    //GOLPE CUERPO A CUERPO DEL HERO A SAURON

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(Hro._state==Hero_1::STATES::ATTACK_RIGHT||Hro._state==Hero_1::STATES::ATTACK_LEFT){
                if (Hro.getBounds().intersects(Villano_2.getBounds())) {
                    std::cout << "�Golpe a Sauron!" << std::endl;

                    attack = true;
                    Hro.energia -= 5; // Consumir energ�a
                    Hro.actualizarEstado();
                    Villano_2.restarVida(2);
                    std::cout << "Energ�a del h�roe: " << Hro.energia << "%" << std::endl;
                    std::cout << "Vida de Sauron: " << Villano_2.vidas << std::endl;

                    if (Villano_2.vidas <= 0 && !dying) {
                        dying = true;
                        Villano_2.isAlive = false;
                        std::cout << "Sauron ha muerto!" << std::endl;
                    }
                }
            }
        }
        //GOLPE CUERPO A CUERPO DEL HERO AL MAGO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(Hro._state==Hero_1::STATES::ATTACK_RIGHT||Hro._state==Hero_1::STATES::ATTACK_LEFT){
                if (Hro.getBounds().intersects(Villano_1.getBounds())) {
                    std::cout << "�Golpe al Mago!" << std::endl;

                    attack = true;

                    Hro.energia-=5;
                    Hro.actualizarEstado();
                    std::cout<<"Energia %: " <<Hro.energia << std::endl;
                    Hro.puntos+=1000;
                    std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                    Villano_1.restarVida(2);
                    std::cout << "Vida de Mago: " << Villano_1.vidasMago << std::endl;
                    std::cout << "Energ�a del h�roe: " << Hro.energia << "%" << std::endl;


                    if (Villano_1.vidasMago <= 0 && !dying) {
                        dying=true;
                        Villano_1.isAlive = false;
                        std::cout << "Mago ha muerto!" << std::endl;
                    }
                }
            }
        }

     Hro.actualizarEstado();
}

void Colisionables::colisionSauronConHro(Sauron& Villano_2, Hero_1& Hro, bool& death){
    //GOLPE DE SAURON AL HERO
    if (!Hro.isAlive) {
        return;
    }
    if (Villano_2._state) {
        if (!estaAtacando) {
            if (Villano_2.getBounds().intersects(Hro.getBounds())) {
                if (Hro.isAlive) {
                    std::cout << "Sauron golpeo al heroe. Pierdes porcentaje de vida." << std::endl;
                    Hro.porcentajeVida -= 5; // Reducir porcentaje de vida
                    Hro.actualizarEstado();
                    std::cout << "Porcentaje de vida del h�roe: " << Hro.porcentajeVida << "%" << std::endl;
                }
            }
        }
    }
}
void Colisionables::colisionMagoConHero(Mago& Villano_1, Hero_1& Hro, bool& death){
   if (!Hro.isAlive) {
        return;
    }
    if (Villano_1._state) {
        if (Villano_1.getBounds().intersects(Hro.getBounds())) {
            if (Villano_1._state == Mago::STATES::ATTACK_RIGHT ||Villano_1. _state == Mago::STATES::ATTACK_LEFT) {
                if (Hro.isAlive) {
                    std::cout << "Sauron golpeo al heroe. Pierdes 1 vida." << std::endl;
                    Hro.porcentajeVida-=5;
                    Hro.actualizarEstado();
                    std::cout << "VIDAS HRO: " << Hro.vida << std::endl;
                }
            }
        }
    }
    for (auto& shot : Villano_1._shots_array) {
        if (shot->isAlive && shot->getBounds().intersects(Hro.getBounds())) {
            std::cout << "�Colision detectada!" << std::endl;

            if (Hro.isAlive) {
                    std::cout << "Sauron golpeo al heroe. Pierdes 1 vida." << std::endl;
                    Hro.porcentajeVida-=5;
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
                    if (Hro.getBounds().intersects(Enemy_wolf->getBounds()))
                    {
                        std::cout << "�Golpe al Wolf!" << std::endl;

                        attack = true;
                        Hro.energia-=5;
                        Hro.actualizarEstado();
                        std::cout<<"Energia %: " <<Hro.energia << std::endl;
                        Hro.puntos+=100;
                        std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                        Enemy_wolf->restarVidas(5);
                        std::cout << "Vida de Wolf: " << Enemy_wolf->vidaW << std::endl;

                        if (Enemy_wolf->vidaW <= 0 && !dying)
                        {
                            dying = true;
                            std::cout << "Wolf ha muerto!" << std::endl;
                        }
                    }
                }
            }
        }

     Hro.actualizarEstado();

}
void Colisionables::colisionFlechasWolf(Hero_1& Hro, Manager_wolf& _Wolf_manager, bool& dying){
    //COLISION DE LAS FLECHAS

         for (auto& Enemy_wolf : _Wolf_manager._array_wolf){
            for (auto& shot : Hro._shots_array) {
                if (shot->isAlive && shot->getBounds().intersects(Enemy_wolf->getBounds())) {
                    std::cout << "�Colision detectada!" << std::endl;


                    Hro.energia-=2;
                    Hro.actualizarEstado();
                    //std::cout<<"Energia % " <<Hro.energia << std::endl;
                    Hro.puntos+=100;
                    std::cout<<"PUNTOS: " <<Hro.puntos << std::endl;
                    Enemy_wolf->restarVidas(5);
                    std::cout << "Vida de Wolf: " << Enemy_wolf->vidaW << std::endl;


                    shot->setAlive(false);

                    if (Enemy_wolf->vidaW <= 0 && !death) {
                        death = true;
                        std::cout << "Wolf ha muerto!" << std::endl;
                    }

                }
            }
        }
     Hro.actualizarEstado();

}
void Colisionables::colisionWolfConHero(Hero_1& Hro,Manager_wolf& _Wolf_manager, bool& dying){
    if (!Hro.isAlive) {
        return; // El h�roe esta muerto, no aplicar m�s da�o
    }
    for (auto& Enemy_wolf : _Wolf_manager._array_wolf){
        if (Enemy_wolf->getBounds().intersects(Hro.getBounds())) {
            if (Enemy_wolf->_state == Enemy_wolf::STATES::W_ATTACK_WOLF_RIGHT ||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_WOLF_RIGHT||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_RIGHT||Enemy_wolf-> _state == Enemy_wolf::STATES::W_ATTACK_LEFT) {

                if (Hro.isAlive) {
                    std::cout << "Lobo ataco al heroe. Pierdes porcentaje de vida." << std::endl;
                    Hro.porcentajeVida -= 1; // Reducir porcentaje de vida
                    Hro.actualizarEstado();
                    std::cout << "Porcentaje de vida del h�roe: " << Hro.porcentajeVida << "%" << std::endl;
                }
            }
        }
    }
}
Colisionables::~Colisionables() {

}
Colisionables::Colisionables()
{

}


