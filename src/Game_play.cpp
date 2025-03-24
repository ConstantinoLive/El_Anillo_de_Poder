#include "Game_play.h"

Game_play::Game_play(sf::RenderWindow& window,Player& player)
{

    num_PackFlechas=0;
    i=0;
    _states=STATES_GAME_PLAY::ACTION;
    _current_level = LEVEL_I;
    clock.restart();
    //Superficie
    Prs[0]=Platforms_rectangle_shape(508,846,355);      //355
    Prs[1]=Platforms_rectangle_shape(264,1466,195);     //195
    Prs[2]=Platforms_rectangle_shape(388,1750,325);     //325
    Prs[3]=Platforms_rectangle_shape(274,4292,365);     //365
    Prs[4]=Platforms_rectangle_shape(495,4638,195);     //195
    Prs[5]=Platforms_rectangle_shape(156,5195,365);     //365
    Prs[6]=Platforms_rectangle_shape(380,5578,195);     //195
    Prs[7]=Platforms_rectangle_shape(508,6406,341);     //341
    Prs[8]=Platforms_rectangle_shape(272,7942,302);     //302
    Prs[9]=Platforms_rectangle_shape(264,9170,317);     //317
    Prs[10]=Platforms_rectangle_shape(264,9584,170);    //170
    Prs[11]=Platforms_rectangle_shape(500,10008,307);   //307
    Prs[12]=Platforms_rectangle_shape(505,10680,177);   //177

    //Cueva
    Prs[13]=Platforms_rectangle_shape(80,35,950+p);       //950
    Prs[14]=Platforms_rectangle_shape (312, 236,1053+p);  //1053
    Prs[15]=Platforms_rectangle_shape(108,1740,1105+p);   //1105
    Prs[16]=Platforms_rectangle_shape(528,1890,980+p);    //980
    Prs[17]=Platforms_rectangle_shape(105,2642,897+p);    //897
    Prs[18]=Platforms_rectangle_shape(105,4978,957+p);    //957
    Prs[19]=Platforms_rectangle_shape(105,5154,1070+p);   //1070
    Prs[20]=Platforms_rectangle_shape(105,5780,1070+p);   //1070
    Prs[21]=Platforms_rectangle_shape(440,6010,975+p);    //975
    Prs[22]=Platforms_rectangle_shape(188,6608,1055+p);   //1055
    Prs[23]=Platforms_rectangle_shape(105,8044,1105+p);   //1105
    Prs[24]=Platforms_rectangle_shape(105,8276,985+p);    //985
    Prs[25]=Platforms_rectangle_shape(444,8544,910+p);    //910
    Prs[26]=Platforms_rectangle_shape(180,9116,985+p);    //985
    Prs[27]=Platforms_rectangle_shape(105,9447,910+p);    //910
    Prs[28]=Platforms_rectangle_shape(105,9624,1085+p);   //1085
    Prs[29]=Platforms_rectangle_shape(460,9844,990+p);    //990
    Prs[30]=Platforms_rectangle_shape(105,10444,1075+p);  //1075
    Prs[31]=Platforms_rectangle_shape(105,11176,1080+p);  //1080
    Prs[32]=Platforms_rectangle_shape(404,11404,970+p);   //970
    Prs[33]=Platforms_rectangle_shape(105,11962,870+p);   //870
    Prs[34]=Platforms_rectangle_shape(228,12132,1025+p);  //1025

   // Prs[35]=Platforms_rectangle_shape(13000,4000,700);//foza

    _wolf_spawn_timer.restart();

    _namePlayer = player.getNombre();

}

Game_play::~Game_play()
{

}

void Game_play::draw(sf::RenderWindow& window)
{
    window.draw(BG.getDraw());
    window.draw(Pltfm.getDraw());
    window.draw(Msg);
    if(Hro.getd_r()==false)
    {
        window.draw(Hro.getDraw());
    }



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
        window.draw(*Wolf);
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
        window.draw(Hud_game);
    }
}

