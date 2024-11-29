#include<iostream>

#include "Partida.h"

Partida::Partida()
{
    strcpy(_nombre, "Player");
    _puntos = 0;
}
Partida::Partida(int puntaje, std::string nombre)
{
    _puntos = puntaje;
    strcpy(_nombre, nombre.c_str());

}

Partida::~Partida()
{
    //dtor
}

std::string Partida::getName() const
{
    return _nombre;
}

void Partida::setName(std::string nombre)
{
    strcpy(_nombre, nombre.c_str());

}

int Partida::getPuntos() //const
{
    return _puntos;
}

void Partida::setPuntos(int puntaje)
{
    _puntos = puntaje;
}

int Partida::contarPartidas()
{
    FILE *p;
    p=fopen("Partidas.dat", "rb");
    if(p==NULL) return -1;
    fseek(p, 0,SEEK_END);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Partida);
}

void Partida::mostrarPlayer()
{
    Partida reg;
    Partida auxOrdenar;

    int cantReg = contarPartidas();
    Partida *vec = new Partida[cantReg];
    if (vec == NULL)
    {
        std::cout << "No hay memoria suficiente.";
        return;
    }

    FILE *p=fopen("Partidas.dat", "rb");
    if(p==NULL)
    {
        std::cout<<"no se pudo abrir"<<std::endl;
        delete[]vec;
        return;
    }
    int x =0;

    while(fread(&reg, sizeof(Partida), 1, p)==1)
    {
        vec[x].setName(reg.getName());
        vec[x].setPuntos(reg.getPuntos());
        x++;
    }
    fclose(p);
    for(int i =0; i<cantReg-1; i++)
    {
        for(int j =0; j<cantReg-i-1; j++)
        {
            if (vec[j].getPuntos()< vec[j+1].getPuntos())
            {
                auxOrdenar = vec[j];
                vec[j] = vec[j+1];
                vec[j+1]= auxOrdenar;
            }
        }
    }

    delete[] vec;

}

