#pragma once
#include "Puzzle.h"
#include <vector>

class Configuator
{
	int argc;
	char** argv;

public:
	Configuator(int argc, char** argv); //  char * argv[]
	~Configuator();

    char* fileWithStartPuzzel;
    char* fileOutputSolution;
    char* fileAdditionalInformation;

    Strategy strategy;
    Heuristics heuristic;  // only for astar

    char* order;
    std::vector<Moves> orderEnum; // jedno z nich skasuj

    auto set() -> void;

};

