#include "Menu.h"

Menu::Menu(TIPO_MENU tipo)
{
    _tipo_menu=tipo;        //en base a uno de los posibles tipos de menu
    initBackground();

}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background,states);
}

void Menu::initBackground()
{
    sf::Vector2f scale;
    switch(_tipo_menu)
    {
    case TIPO_MENU::PRINCIPAL:
        _texture_background.loadFromFile("Resourses/Menu_background2.png");
        _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::RANKING:
        _texture_background.loadFromFile("Resourses/SUBMenu_background2.png");
         _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::REGLAMENTO:
        _texture_background.loadFromFile("Resourses/SUBMenu_background2.png");
         _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::CREDITOS:
        _texture_background.loadFromFile("Resourses/SUBMenu_background2.png");
         _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::SECUNDARIO:
        _texture_background.loadFromFile("Resourses/SUBMenu_background4.png");
         _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::GAME_OVER:
        _texture_background.loadFromFile("Resourses/Menu.png");
         _texture_background.setSmooth(true);
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::WINNER:
        _texture_background.loadFromFile("Resourses/Menu.png");
         _texture_background.setSmooth(true);
        scale = {1.5, 1.5};
        break;

    default:
        _texture_background.loadFromFile("Resourses/Menu_background.png");
         _texture_background.setSmooth(true);
        scale= {0.23,0.2};
        break;
    }
    _background.setTexture(_texture_background);
    _background.setScale(scale);

}
