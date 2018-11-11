#pragma once
#include "Methods.h"
class MethodBFS : 	public Methods
{
	std::vector<Moves> order; // np. LRUD, LURD kolejnosc przeszukian
public:
	 virtual auto run(Solution &solution) -> void;

	MethodBFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum);
	virtual ~MethodBFS();
};

