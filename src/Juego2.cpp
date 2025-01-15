#include "Juego2.h"

Juego2::Juego2():
    B1("INICIO", sf::Vector2f(1300 / 2.55, 700 / 5 * 1.7), sf::Vector2f(0.35, 0.5)),
    B2("RANKING", sf::Vector2f(1300 / 2.55, 700 / 5 * 2.3), sf::Vector2f(0.35, 0.5)),
    B3("CONTROLES", sf::Vector2f(1300 / 2.55, 700 / 5 * 2.9), sf::Vector2f(0.35, 0.5)),
    B4("CREDITOS", sf::Vector2f(1300 / 2.55, 700 / 5 * 3.5), sf::Vector2f(0.35, 0.5)),
    B5("SALIR", sf::Vector2f(1300 / 2.55, 700 / 5 * 4.1), sf::Vector2f(0.35, 0.5)),
    B6("JUGAR", sf::Vector2f(1300 / 6, 700 / 3.5 * 1.5), sf::Vector2f(0.35, 0.5)),
    B7("INGRESAR NOMBRE", sf::Vector2f(1300 / 6, 700 /3.5 * 2), sf::Vector2f(0.35, 0.5)),
    B8("VOLVER", sf::Vector2f(1300 / 6, 700 / 3.5 * 2.5), sf::Vector2f(0.35, 0.5)),
    B9("VOLVER", sf::Vector2f(1300 / 2.55, 700 /2.8 * 2), sf::Vector2f(0.35, 0.5)),
    B10("SALIR", sf::Vector2f(1300 / 2.55, 700 / 2.8 * 2.3), sf::Vector2f(0.35, 0.5)),
    B11("VOLVER", sf::Vector2f(1300 / 2.55, 700 /2.8 * 2), sf::Vector2f(0.35, 0.5)),
    B12("SALIR", sf::Vector2f(1300 / 2.55, 700 / 2.8 * 2.3), sf::Vector2f(0.35, 0.5)),
    B13("VOLVER", sf::Vector2f(1300 / 1.5, 700 /2.8 * 2), sf::Vector2f(0.35, 0.5)),
    B14("SALIR", sf::Vector2f(1300 / 1.5, 700 / 2.8 * 2.3), sf::Vector2f(0.35, 0.5)),
    B15("VOLVER", sf::Vector2f(1300 / 4.7, 700 /1.27), sf::Vector2f(0.35, 0.5)),
    B16("SALIR", sf::Vector2f(1300 / 1.6, 700 / 1.27), sf::Vector2f(0.35, 0.5))

{
    _menu_ppal=new Menu(TIPO_MENU::PRINCIPAL);
    _menu_ranking=new Menu(TIPO_MENU::RANKING);
    _menu_reglamento=new Menu(TIPO_MENU::REGLAMENTO);
    _menu_creditos=new Menu(TIPO_MENU::CREDITOS);
    _menu_secundario=new Menu(TIPO_MENU::SECUNDARIO);
    _menu_game_over=new Menu(TIPO_MENU::GAME_OVER);
    _menu_winner=new Menu(TIPO_MENU::WINNER);

    _player=new Player();

    _tipo_menu=TIPO_MENU::PRINCIPAL;
}

Juego2::~Juego2()
{
    delete _menu_ppal;
    delete _menu_ranking;
    delete _menu_reglamento;
    delete _menu_creditos;
    delete _menu_secundario;
    delete _menu_game_over;
    delete _menu_winner;
}

