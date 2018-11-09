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

	int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia
        
	std::list<Node> frontier;
	std::list<Node> explored;

    std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel

    for (auto mov : order)
    {
        Puzzle puz = *root->puzel;
        puz.MoveZero(mov);
        std::cout << "puz nowy ma hash" << puz.hasHFunction() << "  root stary ma hash: " << (*root->puzel).hasHFunction() << std::endl ;

        //std::shared_ptr<Puzzle> newest = root->puzel;


    }


}
