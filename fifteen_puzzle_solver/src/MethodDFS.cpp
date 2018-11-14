#include "pch.h"
#include "MethodDFS.h"

#include <stack>
#include <unordered_set>

using namespace std;

MethodDFS::MethodDFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum)
    :Methods(contex, fileOutputSolution, fileAdditionalInformation), order{ orderEnum }
{
}


MethodDFS::~MethodDFS()
{
}

auto MethodDFS::run(Solution &solution) -> void //Nowy jako drugi robilem
{



	std::cout << "\n" << (Moves::Down) << "    i co teraz!!!\nkolejnosc:";
	for (auto x : order) cout << x << " ";
	cout << endl << "!!!!!!!!!!!!!  DFS !!!!!!!!!!!!!";

	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	std::cout << "\n MethodBFS fcja run Puzel Poczatkowy:";
	std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
	//int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia

						//std::list<std::shared_ptr<Node>> frontier;
//std::list<std::shared_ptr<Node>> frontier;
//std::list<std::shared_ptr<Node>> explored;

	auto frontier = std::stack<std::shared_ptr<Node>>{};
	auto explored = std::unordered_set<std::size_t>{};

	//jako ze wrzucam w odwrotnej kolejnosci trzba odwroic w tej metodzie
	std::reverse(std::begin(order), std::end(order));


	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
																	  //Puzzle father = *root->puzel;
	//frontier.push_back(root);
	frontier.push(root);

	std::shared_ptr<Node> father = root;

	std::shared_ptr<Node> solvedNode = root;
	bool stillRun = true;
	//bool notFoundSolution = false;
	int iii = 5;
	cout << "\nKOLEJNOSC WRZUCANA:";
	for (auto x : order) cout << x << " ";

	//while (iii--) 
	//while(stillRun)
	while (stillRun)
	{
		cout << " iii:" << iii << endl;

		// zdejmuje czowke i wrzucam do explored i przetwarzam ja teraz
		father = frontier.top();
		explored.insert(father->puzel->hasHFunction());
		frontier.pop();
		cout << "-------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl;
		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == father->recursionDeph)
		{
			//stillRun = false;
			cout << "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";
			cout << "\n********************************************************************************************************************************************";
			continue;
		}

		for (auto mov : order)
		{
			Puzzle puzelek = *father->puzel;

			if (puzelek.MoveZero(mov))
			{
				std::shared_ptr<Puzzle> copy = std::make_shared<Puzzle>(puzelek);

				std::shared_ptr<Node> nod = std::make_shared<Node>(father, copy, mov, (father->recursionDeph) + 1);

				if (nod->puzel->IsOnFinishState())
				{
					cout << "\nkoncowy puzel:";
					cout << *nod->puzel;
					std::cout << " \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";
					std::cout << "\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";
					solvedNode = nod;
					//puzelKoncowy = puzelek;
					stillRun = false;
					frontier.push(nod);

					break; // wyskakuje z while
				}
				bool czyJuzJest = false;

				auto hash = nod->puzel->hasHFunction();

				if (explored.find(hash) != std::end(explored))
				{
					cout << "\nISTNIEJE JUZ HASH w explored: " << hash;
					czyJuzJest = true;
				}

				// czy potrzeba tez w frontiered sprawdzic?
				/*
				if (!czyJuzJest) // ale trzeba zmienic wtedy stack na list
				{

					for (auto x : frontier)
					{
						if ((x->puzel->hasHFunction()) == nod->puzel->hasHFunction())
						{
							czyJuzJest = true;
							//if (  *nod.get() == *x.get()) czyJuzJest = true;
							std::cout << "\n\t\t\t\tjest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
							break;
						}
					}

				}
				*/
				if (!czyJuzJest)
				{
					frontier.push(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)

					std::cout << "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :"; //(*father->puzel).hasHFunction() << std::endl;
					cout << *nod->puzel << endl;
				}




			}

			if (!stillRun) break; // przenosze braeak dalej

		}



	}

	//******************************** WYSWIETLANIE 


	//jako ze wrzucam w odwrotnej kolejnosci trzba odwroic jkeszcze raz by do wynikow dac dobra kolejnosc
	std::reverse(std::begin(order), std::end(order));


	////kopiuje

	std::list<Moves> listMoves;
	if (!frontier.empty())	// nie znaleziono rozwiazania
	{

		bool oneMore = true;
		std::shared_ptr <Node> wezel = solvedNode;
		while (oneMore)
		{
			listMoves.push_back(wezel->operatorUsed);
			//std::cout << "\noneMore:" << oneMore << " operator:" << wezel->operatorUsed;
			wezel = wezel->parrent;
			if (wezel->parrent == nullptr) oneMore = false;			//TODO ******************************************* blad
		}
		cout << "\t\t size listrevert:" << listMoves.size();
		// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania

		//std::list<Moves> listMoves;
		//for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
		//{
		//	listMoves.push_back(*it);
		//}

		std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste


	}

	solution.fileSolution << "glebokosc:" << solvedNode->recursionDeph << std::endl;
	std::cout << "\nglebokosc:" << solvedNode->recursionDeph << std::endl;

	if (!frontier.empty())//if (!frontier.empty()&& stillRun ==false)
	{
		for (auto x : listMoves)
		{
			solution.fileSolution << x << " ";
			std::cout << x << " ";
		}

	}
	else
	{
		solution.fileSolution << -1;
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";
	}
	//std::cout << *wezelKoncowy->puzel.get();



	// *********************************************      zbieranie wynikow

	solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeStart);

	solution.length_of_the_solution_found = listMoves.size();
	solution.number_of_visited_states = frontier.size() + explored.size();
	solution.number_of_processed_states = explored.size();
	////?????????TODO czy to jest dobrze?
	solution.maximum_depth_of_recursion_achieved = solvedNode->recursionDeph;
	if (!listMoves.empty())
	{
		for (auto x : listMoves)
		{
			if (x == Moves::Down)	solution.solution += "D";
			if (x == Moves::Up)		solution.solution += "U";
			if (x == Moves::Left)	solution.solution += "L";
			if (x == Moves::Right)	solution.solution += "R";
		}
	}
	else
	{
		solution.solution = "-1";
	}
    cout << "\n\n\n\n ***************************************   podsumowanie wynikow programu";

    cout << endl << endl << endl << endl << "Puzel poczatkowy:\n";
    std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
    cout << "\nPuzel koncowy:";
    std::cout << *solvedNode->puzel << " jego hash: " << solvedNode->puzel->hasHFunction() << std::endl;


    cout << "\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count();
    cout << "\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;
    cout << "\n Operatory uzyte: " << solution.solution;
    cout << "\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;
    cout << "\n liczba stanow przetworzonych: " << solution.number_of_processed_states;
    cout << endl;
    //solution.save();
}
//TODO jeszcze trzeba sprawdzac stany przetworzone czy nie ma elementu
// przerobic frontier na liste i sprawdzac czy nie ma tam elementu tez