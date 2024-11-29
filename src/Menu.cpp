#include "Menu.h"

Menu::Menu(TIPO_MENU tipo)
{
    _tipo_menu=tipo;        //en base a uno de los posibles tipos de menu
    initFont();
    initBackground();
    initTextos();
    _selected_item=0;

}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background,states);
    for(sf::Text _t : _array_textos)
    {
        target.draw(_t,states);
    }
}

const int Menu::getSelectedItem()
{
    return _selected_item;
}

void Menu::setSelectedItem(const int i)
{
    _selected_item=i;
}


void Menu::up()
{
    if(_selected_item-1>=0)
    {
        _array_textos[_selected_item].setColor(sf::Color(255,255,255,80));
        _selected_item--;

        _array_textos[_selected_item].setColor(sf::Color::Yellow);
    }
}

void Menu::down()
{
    if(_selected_item+1<getSizeArray())
    {
        _array_textos[_selected_item].setColor(sf::Color(255,255,255,80));
        _selected_item++;

        _array_textos[_selected_item].setColor(sf::Color::Yellow);
    }
}


void Menu::updateSelection()
{
    updateSelectedItem();
    for(sf::Text t : _array_textos)
    {
        t.setColor(sf::Color(255,255,255,80));                  ///Des-seleccionamos todos
    }
    _array_textos[_selected_item].setColor(sf::Color::Yellow);   ///Pintamos el seleccionado
}


void Menu::updateSelectedItem()
{
    if(_selected_item<=0)
        _selected_item=0;
    else if(_selected_item>=getSizeArray())
        _selected_item=getSizeArray()-1;

}

const int Menu::getSizeArray()
{
    return int(_array_textos.size());
}

void Menu::agregarTexto(std::string s, int string_size, sf::Vector2f position,bool yellow)
{
    sf::Text texto;
    texto=sf::Text(s,_font,string_size);
    texto.setPosition(position);
    if(yellow)
    {
        texto.setColor(sf::Color::Yellow);
    }
    else
    {
        texto.setColor(sf::Color(255,255,255,80));
    }
    _array_textos.push_back(texto);
}



void Menu::initBackground()
{
    sf::Vector2f scale;
    switch(_tipo_menu)
    {
    case TIPO_MENU::PRINCIPAL:
        _texture_background.loadFromFile("Resourses/Menu_background.png");
        scale= {1,1};

        break;
    case TIPO_MENU::RANKING:
        _texture_background.loadFromFile("Resourses/SUBMenu_background.png");
        scale= {1,1};
        break;
    case TIPO_MENU::REGLAMENTO:
        _texture_background.loadFromFile("Resourses/SUBMenu_background.png");
        scale= {1,1};
        break;
    case TIPO_MENU::CREDITOS:
        _texture_background.loadFromFile("Resourses/SUBMenu_background.png");
        scale= {1,1};
        break;
    case TIPO_MENU::SECUNDARIO:
        _texture_background.loadFromFile("Resourses/SUBMenu_background.png");
        scale= {1,1};
        break;
    case TIPO_MENU::GAME_OVER:
        _texture_background.loadFromFile("Resourses/Menu.png");
        scale= {1.5,1.5};
        break;
    case TIPO_MENU::WINNER:
        _texture_background.loadFromFile("Resourses/Menu.png");
        scale = {1.5, 1.5};
        break;

    default:
        _texture_background.loadFromFile("Resourses/Menu_background.png");
        scale= {0.23,0.2};
        break;
    }
    _background.setTexture(_texture_background);
    _background.setScale(scale);

}

void Menu::initFont()
{
    _font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");
}



void Menu::initTextos()
{
    switch(_tipo_menu)
    {
    case TIPO_MENU::PRINCIPAL:
        initTextosPrincipal();
        break;
    case TIPO_MENU::RANKING:
        initTextosRanking();
        break;
    case TIPO_MENU::REGLAMENTO:
        initTextosReglamento();
        break;
    case TIPO_MENU::CREDITOS:
        initTextosCreditos();
        break;
    case TIPO_MENU::SECUNDARIO:
        initTextosSecundarios();
        break;
    case TIPO_MENU::GAME_OVER:
        initTextosGameOver();
        break;
    case TIPO_MENU::WINNER:
        initTextosWinner();
        break;
    default:
        initTextosPrincipal();
        break;
    }
}

void Menu::initTextosPrincipal()
{
    int width=1300;
    int height=700;

    agregarTexto("INICIO",30,sf::Vector2f(width/2.55,height/5*1.7),true);
    agregarTexto("RANKING",30,sf::Vector2f(width/2.55,height/5*2.3),false);
    agregarTexto("CONTROLES",30,sf::Vector2f(width/2.55,height/5*2.9),false);
    agregarTexto("CREDITOS",30,sf::Vector2f(width/2.55,height/5*3.5),false);
    agregarTexto("SALIR",30,sf::Vector2f(width/2.55,height/5*4.1),false);
}

void Menu::initTextosRanking()
{

    agregarTexto("VOLVER",30, {560,506},true);
    agregarTexto("SALIR",30, {560,556},false);
}

void Menu::initTextosCreditos()
{

    agregarTexto("VOLVER",30, {560,506},true);
    agregarTexto("SALIR",30, {560,556},false);
}

void Menu::initTextosReglamento()
{
    agregarTexto("VOLVER",30, {860,506},true);
    agregarTexto("SALIR",30, {860,556},false);
}

void Menu::initTextosSecundarios()
{
    int width=1300;
    int height=700;

    agregarTexto("JUGAR",40,sf::Vector2f(width / 6, height / 3.5 * 1.5),true);
    agregarTexto("INGRESAR NOMBRE",40,sf::Vector2f(width / 6, height / 3.5 * 2),false);
    agregarTexto("VOLVER",40,sf::Vector2f(width / 6, height / 3.5 * 2.5),false);
}

void Menu::initTextosGameOver()
{
    int width=1300;
    int height=700;

    agregarTexto("VOLVER",30, {300,550},true);
    agregarTexto("SALIR",30, {813,550},false);
}

void Menu::initTextosWinner()
{
    int width=1300;
    int height=700;

    agregarTexto("VOLVER",30, {300,550},true);
    agregarTexto("SALIR",30, {813,550},false);
}
