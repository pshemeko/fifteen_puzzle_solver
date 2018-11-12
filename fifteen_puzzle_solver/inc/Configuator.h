#pragma once
#include "Puzzle.h"
#include "MethodBFS.h"
#include "Contex.h"

#include <vector>

//ma zrobic contex oraz konkretna metode np MethodBFS

// konfiguruje z danych wejsciowych pliku i wtworzy metode do dzialania np. BFS Astar
class Configuator
{
	int argc;
	char** argv;
	Contex conteks;

public:
	Configuator(int argc, char** argv, Contex conteks); //  char * argv[]
	~Configuator();

    //tymcvzasowo do testowania
	Configuator(Contex con);

    char* fileWithStartPuzzel;
    char* fileOutputSolution;
    char* fileAdditionalInformation;

    Strategy strategy;
    Heuristics heuristic;  // only for astar

    char* order;
    std::vector<Moves> orderEnum; // jedno z nich skasuj

    auto set() -> void;

    // tymczasowo

    auto setTest() -> void;

	auto returnMethod()-> Methods*;
 
};