void Game_play::cmd()
{


    if(_states==STATES_GAME_PLAY::ACTION)
    {
        check_collision_platform();

        Hud_game.mobility(Hro.getPosition(),get_camera_position());

        colisionables.anillosColision(Hro, anillos);
        if(anillos.isObtenido())
        {
            if(colisionables.getSilver()==true&&colisionables.getGold()==false)
            {
                Msg.mobility(anillos.getPosition(),true);
            }
            else if(colisionables.getSilver()==false&&colisionables.getGold()==true)
            {
                Msg.mobility(anillos.getPosition(),false);
            }
            else
            {
                colisionables.setGold(false);
                colisionables.setSilver(false);
            }
        }

        colisionables.colisionFlechasConVillanos(Hro, Villano_1, Villano_2, death, dying);
        colisionables.colisionHeroConVillanos(Hro, Villano_1, Villano_2, death, dying, attack);
        colisionables.colisionSauronConHro(Villano_2,Hro, death);
        colisionables.colisionMagoConHero(Villano_1, Hro, death);
        colisionables.colisionHeroConWolf(Hro,_Wolf_manager,attack,dying);
        colisionables.colisionFlechasWolf(Hro,_Wolf_manager,dying);
        colisionables.colisionWolfConHero(Hro,_Wolf_manager,dying);

        Msg.update();

        Hro.mobility();

        Villano_1.mobility(Hro.getPosition(),Hro.getEstado());

        Villano_2.mobility(Hro.getPosition(),Hro.getEstado());


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
        BG.update();

        sf::Time deltaTime = clock.restart(); // Reinicia el reloj y obtiene el tiempo transcurrido



        if(_states==STATES_GAME_PLAY::ACTION)
        {
            Hro.update();

            Hud_game.update(_namePlayer, Hro.getEnergia(),Hro.getVida(),puntaje,Hro.shootig->getArrow());

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

           /* if(posicionInicial_LEVEL_I==1)
            {
                Hro.setPosition(1435,FLOOR_I);
            }

            if(posicionInicial_LEVEL_II==1)
            {
                Hro.setPosition(650,FLOOR_II);//1175
            }*/

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
                    puntaje+=200;
                    _winner=true;
                    _game_over=false;
                }
            }

            if(Hro.getVida()<=0)
            {
                if(Hro_clock_update_muerte_ACTIVADO==false)
                {
                    clock_update_muerte.restart();
                    Hro_clock_update_muerte_ACTIVADO=true;
                }
                if(clock_update_muerte.getElapsedTime().asSeconds()>1.0f&&Hro_clock_update_muerte_ACTIVADO==true)
                {
                    _game_over=true;
                    _winner=false;
                }


            }




            //-------------------------------------------------------------------------------
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
            //---------------------------------------------------------------------------------------*/

            ////////POSICION
            if(posicion_LEVEL_I==true)
            {
                _current_level = LEVEL_I;
                posicion_LEVEL_II=false;
                if(Hro.getPosition().x<1435)
                {
                    Hro.setPosition(1435,Hro.getPosition().y);
                }

                if(Hro.getDraw().getPosition().x > 1366 && Hro.getPosition().y>550)
                {
                    Hro.isAlive=false;
                    Hro.isFallen=true;
                }
            }

            if(posicion_LEVEL_II==true)
            {
                _current_level = LEVEL_II;
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
    sf::Vector2f pos;

    if(Hro.isFallen==true&&Hro.isAlive==false)
    {
        pos= {Hro.getPosition().x,FLOOR_I};
        return  pos;
    }
    else if(Hro.getPosition().y<1260&&Hro.getPosition().y>550)
    {
        pos= {Hro.getPosition().x,1260};
        return  pos;
    }
    else
    {
        pos= {Hro.getPosition().x,Hro.getPosition().y};
        return  pos;
    }
}

void Game_play::check_collision_platform()
{
    for (auto& Platform:Prs)
    {
        if(Hro.getDraw().getGlobalBounds().intersects(Platform.getDraw().getGlobalBounds())&&Hro.getJump_force()<0)
        {
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
        if ((Hro.getDraw().getPosition().x < 866 && Hro.getDraw().getPosition().y>FLOOR_I) ||
                (Hro.getDraw().getPosition().x > 1366 && Hro.getDraw().getPosition().x < 4214 && Hro.getDraw().getPosition().y>FLOOR_I) ||
                (Hro.getDraw().getPosition().x > 4642 && Hro.getDraw().getPosition().x < 5186 && Hro.getDraw().getPosition().y>FLOOR_I) ||
                (Hro.getDraw().getPosition().x > 5374 && Hro.getDraw().getPosition().x < 9584 && Hro.getDraw().getPosition().y>FLOOR_I) ||
                (Hro.getDraw().getPosition().x > 9754 && Hro.getDraw().getPosition().x < 10902 && Hro.getDraw().getPosition().y>FLOOR_I) ||
                (Hro.getDraw().getPosition().x > 11086 && Hro.getDraw().getPosition().y > FLOOR_I))//485 Suelo... limite de caida
        {
            Hro.floor(Hro.getDraw().getPosition().x, FLOOR_I);
        }
    }
    else if (_current_level == LEVEL_II)
    {
        if (Hro.getDraw().getPosition().y > FLOOR_II)
        {
            Hro.floor(Hro.getDraw().getPosition().x, FLOOR_II);
        }
    }

    if (_current_level == LEVEL_I)
    {
        for (auto& Wolf :  _Wolf_manager._array_wolf)
        {
            if ((Wolf->getPosition().x < 866 && Wolf->getPosition().y>FLOOR_I) ||
                    (Wolf->getPosition().x > 1366 && Wolf->getPosition().x < 4214 && Wolf->getPosition().y>FLOOR_I) ||
                    (Wolf->getPosition().x > 4642 && Wolf->getPosition().x < 5186 && Wolf->getPosition().y>FLOOR_I) ||
                    (Wolf->getPosition().x > 5374 && Wolf->getPosition().x < 9584 && Wolf->getPosition().y>FLOOR_I) ||
                    (Wolf->getPosition().x > 9754 && Wolf->getPosition().x < 10902 && Wolf->getPosition().y>FLOOR_I) ||
                    (Wolf->getPosition().x > 11086 && Wolf->getPosition().y > FLOOR_I))//485 Suelo... limite de caida
            {
                Wolf->floor(Wolf->getPosition().x, FLOOR_I);
            }
        }

    }
    else if (_current_level == LEVEL_II)
    {
        for (auto& Wolf :  _Wolf_manager._array_wolf)
        {
            if (Wolf->getPosition().y > FLOOR_II)
            {
                Wolf->floor(Wolf->getPosition().x, FLOOR_II);
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
                newWolf->setPosition(randomOffset, FLOOR_I);
            }
            else if(_current_level==LEVEL_II)
            {
                newWolf->setPosition(randomOffset, FLOOR_II);
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
        if ((Wolf->isDying == true||(Wolf->getPosition().y > 550&&_current_level==LEVEL_I)|| Wolf->getPosition().x < Hro.getPosition().x - 1500))
        {
            if(Wolf->isDying==true)
            {
                puntaje+=20;
            }
            delete Wolf; // Elimina el objeto
            _wolf_spawn_timer.restart();
            it = _Wolf_manager._array_wolf.erase(it); // Elimina del array y actualiza el iterador
            continue; // Salta al siguiente lobo
        }
        ++it; // Si no se elimina el enemigo, avanza al siguiente
    }

}

void Game_play::mobilityEnemySup()
{
    for (Enemy_wolf* Wolf :  _Wolf_manager._array_wolf)
    {
        Wolf->mobility(Hro.getPosition(),Hro.getEstado());
    }
}

void Game_play::updateEnemySup()
{
    updateEnemySupGeneration();
    mobilityEnemySup();
    deleteEnemySup();
}


