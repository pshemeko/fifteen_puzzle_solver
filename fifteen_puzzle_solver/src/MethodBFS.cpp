#include "pch.h"
#include "MethodBFS.h"
#include <queue>


MethodBFS::MethodBFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum)
	:Methods(contex, fileOutputSolution, fileAdditionalInformation), order{orderEnum}
{
}

MethodBFS::~MethodBFS()
{
}


auto MethodBFS::run(Solution &solution) -> void
{
	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia

	//std::list<std::shared_ptr<Node>> frontier;
	std::queue<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
	//Puzzle father = *root->puzel;

	std::shared_ptr<Node> father = root;
	////// od tad petla

	int ile = 0;// MAXIMUM_PERMITTED_RECURSION_DEPTH;
	while (ile != MAXIMUM_PERMITTED_RECURSION_DEPTH)
	{
		
		for (auto mov : order)
		{
			std::shared_ptr<Puzzle> puz = father->puzel;
			puz->MoveZero(mov);
			std::shared_ptr<Node> nod = std::make_shared<Node>(father, puz, mov);
			////sprawdz czy jest docelowy
			if (nod->puzel->IsOnFinishState()) break;  //////////////////////////TO DO  sprawdz czy dziala break jak docelowy to koniec moze lepiej goto;
			frontier.push(nod);

			std::cout << "puz nowy ma hash" << puz->hasHFunction() << "  root stary ma hash: " << (*root->puzel).hasHFunction() << std::endl;

		}
		//teraz biore pierwszy i przetwarzam

		father = frontier.front();
		explored.push_back(father);
		frontier.pop();
		ile++;
	}

	// teraz sprawdzanie i podawanie wynikow
	//moze zrobic klase do tego
	std::list<Moves> listMovesRevert;
	bool oneMore = true;
	while (oneMore)
	{
		listMovesRevert.push_back(father->operatorUsed);
		father = father->parrent;
		if (father->parrent == nullptr) oneMore = false;
	}
	// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania
	std::list<Moves> listMoves;
	for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
	{
		listMoves.push_back(*it);
	}

	solution.fileSolution << "glebokosc:" << ile << std::endl;

	for(auto x : listMoves)
	{
		solution.fileSolution << x <<" ";
	}
	


}
