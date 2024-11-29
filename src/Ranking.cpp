#include "Ranking.h"

Ranking::Ranking()
{
    //ctor
}

Ranking::~Ranking()
{
    //dtor
}

void Ranking::setRanking()
{

    Partida reg;
    Partida auxOrdenar;

    for(int i=0; i<10; i++)
    {
        _partidas[i].setName("Player");
        _partidas[i].setPuntos(0);
    }


    int cantReg = reg.contarPartidas();
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
    ///aca se ordena
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
    }///cargo vector de jugadores con puntos
    ///desde aca

    ///

    for(int i=0; i<cantReg; i++) ///Cargamos vector de partidas, que se compone de nombre y puntos
    {
        _partidas[i]=vec[i];
        if(i>9)
            break;  ///salis del for

    }


    delete[] vec;


}

Partida* Ranking::getRanking()
{
    return _partidas;
}
