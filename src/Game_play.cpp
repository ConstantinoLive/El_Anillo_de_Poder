#include "Game_play.h"

Game_play::Game_play(sf::RenderWindow& window,Player& player)
{

    num_PackFlechas=0;
    i=0;
    _states=STATES_GAME_PLAY::ACTION;
    _current_level = LEVEL_I;
    clock.restart();
    //Superficie
    Prs[0]=Platforms_rectangle_shape(508,846,355);
    Prs[1]=Platforms_rectangle_shape(264,1466,195);
    Prs[2]=Platforms_rectangle_shape(388,1750,325);
    Prs[3]=Platforms_rectangle_shape(274,4292,365);
    Prs[4]=Platforms_rectangle_shape(495,4638,195);
    Prs[5]=Platforms_rectangle_shape(156,5195,365);
    Prs[6]=Platforms_rectangle_shape(380,5578,195);
    Prs[7]=Platforms_rectangle_shape(508,6406,341);
    Prs[8]=Platforms_rectangle_shape(272,7942,302);
    Prs[9]=Platforms_rectangle_shape(264,9170,317);
    Prs[10]=Platforms_rectangle_shape(264,9584,170);
    Prs[11]=Platforms_rectangle_shape(500,10008,307);
    Prs[12]=Platforms_rectangle_shape(505,10680,177);

    //Cueva
    Prs[13]=Platforms_rectangle_shape(80,35,950);
    Prs[14]=Platforms_rectangle_shape (312, 236,1053);
    Prs[15]=Platforms_rectangle_shape(108,1740,1105);
    Prs[16]=Platforms_rectangle_shape(528,1890,980);
    Prs[17]=Platforms_rectangle_shape(105,2642,897);
    Prs[18]=Platforms_rectangle_shape(105,4978,957);
    Prs[19]=Platforms_rectangle_shape(105,5154,1070);
    Prs[20]=Platforms_rectangle_shape(105,5780,1070);
    Prs[21]=Platforms_rectangle_shape(440,6010,975);
    Prs[22]=Platforms_rectangle_shape(188,6608,1055);
    Prs[23]=Platforms_rectangle_shape(105,8044,1105);
    Prs[24]=Platforms_rectangle_shape(105,8276,985);
    Prs[25]=Platforms_rectangle_shape(444,8544,910);
    Prs[26]=Platforms_rectangle_shape(180,9116,985);
    Prs[27]=Platforms_rectangle_shape(105,9447,910);
    Prs[28]=Platforms_rectangle_shape(105,9624,1085);
    Prs[29]=Platforms_rectangle_shape(460,9844,990);
    Prs[30]=Platforms_rectangle_shape(105,10444,1075);
    Prs[31]=Platforms_rectangle_shape(105,11176,1080);
    Prs[32]=Platforms_rectangle_shape(404,11404,970);
    Prs[33]=Platforms_rectangle_shape(105,11962,870);
    Prs[34]=Platforms_rectangle_shape(228,12132,1025);

    _wolf_spawn_timer.restart();

    _namePlayer = player.getNombre();

    /************** NOMBRE DE JUGADOR ****************/

    if (!_fontPlayer.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _textPlayer.setFont(_fontPlayer);
    _textPlayer.setString(_namePlayer);
    _textPlayer.setFillColor(sf::Color::Yellow);
    _textPlayer.setCharacterSize(10.f);

    /*****************PUNTAJE**************************/
    if (!_fontPuntaje.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _textPuntaje.setFont(_fontPuntaje);
    _textPuntaje.setFillColor(sf::Color::Yellow);
    _textPuntaje_1.setFont(_fontPuntaje);
    _textPuntaje_1.setFillColor(sf::Color::Yellow);
    _textPuntaje.setCharacterSize(10.f);
    _textPuntaje_1.setCharacterSize(10.f);

    /*****************VIDAS**************************/

    if (!_fontvidas.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _textvidas.setFont(_fontvidas);
    _textvidas.setFillColor(sf::Color::Yellow);
    _textvidas_1.setFont(_fontvidas);
    _textvidas_1.setFillColor(sf::Color::Yellow);
    _textvidas.setCharacterSize(10.f);
    _textvidas_1.setCharacterSize(10.f);

    /*****************ENERGIA**************************/

    if (!_fontenergia.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }
    _textenergia.setFont(_fontenergia);
    _textenergia.setFillColor(sf::Color::Yellow);
    _textenergia_1.setFont(_fontenergia);
    _textenergia_1.setFillColor(sf::Color::Yellow);
    _textenergia.setCharacterSize(10.f);
    _textenergia_1.setCharacterSize(10.f);

    /***********************************************/


}

Game_play::~Game_play()
{

}

void Game_play::draw(sf::RenderWindow& window)
{
    window.draw(BG.getDraw());
    window.draw(Pltfm.getDraw());
    window.draw(Hro.getDraw());

    window.draw(Villano_1.getDraw());

    window.draw(Villano_2.getDraw());

    if (!anillos.isObtenido())
    {
        window.draw(anillos.getDraw());
    }


    if (!items.isObtenido[num_PackFlechas])
    {
        window.draw(items.getDraw());
    }


    for (auto Wolf : _Wolf_manager._array_wolf)
    {
        if (!Wolf->death)
        {
            window.draw(*Wolf);
        }
    }

    for (auto& Shots: Hro._shots_array)
    {
        window.draw(Shots->getDraw());
    }

    for (auto& Shots: Villano_1._shots_array)
    {
        window.draw(Shots->getDraw());
    }
    for (auto& Platform:Prs)
    {
        window.draw(Platform.getDraw());
    }

    if(_states==STATES_GAME_PLAY::PAUSE)
    {
        window.draw(_text_pause);
    }

    if(_states==STATES_GAME_PLAY::ACTION)
    {
        window.draw(_textPlayer);
        window.draw(_textPuntaje);
        window.draw(_textvidas);
        window.draw(_textenergia);
        window.draw(_textPuntaje_1);
        window.draw(_textvidas_1);
        window.draw(_textenergia_1);
    }
}

void Game_play::cmd()
{


    if(_states==STATES_GAME_PLAY::ACTION)
    {
        check_collision_platform();
        colisionables.anillosColision(Hro, anillos);
        colisionables.colisionFlechasConVillanos(Hro, Villano_1, Villano_2, death, dying);
        colisionables.colisionHeroConVillanos(Hro, Villano_1, Villano_2, death, dying, attack);
        colisionables.colisionSauronConHro(Villano_2,Hro, death);
        colisionables.colisionMagoConHero(Villano_1, Hro, death);
        colisionables.colisionHeroConWolf(Hro,_Wolf_manager,attack,dying);
        colisionables.colisionFlechasWolf(Hro,_Wolf_manager,dying);
        colisionables.colisionWolfConHero(Hro,_Wolf_manager,dying);


        Hro.mobility();

        Villano_1.mobility(Hro.getPosition(),Hro.getEstado());

        Villano_2.mobility(Hro.getPosition(),Hro.getEstado());
//
//        for (auto& Wolf :  _Wolf_manager._array_wolf)
//        {
//            Wolf->mobility(Hro.getPosition());
//        }

//        anillos.mobility(Hro.getPosition());

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            _states=STATES_GAME_PLAY::PAUSE;
            if (!_font_pause.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
            {
                std::cout<<"Error al cargar texto"<<std::endl;
            }
            std::cout<<"Pausa"<<std::endl;
            _text_pause.setFont(_font_pause);
            _text_pause.setString("PAUSA");
            _text_pause.setFillColor(sf::Color::Red);
            _text_pause.setPosition(Hro.getPosition().x+200,Hro.getPosition().y+200);
        }
    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            _states=STATES_GAME_PLAY::ACTION;
        }
    }
}
void Game_play::update(sf::RenderTarget& window)
{
    if(_game_over==false)
    {

        _textenergia.setPosition(Hro.getPosition().x+400,Hro.getPosition().y-270);
        _textenergia.setString(std::to_string(Hro.porcentajeVida));
        _textvidas.setPosition(Hro.getPosition().x+200,Hro.getPosition().y-270);
        _textvidas.setString(std::to_string(Hro.vida));
        _textPuntaje.setPosition(Hro.getPosition().x-100,Hro.getPosition().y-270);
        _textPuntaje.setString(std::to_string(puntaje));
        _textPlayer.setPosition(Hro.getPosition().x-500,Hro.getPosition().y-270);

        _textenergia_1.setPosition(Hro.getPosition().x+300,Hro.getPosition().y-270);
        _textenergia_1.setString("Energia");
        _textvidas_1.setPosition(Hro.getPosition().x+100,Hro.getPosition().y-270);
        _textvidas_1.setString("Vidas");
        _textPuntaje_1.setPosition(Hro.getPosition().x-250,Hro.getPosition().y-270);
        _textPuntaje_1.setString("Puntaje");

        BG.update();

        sf::Time deltaTime = clock.restart(); // Reinicia el reloj y obtiene el tiempo transcurrido



        if(_states==STATES_GAME_PLAY::ACTION)
        {
            Hro.update();

            Villano_1.update(Hro.getPosition(), deltaTime);

            Villano_2.update(Hro.getPosition(), deltaTime);

            for (auto& Wolf :  _Wolf_manager._array_wolf)
            {
                Wolf->update();
            }

            anillos.update(Hro.getPosition());

            check_collision_platform();

            updateEnemySup();

            if(Villano_1.isAlive==false)
            {
                if(Villano_1_clock_update_muerte_ACTIVADO==false)
                {
                    clock_update_muerte.restart();
                    Villano_1_clock_update_muerte_ACTIVADO=true;
                }
                if(clock_update_muerte.getElapsedTime().asSeconds())
                {

                    posicion_LEVEL_II=true;
                    posicionInicial_LEVEL_II++;
                    posicion_LEVEL_I=false;
                }
                else
                {
                    Villano_1.updateMuerte(Hro.getPosition());
                    puntaje+=50;
                }
            }

            if(Villano_2.isAlive==false)
            {
                if(Villano_2_clock_update_muerte_ACTIVADO==false)
                {
                    clock_update_muerte.restart();
                    Villano_2_clock_update_muerte_ACTIVADO=true;
                }
                if(clock_update_muerte.getElapsedTime().asSeconds()>2.0f&&Villano_2_clock_update_muerte_ACTIVADO==true)
                {


                    posicion_LEVEL_I=true;
                    posicionInicial_LEVEL_I++;
                    posicion_LEVEL_II=false;
                }
                else
                {
                    Villano_2.updateMuerte(Hro.getPosition());
                    puntaje+=50;
                }
            }

            if(posicionInicial_LEVEL_I==1)
            {
                Hro.setPosition(1435,485);
            }

            if(posicionInicial_LEVEL_II==1)
            {
                Hro.setPosition(650,1175);
            }

            if(Hro.getPosition().x>=1345&&Hro.getPosition().y<550&&Villano_1.isAlive==true)
            {
                posicion_LEVEL_I=true;
                posicion_LEVEL_II=false;
            }

            if(Hro.getPosition().y>600&&Villano_2.isAlive==true)
            {
                posicion_LEVEL_II=true;
            }


            if(Villano_1.isAlive==false&&Villano_2.isAlive==false)
            {
                if(_casiWinner==false)
                {
                    GANO.restart();
                    _casiWinner=true;
                }
                if(GANO.getElapsedTime().asSeconds()>(2.0f))
                {
                    puntaje=+200;
                    _winner=true;
                    _game_over=false;
                }
            }

//        std::cout<<"MURIO "<<_game_over<<" -- "<<"GANO "<< _winner<<std::endl;


            if(Hro.isAlive==false)
            {
                if(Hro_clock_update_muerte_ACTIVADO==false)
                {
                    clock_update_muerte.restart();
                    Hro_clock_update_muerte_ACTIVADO=true;
                }
                if(clock_update_muerte.getElapsedTime().asSeconds()>2.0f&&Hro_clock_update_muerte_ACTIVADO==true)
                {
                    _game_over=true;
                    _winner=false;
                }
                {
                    Hro.updateMuerte();
                }

            }

//            //-------------------------------------------------------------------------------
            if(num_PackFlechas == 0 && Hro.getPosition().y <= 500)
            {
                items.update(0);
            }

            if((num_PackFlechas == 0 && Hro.getPosition().y > 600)||(Villano_1.isAlive==false&&num_PackFlechas<=3))
            {
                num_PackFlechas = 4;
                items.update(4);
            }

            if(num_PackFlechas >=4 && Villano_2.isAlive==false)
            {
                num_PackFlechas = 0;
                items.update(0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {

                if(num_PackFlechas < 4)
                {
                    if (Hro.getBounds().intersects(items.getBounds()) && !items.isObtenido[num_PackFlechas])
                    {
                        std::cout << "Se sumaron 10 flechas" << std::endl;
                        items.isObtenido[num_PackFlechas] = true;
                    }
                    if (items.isObtenido[num_PackFlechas])
                    {
                        num_PackFlechas = num_PackFlechas + 1;
                        items.update(num_PackFlechas);
                        Hro.shootig->setArrow(10);
                    }
                }
                else
                {
                    if (Hro.getBounds().intersects(items.getBounds()) && !items.isObtenido[num_PackFlechas])
                    {
                        std::cout << "Se sumaron 10 flechas" << std::endl;
                        items.isObtenido[num_PackFlechas] = true;
                    }
                    if (items.isObtenido[num_PackFlechas])
                    {
                        num_PackFlechas = num_PackFlechas + 1;
                        items.update(num_PackFlechas);
                        Hro.shootig->setArrow(10);
                    }
                }
            }

//            ---------------------------------------------------------------------------------------*/
            if (Hro.getDraw().getPosition().y<650)
            {
                _current_level = LEVEL_I;
            }
            else
            {
                _current_level = LEVEL_II;
            }

/////////SETEO DE POSICION DE PERSONAJE SEGUN NIVEL

////////POSICION
            if(posicion_LEVEL_I==true)
            {
                if(Hro.getPosition().x<1435)
                {
                    Hro.setPosition(1435,Hro.getPosition().y);
                }

                if(Hro.getPosition().y>550)
                {
                    Hro.isAlive=false;
                }
            }

            if(posicion_LEVEL_II==true)
            {
                posicion_LEVEL_I=false;
                if(Hro.getPosition().y<775)
                {
                    Hro.setPosition(Hro.getPosition().x,775);
                }
            }

            floor_definition();
        }
    }
    else
    {
        std::cout<<"GAME OVER"<<std::endl;
    }
}



sf::Vector2f Game_play::get_camera_position()
{
    return  Hro.getPosition();
}

void Game_play::check_collision_platform()
{
    for (auto& Platform:Prs)
    {
        if(Hro.getDraw().getGlobalBounds().intersects(Platform.getDraw().getGlobalBounds())&&Hro.getJump_force()<0)
        {
            //std::cout<<"Check"<<std::endl;
            Hro.floor(Hro.getDraw().getPosition().x, Platform.getDraw().getGlobalBounds().top-120);
        }

        for (auto& Wolf :  _Wolf_manager._array_wolf)
        {
            if(Wolf->getBounds().intersects(Platform.getDraw().getGlobalBounds())&&Wolf->getJump_force()<0)
            {
                Wolf->floor(Wolf->getPosition().x, Platform.getDraw().getGlobalBounds().top-120);
            }
        }
    }
}


void Game_play::setNombrePlayer(std::string nombre)
{
    _namePlayer = nombre;
}
bool Game_play::getWinner()
{
    return _winner;
}

void Game_play::floor_definition()
{
    if (_current_level == LEVEL_I)
    {
        if ((Hro.getDraw().getPosition().x < 866 && Hro.getDraw().getPosition().y>485) ||
                (Hro.getDraw().getPosition().x > 1366 && Hro.getDraw().getPosition().x < 4214 && Hro.getDraw().getPosition().y>485) ||
                (Hro.getDraw().getPosition().x > 4642 && Hro.getDraw().getPosition().x < 5186 && Hro.getDraw().getPosition().y>485) ||
                (Hro.getDraw().getPosition().x > 5374 && Hro.getDraw().getPosition().x < 9584 && Hro.getDraw().getPosition().y>485) ||
                (Hro.getDraw().getPosition().x > 9754 && Hro.getDraw().getPosition().x < 10902 && Hro.getDraw().getPosition().y>485) ||
                (Hro.getDraw().getPosition().x > 11086 && Hro.getDraw().getPosition().y > 485))//485 Suelo... limite de caida
        {
            Hro.floor(Hro.getDraw().getPosition().x, 485);
        }
    }
    else if (_current_level == LEVEL_II)
    {
        if (Hro.getDraw().getPosition().y > 1210)
        {
            Hro.floor(Hro.getDraw().getPosition().x, 1210);
        }
    }

    if (_current_level == LEVEL_I)
    {
        for (auto& Wolf :  _Wolf_manager._array_wolf)
        {
            if ((Wolf->getPosition().x < 866 && Wolf->getPosition().y>485) ||
                    (Wolf->getPosition().x > 1366 && Wolf->getPosition().x < 4214 && Wolf->getPosition().y>485) ||
                    (Wolf->getPosition().x > 4642 && Wolf->getPosition().x < 5186 && Wolf->getPosition().y>485) ||
                    (Wolf->getPosition().x > 5374 && Wolf->getPosition().x < 9584 && Wolf->getPosition().y>485) ||
                    (Wolf->getPosition().x > 9754 && Wolf->getPosition().x < 10902 && Wolf->getPosition().y>485) ||
                    (Wolf->getPosition().x > 11086 && Wolf->getPosition().y > 485))//485 Suelo... limite de caida
            {
                Wolf->floor(Wolf->getPosition().x, 485);
            }
        }

    }
    else if (_current_level == LEVEL_II)
    {
        for (auto& Wolf :  _Wolf_manager._array_wolf)
        {
            if (Wolf->getPosition().y > 1210)
            {
                Wolf->floor(Wolf->getPosition().x, 1210);
            }
        }

    }
}

void Game_play::updateEnemySupGeneration()
{
    if (_Wolf_manager._array_wolf.size() < static_cast<size_t>(MAX_WOLVES))
    {
        if (_wolf_spawn_timer.getElapsedTime().asSeconds() >= 1.5) // Spawnea cada 1.5 segundos
        {
            // Genera posiciones aleatorias dentro de un rango de la pantalla
            int randomOffset = (static_cast<int>(Hro.getPosition().x) + 600)+ rand() % ((static_cast<int>(Hro.getPosition().x) + 1501)-(static_cast<int>(Hro.getPosition().x) +600));

            // Crea un nuevo lobo y lo posiciona
            Enemy_wolf* newWolf = new Enemy_wolf();
            if(_current_level==LEVEL_I)
            {
                newWolf->setPosition(randomOffset, 485);
            }
            else if(_current_level==LEVEL_I)
            {
                newWolf->setPosition(randomOffset, 1210);
            }


            // Agrega el lobo al administrador
            _Wolf_manager.Add_wolf(newWolf);

            // Reinicia el temporizador de spawn
            _wolf_spawn_timer.restart();
        }
    }

}

void Game_play::deleteEnemySup()
{
    ///DELETEO DE LOBOS
    ////recorro el array de lobos del gestor y deleteo lobos si corresponde////
    for(auto it=_Wolf_manager._array_wolf.begin(); it!=_Wolf_manager._array_wolf.end();)   //inicio el iterador IT en el principio del array y recorro hasta el final de array
    {
        Enemy_wolf* Wolf = *it;
        /*std::cout<<Wolf->deathTimer.getElapsedTime().asSeconds()<<std::endl;
        //deathTimer.restart();
        if(Wolf->getEnergy()==0||Wolf->getPosition().y>650||Wolf->getPosition().x<Hro.getPosition().x-1500)
        {
            if (Wolf->deathTimer.getElapsedTime().asSeconds() <= 0.11)
            {
                Wolf->updateDeath();
                //deathTimer.restart(); // Reinicio el temporizador de muerte
            }
            if (Wolf->deathTimer.getElapsedTime().asSeconds() > 0.11)   // Duración de la animación de muerte
            {
                delete Wolf;
                _wolf_spawn_timer.restart();
                Wolf->deathTimer.restart();
                it = _Wolf_manager._array_wolf.erase(it); // Elimino el lobo y actualizo el iterador

            }

        }
        else
        {
            ++it; //Si no se elimina el enemigo, avanza al siguiente elemento
        }*/

        std::cout<<Wolf->deathTimer.getElapsedTime().asSeconds()<<std::endl;
        if (Wolf->getEnergy() == 0 ||(Wolf->getPosition().y > 650&&_current_level==LEVEL_I)|| Wolf->getPosition().x < Hro.getPosition().x - 1500)
        {
            if (!Wolf->isDying)
            {
                Wolf->isDying = true;
                Wolf->deathTimer.restart();
            }

            if (Wolf->deathTimer.getElapsedTime().asSeconds() < 0.015f)   // Si la animación terminó
            {
                if(Wolf->getEnergy()==0)
                {
                    puntaje+=20;
                }
                std::cout<<"ok"<<std::endl;
                delete Wolf; // Elimina el objeto
                _wolf_spawn_timer.restart();
                it = _Wolf_manager._array_wolf.erase(it); // Elimina del array y actualiza el iterador
                continue; // Salta al siguiente lobo
            }
            else
            {
                Wolf->updateDeath(); // Dibuja la animación de muerte
                //Wolf->isDying = false;
            }
        }
        ++it; // Si no se elimina el enemigo, avanza al siguiente
    }


}

void Game_play::mobilityEnemySup()
{
    for (Enemy_wolf* Wolf :  _Wolf_manager._array_wolf)
    {
        Wolf->mobility(Hro.getPosition());
    }
}

void Game_play::updateEnemySup()
{
    updateEnemySupGeneration();
    deleteEnemySup();
    mobilityEnemySup();
}


