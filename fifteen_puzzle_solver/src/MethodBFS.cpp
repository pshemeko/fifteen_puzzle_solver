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
	
	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

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
			stillRun = false;
			cout << "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";
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
						cout << "\nkoncowy puzel:";
						cout << *nod->puzel;
						std::cout << " \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";
						std::cout << "\nten puzel ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " :";
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
							std::cout << "\n\t\t\t\tjest juz w explored:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
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
								std::cout << "\n\t\t\t\tjest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;
								break;
							}
						}

					}

					if (!czyJuzJest)
					{
						frontier.push_back(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)

						std::cout << "\nwrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() <<" :" ; //(*father->puzel).hasHFunction() << std::endl;
						cout << *nod->puzel << endl;
					}


			}

			if (!stillRun ) break; // przenosze braeak dalej
		}
		//teraz biore pierwszy i przetwarzam
		
		//father = frontier.front();
		//explored.push_back(father);
		//frontier.pop_front();


		if(stillRun) ile++;///// czy ok 
		std::cout << "\n koniec for:" << ile;
	}
	std::cout << "\n wyszlo z while" <<" ile:" << ile;
	// teraz sprawdzanie i podawanie wynikow
	//moze zrobic klase do tego


	//******************************** WYSWIETLANIE 

	
	std::list<Moves> listMoves;
	bool oneMore = true;
	std::shared_ptr <Node> wezel = wezelKoncowy;
	while (oneMore)
	{
		listMoves.push_back(wezel->operatorUsed);
		//std::cout << "\noneMore:" << oneMore << " operator:" << wezel->operatorUsed;
		wezel = wezel->parrent;
		if (wezel->parrent == nullptr) oneMore = false;
	}
	cout <<  "\t\t size listrevert:" << listMoves.size();
	// zaweira w dobrej kolejnosci kolejnosc ruchow od poczatku do rozwiazania
	
	//std::list<Moves> listMoves;
	//for (std::list<Moves>::reverse_iterator it = listMoves.rbegin(); it != listMoves.rend(); ++it)
	//{
	//	listMoves.push_back(*it);
	//}

	std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste

	solution.fileSolution << "glebokosc:" << ile << std::endl;
	std::cout << "\nglebokosc:" << ile << std::endl;

	for(auto x : listMoves)
	{
		solution.fileSolution << x <<" ";
		std::cout << x << " ";
	}

	//std::cout << *wezelKoncowy->puzel.get();
	


	// *********************************************      zbieranie wynikow

	solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeStart);

	solution.length_of_the_solution_found = listMoves.size();
	solution.number_of_visited_states = frontier.size() + explored.size();
	solution.number_of_processed_states = explored.size();
	////?????????TODO czy to jest dobrze?
	solution.maximum_depth_of_recursion_achieved = ile;
	for (auto x : listMoves)
	{
		if (x == Moves::Down)	solution.solution += "D";
		if (x == Moves::Up)		solution.solution += "U";
		if (x == Moves::Left)	solution.solution += "L";
		if (x == Moves::Right)	solution.solution += "R";
	}
	cout << "\n\n\n\n ***************************************   podsumowanie wynikow programu";

	cout << endl << endl << endl << endl<<"Puzel poczatkowy:\n";
	std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
	cout << "\nPuzel koncowy:";
	std::cout << *wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hasHFunction() << std::endl;
	

	cout << "\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count();
	cout << "\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;
	cout << "\n Operatory uzyte: " << solution.solution;
	cout << "\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;
	cout << "\n liczba stanow przetworzonych: " << solution.number_of_processed_states;
	cout << endl;
	//solution.save();
}
