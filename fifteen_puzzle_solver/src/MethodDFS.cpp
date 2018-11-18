#include "pch.h"
#include "MethodDFS.h"

#include <stack>
#include <unordered_set>

#define SHOW_PUZZEL(msg)
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


	SHOW_DEBUG("\n" << (Moves::Down) << "    i co teraz!!!\nkolejnosc:";);
	//std::cout << "\n" << (Moves::Down) << "    i co teraz!!!\nkolejnosc:";
	for (auto x : order) SHOW_DEBUG(x << " ";);
	//for (auto x : order) cout << x << " ";

	cout << endl << "\n**************************************  DFS **************************************\n";
	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

	int MaxDepth = 0;

	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();
	SHOW_PUZZEL("\n MethodBFS fcja run Puzel Poczatkowy:";);
	//std::cout << "\n MethodBFS fcja run Puzel Poczatkowy:";
	SHOW_PUZZEL(*startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;);
	//std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
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
	//int iii = 5;
	SHOW_DEBUG("\nKOLEJNOSC WRZUCANA:";);
	//cout << "\nKOLEJNOSC WRZUCANA:";
	//for (auto x : order) cout << x << " ";
	for (auto x : order) SHOW_DEBUG(x << " ";);

	//while(stillRun)
    SHOW_DEBUG("\nwielkos frontier w DFS przed while:" << frontier.size(););
	while (stillRun && !frontier.empty()) // TODO jak zle zostaw samo stillRun
	{
        SHOW_DEBUG("\nwielkows frontier  w while:" << frontier.size(););

		// zdejmuje czowke i wrzucam do explored i przetwarzam ja teraz
		father = frontier.top();
		explored.insert(father->puzel->hasHFunction());
		frontier.pop();

		SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hasHFunction() << "\twielkosc frontier w while:" << frontier.size(););

		if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;

		SHOW_INFO("---------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl;);
		//cout << "-------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl;
		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == father->recursionDeph)
		{
			//stillRun = false;
			SHOW_DEBUG("\n\t\t\t\t************** PRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";);
			//cout << "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";
			//cout << "\n********************************************************************************************************************************************";
			SHOW_INFO("\n********************************************************************************************************************************************";);
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
					SHOW_PUZZEL("\nkoncowy puzel:";);
					//cout << "\nkoncowy puzel:";
					SHOW_PUZZEL(*nod->puzel;);
					//cout << *nod->puzel;
					SHOW_DEBUG(" \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";);
					//std::cout << " \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";
					SHOW_DEBUG("\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";);
					//std::cout << "\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";

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
					SHOW_INFO("\nISTNIEJE JUZ HASH w explored: " << hash;);
					//cout << "\nISTNIEJE JUZ HASH w explored: " << hash;
					czyJuzJest = true;
				}

				// czy potrzeba tez w frontiered sprawdzic?
				/*
                //TODO trzeba to uwzglednic
				if (!czyJuzJest) //  ale trzeba zmienic wtedy stack na list
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

					//SHOW_DEBUG("\n+++wrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";);
					SHOW_DEBUG("\n+++wrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " wykonano na nim ruch:"
						<< nod->operatorUsed << " Rozmiar frontier:" << frontier.size(););
					
					//std::cout << "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :"; //(*father->puzel).hasHFunction() << std::endl;
					SHOW_PUZZEL(*nod->puzel << endl;); // to chyba bez sensu
					//cout << *nod->puzel << endl;
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
	if (!stillRun)	// nie znaleziono rozwiazania
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
		SHOW_DEBUG("\t\t size listrevert:" << listMoves.size(););
		//cout << "\t\t size listrevert:" << listMoves.size();
		// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania

		//std::list<Moves> listMoves;
		//for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
		//{
		//	listMoves.push_back(*it);
		//}

		std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste


	}

	//solution.fileSolution << "glebokosc:" << solvedNode->recursionDeph << std::endl;
	SHOW_DEBUG("\nglebokosc:" << solvedNode->recursionDeph << std::endl;);
	//std::cout << "\nglebokosc:" << solvedNode->recursionDeph << std::endl;

	//cout << "\n\n\t STILL RUN =" << stillRun << endl;
	if (!stillRun)//if (!frontier.empty()&& stillRun ==false)
	{
		for (auto x : listMoves)
		{
			//solution.fileSolution << x << " ";
			SHOW_DEBUG(x << " ";);
			//std::cout << x << " ";
		}

		solution.length_of_the_solution_found = listMoves.size();
		//cout << "!!!!!!JEST ROZWIAZANIE" << endl;
	}
	else
	{
		//solution.fileSolution << -1;
		solution.length_of_the_solution_found = -1;
		SHOW_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";);
		//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";
	}
	//std::cout << *wezelKoncowy->puzel.get();



	// *********************************************      zbieranie wynikow

	solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeStart);

	
	solution.number_of_visited_states = frontier.size() + explored.size();
	solution.number_of_processed_states = explored.size();
	////?????????TODO czy to jest dobrze?
	solution.maximum_depth_of_recursion_achieved = MaxDepth;

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
	
	SHOW_INFO("\n\n\n\n ***************************************  podsumowanie wynikow programu  ***************************************";);
    //cout << "\n\n\n\n ***************************************   podsumowanie wynikow programu";
	SHOW_INFO(endl << endl << endl << endl << "Puzel poczatkowy:\n";);
	SHOW_INFO(*startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;);
	SHOW_INFO("\nPuzel koncowy:";);
	SHOW_INFO(*solvedNode->puzel << " jego hash: " << solvedNode->puzel->hasHFunction() << std::endl;);

    //cout << endl << endl << endl << endl << "Puzel poczatkowy:\n";
    //std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
    //cout << "\nPuzel koncowy:";
    //std::cout << *solvedNode->puzel << " jego hash: " << solvedNode->puzel->hasHFunction() << std::endl;

	SHOW_INFO("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
	SHOW_INFO("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
	SHOW_INFO("\n Operatory uzyte: " << solution.solution;);
	SHOW_INFO("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
	SHOW_INFO("\n liczba stanow przetworzonych: " << solution.number_of_processed_states<<std::endl;);

    //cout << "\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count();
    //cout << "\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;
    //cout << "\n Operatory uzyte: " << solution.solution;
    //cout << "\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;
    //cout << "\n liczba stanow przetworzonych: " << solution.number_of_processed_states;
    //cout << endl;



    solution.save();
}
//TODO jeszcze trzeba sprawdzac stany przetworzone czy nie ma elementu
// przerobic frontier na liste i sprawdzac czy nie ma tam elementu tez



