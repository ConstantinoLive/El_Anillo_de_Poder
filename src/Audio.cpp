#include "Audio.h"

Audio::Audio(int opc)
{
    _opcion_musica=opc;

    if(_opcion_musica==1)
    {
        //Musica de fondo
        if(!musica.openFromFile("Audio/winning-loop-228639.wav"))
        {
            std::cout << "Error al cargar sonido" << std::endl;
            return;
        }
            musica.setLoop(true);
    }

        else
        {
            //Menu
            if(_opcion_musica==3)
            {
                if(!_audio_menu.openFromFile("Audio/medieval-bell-d3-90290.wav"))
                {
                    std::cout << "Error al cargar sonido" << std::endl;
                    return;
                }
            }
                    }
                }

Audio::~Audio()
{
    //dtor
}

void Audio::audioON()
{
    if(_opcion_musica==1)
    {
        //Musica de fondo
        musica.play();
    }
    else
    {
        //Menu
            if(_opcion_musica==3)
            {
                _audio_menu.play();
            }

        }
    }


void Audio::audioOFF()
{
    if(_opcion_musica==1)
    {
        //Musica de fondo
        musica.stop();
    }

        else
        {
            //Menu
            if(_opcion_musica==3)
            {
                _audio_menu.stop();
            }

            }
        }

