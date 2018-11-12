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

	using namespace std;
	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();
	std::cout << "\n MethodBFS fcja run Puzel Poczatkowy:";
	std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() <<std::endl;
	int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia

	//std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
	//Puzzle father = *root->puzel;

	std::shared_ptr<Node> father = root;
	////// od tad petla

	int ile = 0;// MAXIMUM_PERMITTED_RECURSION_DEPTH;
	bool stillRun = true;
	//Puzzle puzelKoncowy = *startPuzzel.get();
	std::shared_ptr<Node> wezelKoncowy = root;
	while (stillRun)
	{
		std::cout << "\t\t\t\t\t\t\t\t\t\tstill run: " << stillRun << std::endl;
		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == ile) stillRun = false;

		for (auto mov : order)
		{
			
			Puzzle puzelek = *father->puzel.get();
			//std::shared_ptr<Puzzle> puz = father->puzel;
			bool zmienil = puzelek.MoveZero(mov);		//TODO tu trzeba przerwac bo nie mozna zrobic ruchu
			
			if (zmienil)
				{

					cout << "czy zmienil plozenie zera " << zmienil << " z ruchem" << mov;
					cout << puzelek; 
					std::shared_ptr<Puzzle> kopia = std::make_shared<Puzzle>(puzelek);

					std::shared_ptr<Node> nod = std::make_shared<Node>(father, kopia, mov);
					////sprawdz czy jest docelowy
					if (nod->puzel->IsOnFinishState()) {
						std::cout << " \n teraz uruchomil sie break";
						wezelKoncowy = nod;
						//puzelKoncowy = puzelek;
						stillRun = false;
						frontier.push_back(nod);

						break;
					}
					//////////////////////////TO DO  sprawdz czy dziala break jak docelowy to koniec moze lepiej goto;
					bool czyJuzJest = false;


					for (auto x : frontier)
					{
						//Node d = *x.get(); 
						//Puzzle pp = *x->puzel; 

						if ((x->puzel->hasHFunction()) == nod->puzel->hasHFunction())
						{
							czyJuzJest = true;
							//if (  *nod.get() == *x.get()) czyJuzJest = true;
							std::cout << "jest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
						}
					}
					if (!czyJuzJest)
					{
						frontier.push_back(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)

						std::cout << "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << std::endl; //(*father->puzel).hasHFunction() << std::endl;
					}


				}
		}
		//teraz biore pierwszy i przetwarzam
		
		father = frontier.front();
		explored.push_back(father);
		frontier.pop_front();
		ile++;
		std::cout << "\n koniec for:" << ile;
	}
	std::cout << "\n wyszlo z while" <<" ile:" << ile;
	// teraz sprawdzanie i podawanie wynikow
	//moze zrobic klase do tego


	//******************************** WYSWIETLANIE 

	std::list<Moves> listMovesRevert;
	bool oneMore = true;
	while (oneMore)
	{
		listMovesRevert.push_back(father->operatorUsed);
		father = father->parrent;
		std::cout << "\noneMore:" << oneMore << " operator:" << father->operatorUsed;
		if (father->parrent == nullptr) oneMore = false;
	}
	cout <<  "\t\t size listrevert:" << listMovesRevert.size();
	// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania
	
	std::list<Moves> listMoves;
	for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
	{
		listMoves.push_back(*it);
	}

	solution.fileSolution << "glebokosc:" << ile << std::endl;
	std::cout << "\nglebokosc:" << ile << std::endl;

	for(auto x : listMoves)
	{
		solution.fileSolution << x <<" ";
		std::cout << x << " ";
	}

	std::cout << *wezelKoncowy->puzel.get();
	


}
