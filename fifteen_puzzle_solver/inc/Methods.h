#pragma once
#include <Contex.h>

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

