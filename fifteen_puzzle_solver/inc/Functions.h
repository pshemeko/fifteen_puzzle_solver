#pragma once
#include <cstdlib>
#include <Puzzle.h>

int metrykaHamington(std::shared_ptr<Puzzle> puz)
{
    int sum = 0;
    for (size_t i = 0; i < puz->dimensionX * puz->dimensionY; ++i)
    {
        if (puz->board[i] != i + 1)
        {

            if (puz->board[i] != 0)
            {
              sum++;
            }

        }
    }
return sum;
};

int metrykaManhattan(std::shared_ptr<Puzzle> puz)   //TODO zrobic bo liczy zle!!!!!
{
    int sum = 0;
    for (size_t i = 0; i < puz->dimensionX * puz->dimensionY; ++i)
    {
        if (puz->board[i] != i + 1) // gdy element nie jest na swoim miejscu
        {

            if (puz->board[i] != 0) // zera nie licze
            {
                //// musze znalezc gdzie jest jego docelowe miejszce i wyliczyc odleglosc
                  // licze miejsce w ktorym powinien byc
                int col = (puz->board[i]) % puz->dimensionY; // modulo ilosc kolumn wyliczy wspolrzedna x
                if (col == 0) col = 4;
                                                               // teraz wsp y
                int row = (puz->board[i]+1) / puz->dimensionY;

                // licze miejsce w ktorym jest
                int colAktual = (i+1) % puz->dimensionY;
                if (colAktual == 0) colAktual = 4;
                int rowActual = ((i+1) / puz->dimensionY);
                int ile = labs(col - colAktual) + labs(row - rowActual);
                sum += ile;
            }

        }
    }
     return sum;
};



