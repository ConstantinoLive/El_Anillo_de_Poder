#ifndef MENU_H
#define MENU_H

#include<iostream>


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>





enum TIPO_MENU
{
    PRINCIPAL,
    RANKING,
    REGLAMENTO,
    CREDITOS,
    SECUNDARIO,
    GAME_OVER,
    WINNER,
    EXIT
};

class Menu : public sf::Drawable
{
    public:
        Menu(TIPO_MENU tipo);
        virtual ~Menu();

        void draw(sf::RenderTarget&target,sf::RenderStates states)const override;

        void initBackground();


    private:
        TIPO_MENU _tipo_menu;  /// elijo el tipo de menu

        sf::Sprite _background;
        sf::Texture _texture_background;



};
#endif