int Juego2::run()      ///Estructura principal de la aplicacion
{
    sf::RenderWindow window(sf::VideoMode(1300, 700), "El Anillo de Poder");
    window.setFramerateLimit(60);

    while(true)
    {
        switch (_tipo_menu)
        {
        case TIPO_MENU::PRINCIPAL:
            _tipo_menu=menuPpal(window);
            break;
        case TIPO_MENU::RANKING:
            _tipo_menu=ranking(window);
            break;
        case TIPO_MENU::REGLAMENTO:
            _tipo_menu=reglamento(window);
            break;
        case TIPO_MENU::CREDITOS:
            _tipo_menu=creditos(window);
            break;
        case TIPO_MENU::EXIT:
            window.close();
            return 0;
            break;
        case TIPO_MENU::SECUNDARIO:             ///aca esta el juego, o sea gameplay
            _tipo_menu=menuSecundario(window);
            break;
        case TIPO_MENU::WINNER:
            _tipo_menu=winner(window);
            break;
        case TIPO_MENU::GAME_OVER:
            _tipo_menu=gameOver(window);
            break;
        default:
            break;
        }
    }
}

TIPO_MENU Juego2::menuPpal(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::PRINCIPAL;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B1.getBounds().contains(mousePos))
                    {
                        std::cout << "INICIO" << std::endl;
                        t=TIPO_MENU::SECUNDARIO;
                    }
                    if(B2.getBounds().contains(mousePos))
                    {
                        std::cout << "RANKING" << std::endl;
                        t=TIPO_MENU::RANKING;
                    }
                    if(B3.getBounds().contains(mousePos))
                    {
                        std::cout << "CONTROLES" << std::endl;
                        t=TIPO_MENU::REGLAMENTO;
                    }
                    if(B4.getBounds().contains(mousePos))
                    {
                        std::cout << "CRÉDITOs" << std::endl;
                        t=TIPO_MENU::CREDITOS;
                    }
                    if(B5.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;
                    }
                }
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }

        window.clear(sf::Color::Black);
        window.draw(*_menu_ppal);   ///dibujo el contendido , que es un menu dibujable :)
        showStart1(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::ranking(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::RANKING;

    Partida partida;

    Ranking ranking;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B9.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;
                    }
                    if(B10.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;

                    }

                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ///ACA VA EL RANKING!

        if(partida.contarPartidas()>0)
        {
            ranking.setRanking();

            window.clear(sf::Color::Black);
            window.draw(*_menu_ranking);   ///dibujo el contendido , que es un menu dibujable :)
            showRanking(window,ranking);
        }
        else
        {
            window.clear(sf::Color::Black);
            window.draw(*_menu_ranking);   ///dibujo el contendido , que es un menu dibujable :)
        }


        window.display();

        return t;
    }
}

TIPO_MENU Juego2::creditos(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::CREDITOS;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B11.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;
                    }
                    if(B12.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;
                    }
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(*_menu_creditos);   ///dibujo el contendido , que es un menu dibujable :)
        showBestTeam(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::reglamento(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::REGLAMENTO;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B13.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;
                    }
                    if(B14.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;

                    }
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        window.clear(sf::Color::Black);
        window.draw(*_menu_reglamento);   ///dibujo el contendido , que es un menu dibujable :)
        showRule(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::menuSecundario(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::SECUNDARIO;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B6.getBounds().contains(mousePos))
                    {
                        std::cout << "JUGAR" << std::endl;
                        t=Jugar(*_player,window);
                    }
                    if(B7.getBounds().contains(mousePos))
                    {
                        std::cout << "INGRESAR NOMBRE" << std::endl;
                        _player->setNombre(_player->ingresarNombre());

                    }
                    if(B8.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER PRINCIPAL" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;

                    }

                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        window.clear(sf::Color::Black);
        window.draw(*_menu_secundario);   ///dibujo el contendido , que es un menu dibujable :)
        showStart2(window);
        window.display();
        return t;
    }
}



TIPO_MENU Juego2::winner(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::WINNER;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B15.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;
                    }
                    if(B16.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;

                    }

                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(*_menu_winner);   ///dibujo el contendido , que es un menu dibujable :)
        showWinnerText(window);
        window.display();
        return t;
    }
}

