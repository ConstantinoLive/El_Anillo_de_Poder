#ifndef JUEGO2_H
#define JUEGO2_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "Game_play.h"
#include "Partida.h"
#include "Ranking.h"
#include "Audio.h"
#include "Button.h"

class Juego2
{
public:
    Juego2();
    virtual ~Juego2();


    int run();

    TIPO_MENU menuPpal(sf::RenderWindow& window);
    TIPO_MENU ranking(sf::RenderWindow& window);
    TIPO_MENU reglamento(sf::RenderWindow& window);
    TIPO_MENU creditos(sf::RenderWindow& window);
    TIPO_MENU menuSecundario(sf::RenderWindow& window);
    TIPO_MENU gameOver(sf::RenderWindow& window);
    TIPO_MENU winner(sf::RenderWindow& window);

    void showStart1(sf::RenderWindow& window);
    void showStart2(sf::RenderWindow& window);
    void showRule(sf::RenderWindow& window);
    void showBestTeam(sf::RenderWindow& window);
    void showWinnerText(sf::RenderWindow& window);
    void showLoserText(sf::RenderWindow& window);
    void showRanking(sf::RenderWindow& window,Ranking& ranking);

    TIPO_MENU Jugar(Player& player,sf::RenderWindow& window);



private:

    TIPO_MENU _tipo_menu;
    Menu* _menu_ppal;
    Menu* _menu_ranking;
    Menu* _menu_reglamento;
    Menu* _menu_creditos;
    Menu* _menu_secundario;
    Menu* _menu_game_over;
    Menu* _menu_winner;

    Player* _player;
    Button B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B16;
    sf::Image cursorImagen;
    sf::Cursor customCursor;
    sf::Image icon;





};

#endif // JUEGO2_H
