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
        
	std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

    std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
    //Puzzle father = *root->puzel;

    std::shared_ptr<Node> father = root;
    ////// od tad petla


    for (auto mov : order)
    {
        std::shared_ptr<Puzzle> puz = father->puzel;
        puz->MoveZero(mov);
        std::shared_ptr<Node> nod = std::make_shared<Node>(father, puz, mov);
        frontier.push_back(nod);

        std::cout << "puz nowy ma hash" << puz->hasHFunction() << "  root stary ma hash: " << (*root->puzel).hasHFunction() << std::endl ;

    }
    //teraz biore pierwszy i przetwarzam

    father = frontier.front();
    explored.push_back(father);
    frontier.pop_front();

}
