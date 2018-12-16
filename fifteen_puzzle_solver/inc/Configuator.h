#pragma once
#include "Puzzle.h"
#include "MethodBFS.h"
#include "MethodDFS.h"
#include "MethodAStar.h"
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

    char* fileWithStartPuzzel;
    char* fileOutputSolution;
    char* fileAdditionalInformation;

    Strategy strategy;
    Heuristics heuristic;  // only for astar

    char* order;
    std::vector<Moves> orderEnum; 

	auto returnMethod()->Methods*;

    auto set() -> void;
	
	// tymczasowo
	//auto setForTest() -> void;
    //auto setTest() -> void;
	
};