TIPO_MENU Juego2::gameOver(sf::RenderWindow& window)
{
    TIPO_MENU t=TIPO_MENU::GAME_OVER;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if(B15.getBounds().contains(mousePos))
                    {
                        std::cout << "VOLVER" << std::endl;
                        t=TIPO_MENU::PRINCIPAL;
                    }
                    if(B16.getBounds().contains(mousePos))
                    {
                        std::cout << "SALIR" << std::endl;
                        t=TIPO_MENU::EXIT;

                    }

                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(*_menu_game_over);   ///dibujo el contendido , que es un menu dibujable :)
        showLoserText(window);
        window.display();
        return t;
    }
}

void Juego2::showStart1(sf::RenderWindow& window)
{
    sf::Text _tittle;
    sf::Font _font_t;


    _font_t.loadFromFile("Resourses/Font/VIKING-N.TTF");
    _tittle.setFont(_font_t);
    _tittle.setString("El anillo de poder");
    _tittle.setFillColor(sf::Color(223,223,223));
    _tittle.setCharacterSize(70.f);
    _tittle.setPosition(220,70);

    window.draw(_tittle);
    window.draw(B1);
    window.draw(B2);
    window.draw(B3);
    window.draw(B4);
    window.draw(B5);

}

void Juego2::showStart2(sf::RenderWindow& window)
{
    sf::Text _tittle;
    sf::Font _font_t;

    _font_t.loadFromFile("Resourses/Font/VIKING-N.TTF");
    _tittle.setFont(_font_t);
    _tittle.setString("El anillo de poder");
    _tittle.setFillColor(sf::Color(223,223,223));
    _tittle.setCharacterSize(70.f);
    _tittle.setPosition(220,70);

    window.draw(_tittle);
    window.draw(B6);
    window.draw(B7);
    window.draw(B8);
}


void Juego2::showBestTeam(sf::RenderWindow& window)
{
    sf::Text utn;
    sf::Text labo;
    sf::Text project;
    sf::Text fer;
    sf::Text emi;
    sf::Text mateo;

    sf::Text _tittle;
    sf::Font _font_t;

    _font_t.loadFromFile("Resourses/Font/VIKING-N.TTF");
    _tittle.setFont(_font_t);
    _tittle.setString("El anillo de poder");
    _tittle.setFillColor(sf::Color(223,223,223));
    _tittle.setCharacterSize(70.f);
    _tittle.setPosition(220,70);

    sf::Font font;
    font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");

    utn=sf::Text("U.T.N.",_font_t,50);
    utn.setFillColor(sf::Color(255,255,255,180));
    utn.setPosition(200,220);

    labo=sf::Text("Laboratorio II",_font_t,50);
    labo.setFillColor(sf::Color(255,255,255,180));
    labo.setPosition(500,220);

    project=sf::Text("Proyecto realizado por:",font,20);
    project.setFillColor(sf::Color(255,255,255,180));
    project.setPosition(150,290);

    fer=sf::Text("Fernando Daniel Clingo_______________ Legajo xxxxx",font,20);
    fer.setFillColor(sf::Color(255,255,255,180));
    fer.setPosition(150,340);

    emi=sf::Text("Emilse Narela Pericles_______________ Legajo xxxxx",font,20);
    emi.setFillColor(sf::Color(255,255,255,180));
    emi.setPosition(150,400);

    mateo=sf::Text("Mateo Leon Maciel__________________ Legajo xxxxx",font,20);
    mateo.setFillColor(sf::Color(255,255,255,180));
    mateo.setPosition(150,460);


    window.draw(_tittle);
    window.draw(utn);
    window.draw(labo);
    window.draw(project);
    window.draw(fer);
    window.draw(emi);
    window.draw(mateo);
    window.draw(B11);
    window.draw(B12);
}


