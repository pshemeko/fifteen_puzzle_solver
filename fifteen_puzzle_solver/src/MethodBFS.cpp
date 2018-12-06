#include "pch.h"
#include "MethodBFS.h"
#include <queue>
#include <iomanip>




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
	
    //std::chrono::time_point<std::chrono::steady_clock> timeEnd = std::chrono::high_resolution_clock::now();
	//std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();
	auto timeStart = std::chrono::high_resolution_clock::now();

	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	int MaxDepth = 0;
	
	SHOW_INFOS_FOR_SCRYPTS("\n*BFS (Wszerz) : ";);
	//SHOW_INFOS_FOR_SCRYPTS(solution.fileInput << "\t\t wersja:";);
    
	for (auto x : order) SHOW_INFOS_FOR_SCRYPTS(ToString(x););
   //     for (auto x : order)
   //     {
			//if (x == Moves::Down)	SHOW_INFOS_FOR_SCRYPTS("D";);
			//if (x == Moves::Up)		SHOW_INFOS_FOR_SCRYPTS("U";);
			//if (x == Moves::Left)	SHOW_INFOS_FOR_SCRYPTS("L";);
			//if (x == Moves::Right)	SHOW_INFOS_FOR_SCRYPTS("R";);
   //     }
		SHOW_INFOS_FOR_SCRYPTS(" " << solution.fileInput );
				
    SHOW_DEBUG("\n*************************************  Wszerz ************************************\n";);


	SHOW_PUZZEL("Puzel Poczatkowy:"<< *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;)

	//int maximum = MAXIMUM_PERMITTED_RECURSION_DEPTH;// uzywac tego ograniczenia


	std::list<std::shared_ptr<Node>> frontier;
	std::list<std::shared_ptr<Node>> explored;

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel

	frontier.push_back(root);

	std::shared_ptr<Node> father = root;
	////// od tad petla


	bool stillRun = true;

	std::shared_ptr<Node> wezelKoncowy = root;
    SHOW_DEBUG("\nwielkosc frontier w BFS przed while:" << frontier.size(););

    bool isResolved = false;

	//while (stillRun) // potem 
    while(stillRun && !frontier.empty()) // TODO jak zle zostaw samo stillRun
	{

		father = frontier.front();
		//explored.push_back(father);
		frontier.pop_front();
        SHOW_DEBUG(" kglebokosc rekursjii:" << father->recursionDeph;);
        SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hashValue << "\twielkosc frontier w while:" << frontier.size(););
		//if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;
		
		////
