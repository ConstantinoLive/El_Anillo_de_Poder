#ifndef GAME_PLAY_H
#define GAME_PLAY_H
#include <SFML/Graphics.hpp>
#include "Hero_1.h"
#include "Mago.h"
#include "Sauron.h"
#include "Anillos.h"
#include "Background.h"
#include "Shots.h"
#include "Platforms.h"
#include "Platforms_rectangle_shape.h"
#include "Player.h"
#include "Manager_wolf.h"
#include "Items.h"
#include "Colision.h"
#include "Colisionables.h"


class Game_play
{
public:
    Game_play(sf::RenderWindow& window,Player& player);
    virtual ~Game_play();
    void draw(sf::RenderWindow& window);
    void cmd();
    void update(sf::RenderTarget& window);
    sf::Vector2f get_camera_position();
    bool arranqueMago;
    void check_collision_platform();
    void updateEnemySupGeneration();
    void floor_definition();
    bool isAlive=false;
    Shots shot;
    int getArrow();
    bool death=false;
    bool attack=false;
    bool estaAtacando=false;
    bool estaDisparando=false;
    int getPuntaje()
    {
        return puntaje;
    }
    void setPuntaje(int n)
    {
        puntaje=puntaje+n;
    }

    bool getGameOver()
    {
        return _game_over;
    }

    std::string getNombrePlayer()
    {
        return _namePlayer;
    }
    void setNombrePlayer(std::string nombre);
    bool getWinner();

    /*int puntaje = 0;
    int vidas;
    int enemigos=0;
    int enemigos_eliminados=0;
    bool _winner = false;
    bool dying=false;
    int i;
    int j;*/


private:
    enum LEVEL
    {
        LEVEL_I,
        LEVEL_II
    };
    LEVEL _current_level;
    enum STATES_GAME_PLAY
    {
        ACTION,
        PAUSE
    };
    STATES_GAME_PLAY _states;
    Items* items;
    Hero_1 Hro;
    Background BG;
    Mago Villano_1;
    Shots* shootig;
    Sauron Villano_2;
    Anillos anillos;
    Platforms Pltfm;
    Colisionables colisionables;
    Platforms_rectangle_shape Prs[35];
    Manager_wolf _Wolf_manager;
    // Agregar el reloj para movimiento random de villanos
    sf::Clock clock;

    const int MAX_WOLVES = 3;
    sf::Clock _wolf_spawn_timer;

    std::string _namePlayer;



    bool lavel_I=true;
    bool lavel_II=false;

    sf::Font _font_pause;
    sf::Text _text_pause;
    sf::Font _fontPlayer;
    sf::Text _textPlayer;
    sf::Font _fontPuntaje;
    sf::Text _textPuntaje;
    sf::Font _fontvidas;
    sf::Text _textvidas;
    sf::Text _cantvidas;

    int puntaje = 0;
    int enemigos=0;
    int enemigos_eliminados=0;
    bool _winner = false;
    bool _game_over=false;

    bool dying=false;
    int i;
    int j;

};

#endif // GAME_PLAY_H
