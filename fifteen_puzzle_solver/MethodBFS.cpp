#include "pch.h"
#include "MethodBFS.h"


auto MethodBFS::run() -> void
{
	//TODO  zaimplementoac caly algorytm
	contex.start.get(); // pobranie sartowego puzla

}

MethodBFS::MethodBFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum)
	:Methods(contex, fileOutputSolution, fileAdditionalInformation), order{orderEnum}
{
}

MethodBFS::~MethodBFS()
{
}


