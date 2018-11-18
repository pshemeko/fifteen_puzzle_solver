#pragma once
#include "Methods.h"

class AStar : public Methods
{
public:

	Heuristics heuristic;

	AStar(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, Heuristics heuristic);
	
	virtual ~AStar();

	auto run(Solution &sol) -> void;
};

