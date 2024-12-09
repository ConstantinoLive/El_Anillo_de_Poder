#ifndef AUDIO_H
#define AUDIO_H
#include <iostream>
#include <SFML/Audio.hpp>

class Audio
{
    public:
        Audio(int opc);
        virtual ~Audio();
        void audioON();
        void audioOFF();

    protected:

    private:
        int _opcion_musica;
        sf::Music musica;
        sf::SoundBuffer buffer1;
        sf::SoundBuffer buffer3;
        sf::Music _audio_menu;


};

#endif // AUDIO_H