//if(father->puzel->hashValue == 877185)system("pause");
//if (father->puzel->hashValue == 876993)system("pause");
/*
if (father->puzel->hashValue == 876545)
{
	system("pause");
	for (auto x : frontier) cout << x->puzel->hashValue << ", ";
	cout << endl;
}
if (father->puzel->hashValue == 861185)
{
	system("pause");
	for (auto x : frontier) cout << x->puzel->hashValue << ", ";
	cout << endl;
}
if (father->puzel->hashValue == 873473)
{
	system("pause");
	for (auto x : frontier) cout << x->puzel->hashValue << ", ";
	cout << endl;
}
if (father->puzel->hashValue == 704513)system("pause");
if (father->puzel->hashValue == 458751)system("pause");
*/

		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == father->recursionDeph)
		{
			//stillRun = false;
			SHOW_DEBUG( "\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n";);
			continue;
		}

		explored.push_back(father);	// przenioslem tu nizej by ¿eby wykryl mi w ukladance rozwiazanie przy poziomie 20

		for (auto mov : order)
		{

			Puzzle puzelek = *father->puzel.get();

			if (puzelek.MoveZero(mov))
			{
				std::shared_ptr<Puzzle> kopia = std::make_shared<Puzzle>(puzelek);

				std::shared_ptr<Node> nod = std::make_shared<Node>(father, kopia, mov, (father->recursionDeph) +1);

				if (MaxDepth < nod->recursionDeph) MaxDepth = nod->recursionDeph;
				//////////////////////////TO DO  sprawdz czy dziala break jak docelowy to koniec moze lepiej goto;
				bool czyJuzJest = false;

				for (auto x : explored)
				{
					if ((x->puzel->hashValue) == nod->puzel->hashValue)
					{
						czyJuzJest = true;
						SHOW_INFO( "\n\t\t\t\tjest juz w explored: " << nod->puzel->hashValue << "ruch byl:" << mov << std::endl;);
						break;
					}
				}

				if (!czyJuzJest)
				{

					for (auto x : frontier)
					{
						if ((x->puzel->hashValue) == nod->puzel->hashValue)
						{
							czyJuzJest = true;
							SHOW_DEBUG( "\n\t\t\t\tjest juz w frontier: " << nod->puzel->hashValue << "ruch byl:" << mov << std::endl;);
							break;
						}
					}
					if (czyJuzJest) continue;

				}
				else continue; // to jst continues dla poprzedniego for szukajacego w explores jak znalaz³ to wychodzi z for(auto  mov: order)

				////sprawdz czy jest docelowy
				if (nod->puzel->IsOnFinishState())
				{					
					//timeEnd = std::chrono::high_resolution_clock::now();
					isResolved = true;
					SHOW_PUZZEL("\nkoncowy puzel:";);
					SHOW_PUZZEL(*nod->puzel;);
					SHOW_PUZZEL(" \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";);
					SHOW_PUZZEL("\nten puzel ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " :";);
					wezelKoncowy = nod;
					//puzelKoncowy = puzelek;
					stillRun = false;
					frontier.push_back(nod);    // CZY TO POWINNO BYC???

					break;
				}

				if (!czyJuzJest)
				{
					frontier.push_back(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)
					SHOW_DEBUG( "\n+++wrzucilem wezel do frontier puz nowy ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " wykonano na nim ruch:"
						<< ToString(nod->operatorUsed) << " Rozmiar frontier: " <<frontier.size(););
					SHOW_PUZZEL( *nod->puzel << endl;);
				}


			}

			//if (!stillRun) break; // przenosze braeak dalej
		}
		//teraz biore pierwszy i przetwarzam

		//father = frontier.front();
		//explored.push_back(father);
		//frontier.pop_front();


	}

    //if (!isResolved)  timeEnd = std::chrono::high_resolution_clock::now();


    SHOW_DEBUG("\n wyszlo z while - glebokosc rekursji" << father->recursionDeph;);
	

	//******************************** WYSWIETLANIE 


	std::list<Moves> listMoves;
	if (!frontier.empty())
	{

		bool oneMore = true;
		std::shared_ptr <Node> wezel = wezelKoncowy;
		while (oneMore)
		{
			listMoves.push_back(wezel->operatorUsed);
			wezel = wezel->parrent;
			if (wezel->parrent == nullptr) oneMore = false; //TODO tu wywala blad
		}
		SHOW_DEBUG( "\t\t size listrevert:" << listMoves.size(););

		std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste

	}


	
	if(!stillRun)
	{
		for (auto x : listMoves)
		{
			SHOW_DEBUG( x << " ";);
		}
		solution.length_of_the_solution_found = listMoves.size();
	}
	else
	{
		solution.length_of_the_solution_found = -1;
		SHOW_DEBUG( "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";);
	}
		


	// *********************************************      zbieranie wynikow

	//solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
	solution.time_duration_of_process = (std::chrono::high_resolution_clock::now() - timeStart);
		
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
	

	SHOW_ENDING_INFOS( "\n\n\n\n***************************************  podsumowanie wynikow programu  ***************************************";);
	SHOW_ENDING_INFOS("\n\n\n\nPuzel poczatkowy:\n";);
	SHOW_ENDING_INFOS(*startPuzzel << " jego hash: " << startPuzzel->hashValue << std::endl;);
	SHOW_ENDING_INFOS("\nPuzel koncowy:";);
	SHOW_ENDING_INFOS(*wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hashValue << std::endl;);
	SHOW_ENDING_INFOS("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
	SHOW_ENDING_INFOS("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
	SHOW_ENDING_INFOS("\n Operatory uzyte: " << solution.solution;);
	SHOW_ENDING_INFOS("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
    SHOW_ENDING_INFOS("\n liczba stanow przetworzonych: " << solution.number_of_processed_states;);
    SHOW_ENDING_INFOS("\n maksymalna glebokosc rekursji: " << solution.maximum_depth_of_recursion_achieved << std::endl;);

	SHOW_INFOS_FOR_SCRYPTS(" Czas : " << solution.time_duration_of_process.count(););
	solution.save();
}
