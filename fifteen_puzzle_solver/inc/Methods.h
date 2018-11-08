#pragma once
#include <Contex.h>
#include <Puzzle.h>
#include <Node.h>

class Methods
{

protected:
	Contex contex;
	char* fileOutputSolution;
	char* fileAdditionalInformation;

public:
	virtual auto run() -> void = 0;
	Methods(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation);
	virtual ~Methods();

};

