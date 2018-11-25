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

	int MaxDepth = 0;
	
	cout << endl << "\n**************************************  BFS **************************************\n";

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
    SHOW_DEBUG("\nwielkosc frontier w BFS przed while:" << frontier.size(););
	//while (stillRun) // potem 
    while(stillRun && !frontier.empty()) // TODO jak zle zostaw samo stillRun
	{
		SHOW_DEBUG("\n kglebokosc rekursjii:" << father->recursionDeph;);

        //SHOW_DEBUG("\nwielkows frontier w BFS w while:" << frontier.size(););
		father = frontier.front();
		explored.push_back(father);
		frontier.pop_front();
        SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hasHFunction()<< "\twielkosc frontier w while:" << frontier.size(););
		if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;

		//std::cout << "\t\t\t\t\t\t\t\t\t\tstill run: " << stillRun << std::endl;
		if (MAXIMUM_PERMITTED_RECURSION_DEPTH == father->recursionDeph)
		{
			//stillRun = false;
			//cout << "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";
			SHOW_DEBUG( "\n\n\n\t\t\t\t\t\tPRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";);
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

				std::shared_ptr<Node> nod = std::make_shared<Node>(father, kopia, mov, (father->recursionDeph) +1);

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
					frontier.push_back(nod);    // CZY TO POWINNO BYC???
					
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
					SHOW_DEBUG( "\n+++wrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " wykonano na nim ruch:"
						<< nod->operatorUsed << " Rozmiar frontier:" <<frontier.size(););
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
		//SHOW_DEBUG( "\n koniec for(chyba niepotrzerbne juz):" << ile;); 
    	//std::cout << "\n koniec for:" << ile;
	}
	SHOW_DEBUG( "\n wyszlo z while" << " ile:" << ile;);
    SHOW_DEBUG("\n wyszlo z while - glebokosc rekursji" << " ile:" << father->recursionDeph;);
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


	//solution.fileSolution << "glebokosc:" << ile << std::endl;
	SHOW_INFO( "\nglebokosc:" << ile << std::endl;);
	//std::cout << "\nglebokosc:" << ile << std::endl;




	
	
	//if (!frontier.empty())//if (!frontier.empty()&& stillRun ==false)
	if(!stillRun)
	{
		for (auto x : listMoves)
		{
			//solution.fileSolution << x << " ";
			SHOW_DEBUG( x << " ";);
			//std::cout << x << " ";
		}
		solution.length_of_the_solution_found = listMoves.size();
	}
	else
	{
		//solution.fileSolution << -1;
		solution.length_of_the_solution_found = -1;
		SHOW_DEBUG( "!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";);
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
	

	SHOW_ENDING_INFOS( "\n\n\n\n***************************************  podsumowanie wynikow programu  ***************************************";);
	//cout << "\n\n\n\n ***************************************   podsumowanie wynikow programu";

	SHOW_ENDING_INFOS(endl << endl << endl << endl << "Puzel poczatkowy:\n";);
	//cout << endl << endl << endl << endl<<"Puzel poczatkowy:\n";
	SHOW_ENDING_INFOS(*startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;);
	//std::cout << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;
	SHOW_ENDING_INFOS("\nPuzel koncowy:";);
	//cout << "\nPuzel koncowy:";
	
	SHOW_ENDING_INFOS(*wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hasHFunction() << std::endl;);
	//std::cout << *wezelKoncowy->puzel.get() << " jego hash: " << wezelKoncowy->puzel->hasHFunction() << std::endl;
	
	SHOW_ENDING_INFOS("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
	SHOW_ENDING_INFOS("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
	SHOW_ENDING_INFOS("\n Operatory uzyte: " << solution.solution;);
	SHOW_ENDING_INFOS("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
	SHOW_ENDING_INFOS("\n liczba stanow przetworzonych: " << solution.number_of_processed_states << std::endl;);


	//cout << "\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count();
	//cout << "\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;
	//cout << "\n Operatory uzyte: " << solution.solution;
	//cout << "\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;
	//cout << "\n liczba stanow przetworzonych: " << solution.number_of_processed_states;
	//cout << endl;


	//solution.save();
}
