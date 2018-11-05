#pragma once
#include "Puzzle.h"

class Configuator
{
	int argc;
	char** argv;

public:
	Configuator(int argc, char** argv); //  char * argv[]
	~Configuator();
};

