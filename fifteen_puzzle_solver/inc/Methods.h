#pragma once
#include <Contex.h>
#include <Puzzle.h>
#include <Node.h>
#include <time.h>
#include <chrono>
#include <string>
#include "Solution.h"

class Methods
{

protected:
	Contex contex;
	char* fileOutputSolution;
	char* fileAdditionalInformation;

public:
	 virtual auto run(Solution &sol) -> void = 0;
	Methods(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation);
	 virtual ~Methods();

};

