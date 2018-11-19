#pragma once
#include "Methods.h"
#include <cstdlib>

class MethodAStar : public Methods
{
public:

	Heuristics heuristic;


	MethodAStar(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, Heuristics heuristic);

	virtual ~MethodAStar();

	auto run(Solution &sol) -> void;
};
