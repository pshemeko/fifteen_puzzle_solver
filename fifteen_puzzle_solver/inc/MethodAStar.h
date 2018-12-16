#pragma once
#include "Methods.h"
#include <cstdlib>

class MethodAStar : public Methods
{
    std::vector<Moves> order;
public:

	Heuristics heuristic;

	MethodAStar(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, Heuristics heuristic, std::vector<Moves> orderEnum);

	virtual ~MethodAStar();

	auto run(Solution &sol) -> void;
};
