#ifndef RANKING_H
#define RANKING_H

#include <iostream>

#include "Partida.h"

class Ranking
{
    public:
        Ranking();
        virtual ~Ranking();

        void setRanking();
        Partida* getRanking();

    private:
        Partida _partidas[10];
};

#endif // RANKING_H
