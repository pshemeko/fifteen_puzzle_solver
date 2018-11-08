#include "pch.h"
#include "MethodBFS.h"


MethodBFS::MethodBFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum)
	:Methods(contex, fileOutputSolution, fileAdditionalInformation), order{orderEnum}
{
}

MethodBFS::~MethodBFS()
{
}


auto MethodBFS::run() -> void
{
	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle(); 

	int a = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia

	//std::list<> frontier;
	//std:list<> explored;

}
