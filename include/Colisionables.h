#ifndef COLISIONABLES_H
#define COLISIONABLES_H
#include <vector>
#include "Hero_1.h"
#include "Background.h"
#include "Shots.h"
#include "Items.h"
#include "Colision.h"
#include "Mago.h"
#include "Sauron.h"
#include "Anillos.h"
#include "Enemy_wolf.h"
#include "Manager_wolf.h"
#include "Enemy_wolf.h"



class Colisionables
{
    public:
        Colisionables();
        virtual ~Colisionables();
        void itemsColision(Hero_1& Hro, Items*& items);
        void anillosColision(Hero_1& Hro, Anillos& anillos);
        void colisionFlechasConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2, bool& death, bool& dying);
        void colisionHeroConVillanos(Hero_1& Hro, Mago& Villano_1, Sauron& Villano_2, bool& death, bool& dying, bool& attack);  // **Corrige la firma aquí**
        void colisionSauronConHro(Sauron& Villano_2, Hero_1& Hro, bool& death);
        void colisionMagoConHero(Mago& Villano_1, Hero_1& Hro, bool& death);
        void colisionHeroConWolf(Hero_1& Hro,Manager_wolf& _Wolf_manager,bool& attack, bool&dying);
        void colisionFlechasWolf(Hero_1& Hro, Manager_wolf& _Wolf_manager, bool& dying);
        void colisionWolfConHero(Hero_1& Hro,Manager_wolf& _Wolf_manager, bool& dying);
        bool isAlive=false;
        Shots shot;
        int getArrow();
        bool death=false;
        bool attack=false;
        bool estaAtacando=false;
        bool estaDisparando=false;
        bool dying=false;
        //int vidas;

    protected:

    private:
        Items* items;
        Hero_1 Hro;
        Mago Villano_1;
        Shots* shootig;
        Sauron Villano_2;
        Anillos anillos;
        Manager_wolf _Wolf_manager;
        Enemy_wolf enemy_wolf;
};

#endif // COLISIONABLES_H
