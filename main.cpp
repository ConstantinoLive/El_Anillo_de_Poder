#include <SFML/Graphics.hpp>
#include "Game_play.h"
#include "Juego2.h"
#include "Menu.h"


int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  //inicio semilla para rand

        Audio Sound_3c(3);
        Juego2 anillo_de_poder;

        Sound_3c.audioON();

        anillo_de_poder.run();

    return 0;
}