void Juego2::showRule(sf::RenderWindow& window)
{
    sf::Sprite sprite_S;
    sf::Texture texture_S;
    sf::Sprite sprite_D;
    sf::Texture texture_D;
    sf::Sprite sprite_A;
    sf::Texture texture_A;
    sf::Sprite sprite_Izq;
    sf::Texture texture_Izq;
    sf::Sprite sprite_Der;
    sf::Texture texture_Der;
    sf::Sprite sprite_P;
    sf::Texture texture_P;
    sf::Texture texture_spaceBar;
    sf::Sprite sprite_spaceBar;
    sf::Texture _texture_historia;
    sf::Sprite _sprite_historia;
    sf::Text S;
    sf::Text D;
    sf::Text A;
    sf::Text Der;
    sf::Text Izq;
    sf::Text P;
    sf::Text spaceBar;
    sf::Font font;
    sf::Text nombre_text;
    sf::Font nombre_font;


    sf::Text _tittle;
    sf::Font _font_t;

    _font_t.loadFromFile("Resourses/Font/VIKING-N.TTF");
    _tittle.setFont(_font_t);
    _tittle.setString("El anillo de poder");
    _tittle.setFillColor(sf::Color(223,223,223));
    _tittle.setCharacterSize(70.f);
    _tittle.setPosition(220,70);



    font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");

    texture_A.loadFromFile("Resourses/A.png");
    sprite_A.setTexture(texture_A);
    sprite_A.setPosition(1020,250);

    A=sf::Text("Agarrar",font,25);
    A.setFillColor(sf::Color(255,255,255,180));
    A.setPosition(1000,380);

    texture_S.loadFromFile("Resourses/S.png");
    sprite_S.setTexture(texture_S);
    sprite_S.setPosition(820,250);

    S=sf::Text("Atacar",font,25);
    S.setFillColor(sf::Color(255,255,255,180));
    S.setPosition(820,380);

    texture_D.loadFromFile("Resourses/D.png");
    sprite_D.setTexture(texture_D);
    sprite_D.setPosition(600,250);

    D=sf::Text("Disparar",font,25);
    D.setFillColor(sf::Color(255,255,255,180));
    D.setPosition(580,380);

    texture_Izq.loadFromFile("Resourses/Izq.png");
    sprite_Izq.setTexture(texture_Izq);
    sprite_Izq.setPosition(350,250);

    Izq=sf::Text("Izquierda",font,25);
    Izq.setFillColor(sf::Color(255,255,255,180));
    Izq.setPosition(320,380);

    texture_Der.loadFromFile("Resourses/Der.png");
    sprite_Der.setTexture(texture_Der);
    sprite_Der.setPosition(110,250);

    Der=sf::Text("Derecha",font,25);
    Der.setFillColor(sf::Color(255,255,255,180));
    Der.setPosition(110,380);

    texture_spaceBar.loadFromFile("Resourses/spaceBar.png");
    sprite_spaceBar.setTexture(texture_spaceBar);
    sprite_spaceBar.setPosition(120,450);
    sprite_spaceBar.setScale(0.1,0.13);

    spaceBar=sf::Text("Saltar",font,25);
    spaceBar.setFillColor(sf::Color(255,255,255,180));
    spaceBar.setPosition(130,550);

    texture_P.loadFromFile("Resourses/P.png");
    sprite_P.setTexture(texture_P);
    sprite_P.setPosition(550,420);

    P=sf::Text("Pausa",font,25);
    P.setFillColor(sf::Color(255,255,255,180));
    P.setPosition(550,550);


    window.draw(_tittle);
    window.draw(nombre_text);
    window.draw(sprite_A);
    window.draw(sprite_S);
    window.draw(sprite_D);
    window.draw(sprite_Izq);
    window.draw(sprite_Der);
    window.draw(sprite_spaceBar);
    window.draw(sprite_P);
    window.draw(A);
    window.draw(S);
    window.draw(D);
    window.draw(Izq);
    window.draw(Der);
    window.draw(spaceBar);
    window.draw(P);
    window.draw(B13);
    window.draw(B14);
}

void Juego2::showWinnerText(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;
    sf::Text text_P;
    sf::Font font_P;

    font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");
    font_P.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");

    text=sf::Text("WINNER!!!",font,130);
    text.setFillColor(sf::Color(255,255,255,80));
    text.setPosition(80,300);

    window.draw(text);
    //window.draw(text_P);
    window.draw(B15);
    window.draw(B16);
}

