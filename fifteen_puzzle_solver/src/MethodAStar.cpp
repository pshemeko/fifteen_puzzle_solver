#include "pch.h"
#include "MethodAStar.h"
#include "Functions.h"

//#define SHOW_PUZZEL(msg)
//#define SHOW_INFO(msg)
//#define SHOW_DEBUG(msg)

#ifndef SHOW_PUZZEL
#define SHOW_PUZZEL(msg) std::cout<< msg
#endif // !SHOW

#ifndef SHOW_INFO
#define SHOW_INFO(msg) std::cout<< msg
#endif // !SHOW_INFO

#ifndef SHOW_DEBUG
#define SHOW_DEBUG(msg) std::cout<< msg
#endif // !SHOW_DEBUG


MethodAStar::MethodAStar(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, Heuristics heuristic)
	:Methods(contex, fileOutputSolution, fileAdditionalInformation), heuristic{ heuristic }
{
}


MethodAStar::~MethodAStar()
{
}

// TODO Zrobic jako wskaznik na funcje i 2 funkcje
auto MethodAStar::run(Solution &sol) -> void
{
 
    // wskazniki na funkcje zwracajace int i pobierajaca puzla
    heuristic;
    int(*wskaznikNaFunkcje)(std::shared_ptr<Puzzle> puz);
	if (heuristic == Heuristics::hamm)
	{
		wskaznikNaFunkcje = &metrykaHamington;
	}
	else if (heuristic == Heuristics::manh)
	{
		wskaznikNaFunkcje = &metrykaManhattan;
	}
	else wskaznikNaFunkcje = &metrykaNieznana;
 

	using namespace std;

	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	int MaxDepth = 0;

	cout << endl << "\n**************************************  ASTAR **************************************\n";

	SHOW_PUZZEL("Puzel Poczatkowy:" << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;)

	std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
	//Puzzle father = *root->puzel;
	frontier.push_back(root);

	std::shared_ptr<Node> father = root;

	int ile = 0;// MAXIMUM_PERMITTED_RECURSION_DEPTH;
	bool stillRun = true;
	//Puzzle puzelKoncowy = *startPuzzel.get();
	std::shared_ptr<Node> wezelKoncowy = root;
	SHOW_DEBUG("\nwielkosc frontier w A* przed while:" << frontier.size(););
    
    int zFunckcji = (*wskaznikNaFunkcje)(startPuzzel);
    ///////////////////
	if (heuristic == Heuristics::hamm) SHOW_DEBUG("\n Hamilton, ";);
	if (heuristic == Heuristics::manh) SHOW_DEBUG("\n Manhatan, ";);
	SHOW_DEBUG(" wartosc funkcji: " << zFunckcji << endl;);
    
	
	cout << endl << *startPuzzel << endl;


	//while (stillRun && !frontier.empty())
	//{



	//}




}