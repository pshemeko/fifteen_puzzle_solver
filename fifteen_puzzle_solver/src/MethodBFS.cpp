#include "pch.h"
#include "MethodBFS.h"
#include <queue>

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

	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();
	std::cout << "\n                  Method BFS                 fcja run\n ";
	SHOW_PUZZEL("Puzel Poczatkowy:"<< *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;)
	//std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
	int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia

	//std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
	//Puzzle father = *root->puzel;
	frontier.push_back(root);

	std::shared_ptr<Node> father = root;
	////// od tad petla

	int ile = 0;// MAXIMUM_PERMITTED_RECURSION_DEPTH;
	bool stillRun = true;
	//Puzzle puzelKoncowy = *startPuzzel.get();
	std::shared_ptr<Node> wezelKoncowy = root;

	while (stillRun) // potem while(!frontier.empty()) // i wywalic to oganiczenie rekursjii
	{
		father = frontier.front();
		explored.push_back(father);
		frontier.pop_front();


		//std::cout << "\t\t\t\t\t\t\t\t\t\tstill run: " << stillRun << std::endl;
		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == ile)
		{
			//stillRun = false;
			//cout << "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";
			SHOW_INFO( "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";);
			continue;
		}

		for (auto mov : order)
		{

			Puzzle puzelek = *father->puzel.get();
			//std::shared_ptr<Puzzle> puz = father->puzel;
			//bool zmienil = puzelek.MoveZero(mov);		//TODO tu trzeba przerwac bo nie mozna zrobic ruchu

			if (puzelek.MoveZero(mov))
			{

				//cout << "czy zmienil plozenie zera " << zmienil << " z ruchem" << mov;
				//cout << puzelek;
				std::shared_ptr<Puzzle> kopia = std::make_shared<Puzzle>(puzelek);

				std::shared_ptr<Node> nod = std::make_shared<Node>(father, kopia, mov);

				////sprawdz czy jest docelowy
				if (nod->puzel->IsOnFinishState()) {
					SHOW_PUZZEL( "\nkoncowy puzel:";);
					//cout << "\nkoncowy puzel:";
					SHOW_PUZZEL( *nod->puzel;);
					//cout << *nod->puzel;
					SHOW_PUZZEL( " \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";);
					//std::cout << " \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";
					SHOW_PUZZEL( "\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";);
					//std::cout << "\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";
					wezelKoncowy = nod;
					//puzelKoncowy = puzelek;
					stillRun = false;
					frontier.push_back(nod);

					break;
				}
				//////////////////////////TO DO  sprawdz czy dziala break jak docelowy to koniec moze lepiej goto;
				bool czyJuzJest = false;

				for (auto x : explored)
				{
					if ((x->puzel->hasHFunction()) == nod->puzel->hasHFunction())
					{
						czyJuzJest = true;
						//if (  *nod.get() == *x.get()) czyJuzJest = true;
						//std::cout << "\n\t\t\t\tjest juz w explored:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
						SHOW_INFO( "\n\t\t\t\tjest juz w explored:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;);
						break;
					}
				}

				if (!czyJuzJest)
				{

					for (auto x : frontier)
					{
						if ((x->puzel->hasHFunction()) == nod->puzel->hasHFunction())
						{
							czyJuzJest = true;
							//if (  *nod.get() == *x.get()) czyJuzJest = true;
							SHOW_INFO( "\n\t\t\t\tjest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;);
							//std::cout << "\n\t\t\t\tjest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
							break;
						}
					}

				}

				if (!czyJuzJest)
				{
					frontier.push_back(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)
					SHOW_INFO( "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";);
					//std::cout << "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :"; //(*father->puzel).hasHFunction() << std::endl;
					SHOW_PUZZEL( *nod->puzel << endl;);
					//cout << *nod->puzel << endl;
				}


			}

			if (!stillRun) break; // przenosze braeak dalej
		}
		//teraz biore pierwszy i przetwarzam

		//father = frontier.front();
		//explored.push_back(father);
		//frontier.pop_front();


		if (stillRun) ile++;///// czy ok 
		SHOW_DEBUG( "\n koniec for:" << ile;);
		//std::cout << "\n koniec for:" << ile;
	}
	SHOW_DEBUG( "\n wyszlo z while" << " ile:" << ile;);
	//std::cout << "\n wyszlo z while" << " ile:" << ile;
	
	// teraz sprawdzanie i podawanie wynikow
	//moze zrobic klase do tego


	//******************************** WYSWIETLANIE 


	std::list<Moves> listMoves;
	if (!frontier.empty())
	{

		bool oneMore = true;
		std::shared_ptr <Node> wezel = wezelKoncowy;
		while (oneMore)
		{
			listMoves.push_back(wezel->operatorUsed);
			//std::cout << "\noneMore:" << oneMore << " operator:" << wezel->operatorUsed;
			wezel = wezel->parrent;
			if (wezel->parrent == nullptr) oneMore = false; //TODO tu wywala blad
		}
		SHOW_DEBUG( "\t\t size listrevert:" << listMoves.size(););
		//cout << "\t\t size listrevert:" << listMoves.size();
		// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania

		//std::list<Moves> listMoves;
		//for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
		//{
		//	listMoves.push_back(*it);
		//}

		std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste

	}


	solution.fileSolution << "glebokosc:" << ile << std::endl;
	SHOW_INFO( "\nglebokosc:" << ile << std::endl;);
	//std::cout << "\nglebokosc:" << ile << std::endl;
	
	if (!frontier.empty())//if (!frontier.empty()&& stillRun ==false)
	{
		for (auto x : listMoves)
		{
			solution.fileSolution << x << " ";
			SHOW_INFO( x << " ";);
			//std::cout << x << " ";
		}
	}
	else
	{
		solution.fileSolution << -1;
		SHOW_INFO( "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";);
		//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";
	}
	//std::cout << *wezelKoncowy->puzel.get();
	


	// *********************************************      zbieranie wynikow

	solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeStart);

	solution.length_of_the_solution_found = listMoves.size();
	solution.number_of_visited_states = frontier.size() + explored.size();
	solution.number_of_processed_states = explored.size();
	////?????????TODO czy to jest dobrze?
	solution.maximum_depth_of_recursion_achieved = ile;

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

	SHOW_INFO( "\n\n\n\n ***************************************   podsumowanie wynikow programu";);
	//cout << "\n\n\n\n ***************************************   podsumowanie wynikow programu";

	SHOW_INFO(endl << endl << endl << endl << "Puzel poczatkowy:\n";);
	//cout << endl << endl << endl << endl<<"Puzel poczatkowy:\n";
	SHOW_INFO(*startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;);
	//std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
	SHOW_INFO("\nPuzel koncowy:";);
	//cout << "\nPuzel koncowy:";
	
	SHOW_INFO(*wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hasHFunction() << std::endl;);
	//std::cout << *wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hasHFunction() << std::endl;
	
	SHOW_INFO("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
	SHOW_INFO("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
	SHOW_INFO("\n Operatory uzyte: " << solution.solution;);
	SHOW_INFO("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
	SHOW_INFO("\n liczba stanow przetworzonych: " << solution.number_of_processed_states << std::endl;);


	//cout << "\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count();
	//cout << "\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;
	//cout << "\n Operatory uzyte: " << solution.solution;
	//cout << "\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;
	//cout << "\n liczba stanow przetworzonych: " << solution.number_of_processed_states;
	//cout << endl;


	//solution.save();
}