void Juego2::showLoserText(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font font;

    font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");

    text=sf::Text("GAME OVER",font,130);
    text.setFillColor(sf::Color(255,255,255,80));
    text.setPosition(80,300);
    window.draw(text);
    window.draw(B15);
    window.draw(B16);
}

void Juego2::showRanking(sf::RenderWindow& window,Ranking& ranking)
{

    sf::Text _tittle;
    sf::Font _font_t;

    _font_t.loadFromFile("Resourses/Font/VIKING-N.TTF");
    _tittle.setFont(_font_t);
    _tittle.setString("El anillo de poder");
    _tittle.setFillColor(sf::Color(223,223,223));
    _tittle.setCharacterSize(70.f);
    _tittle.setPosition(220,70);

    Partida* p=ranking.getRanking();

    sf::Text text[10];
    sf::Font font;
    font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf");

    window.draw(_tittle);
    for(int i=0; i<10; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(10);
        text[i].setFillColor(sf::Color(0,0,0));
        text[i].setString("Puesto n°:  "+ std::to_string(i+1)+ "  " +p[i].getName()+ " con " +std::to_string(p[i].getPuntos())+ " puntos");
        if(i<5)
        {
            text[i].setPosition(240, 265 + i* 45);
        }
        else
        {
            text[i].setPosition(700, 40 + i* 45);
        }


        window.draw(text[i]);
    }
    window.draw(B9);
    window.draw(B10);
}


TIPO_MENU Juego2::Jugar(Player& player,sf::RenderWindow& window)
{
    sf::Sprite sprite_fondo;
    sf::Texture texture_fondo;

    texture_fondo.loadFromFile("Resourses/Menu_background.png");
    sprite_fondo.setTexture(texture_fondo);

    Game_play gp(window,player);
    gp.setNombrePlayer(player.getNombre());

    Audio musica(1);

    musica.audioON();

    sf::View _view(sf::FloatRect(0.f,0.f,1100.f,600.f));//1300, 700

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        ///Por aca condicion de juego
        if(gp.getGameOver()==false&&gp.getWinner()==false)
        {

            _view.setCenter(gp.get_camera_position());//.x,415


            window.setView(_view);
            gp.update(window);

            gp.cmd();

            window.clear(sf::Color::Black);

            window.draw(sprite_fondo);
            gp.draw(window);

            window.display();
        }

        ///Por aca ganaste!
        if(gp.getWinner()==true&&gp.getGameOver()==false)
        {
            _view.setCenter(660,380);
            _view.setSize(1300.f, 700.f);
            window.setView(_view);
            musica.audioOFF();
            ///Por aca hay que mostrar pantalla winner!!
            gp.setPuntaje(gp.puntaje);
            Partida partida(gp.getPuntaje(), gp.getNombrePlayer());
            FILE *pPartida = fopen("Partidas.dat", "ab");
            if(pPartida == nullptr)
            {
                std::cout<< "No se pudo abrir/crear archivo"<< std::endl;

            }
            fwrite(&partida, sizeof(Partida), 1, pPartida);
            fclose(pPartida);
            std::cout<< "Archivo creado correctamente"<<std::endl;
            return TIPO_MENU::WINNER;
        }
        else///Por aca perdiste!
        {
            if(gp.getGameOver()==true&&gp.getWinner()==false)
            {
                _view.setCenter(660,380);
                _view.setSize(1300.f, 700.f);
                window.setView(_view);
                musica.audioOFF();
                ///Por aca hay que mostrar pantalla GAMEOVER!!
                Partida partida(gp.getPuntaje(), gp.getNombrePlayer());

                FILE *pPartida = fopen("Partidas.dat", "ab");
                if(pPartida == nullptr)
                {
                    std::cout<< "No se pudo abrir/crear archivo"<< std::endl;
                }
                fwrite(&partida, sizeof(Partida), 1, pPartida);
                fclose(pPartida);
                std::cout<< "Archivo creado correctamente"<<std::endl;
                return TIPO_MENU::GAME_OVER;
            }
        }


    }
}

