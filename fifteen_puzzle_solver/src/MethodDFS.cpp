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

// DFS lepiej robic rekurencyjnie mniej pamieci zajmie ale dluzej dzialac bedzie, gdy malo pamieci to lepiej dfs
auto MethodDFS::run(Solution &solution) -> void //Nowy jako drugi robilem
{


	SHOW_DEBUG("\n" << (Moves::Down) << "    i co teraz!!!\nkolejnosc:";);
	for (auto x : order) SHOW_DEBUG(x << " ";);
	SHOW_INFOS_FOR_SCRYPTS("\n**************************************  DFS **************************************\n";);
	SHOW_INFOS_FOR_SCRYPTS(solution.fileInput << "\t\t wersja:";);
    for (auto x : order)
    {
		if (x == Moves::Down)	SHOW_INFOS_FOR_SCRYPTS("D";);
		if (x == Moves::Up)		SHOW_INFOS_FOR_SCRYPTS("U";);
		if (x == Moves::Left)	SHOW_INFOS_FOR_SCRYPTS("L";);
		if (x == Moves::Right)	SHOW_INFOS_FOR_SCRYPTS("R";);
    }
	SHOW_INFOS_FOR_SCRYPTS("\n*************************************  Wglab *************************************";);
    //SHOW_DEBUG(endl << "\n*************************************  Wglab ************************************\n";);

	std::chrono::time_point<std::chrono::steady_clock> timeEnd;// = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();
   

	int MaxDepth = 0;

	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();
	SHOW_PUZZEL("\n MethodBFS fcja run Puzel Poczatkowy:";);
	SHOW_PUZZEL(*startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl;);


	//std::list<std::shared_ptr<Node>> frontier;
	//std::list<std::shared_ptr<Node>> explored;

	auto frontier = std::list<std::shared_ptr<Node>>{};
	auto explored = std::unordered_set<std::size_t>{};

	//jako ze wrzucam w odwrotnej kolejnosci trzba odwroic w tej metodzie
	std::reverse(std::begin(order), std::end(order));


	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel
																	  //Puzzle father = *root->puzel;
	frontier.push_back(root);

	std::shared_ptr<Node> father = root;

	std::shared_ptr<Node> solvedNode = root;
	bool stillRun = true;

		SHOW_DEBUG("\nKOLEJNOSC WRZUCANA:";);
		for (auto x : order) SHOW_DEBUG(x << " ";);

    bool isResolved = false;

	//while(stillRun)
		SHOW_DEBUG("\nwielkos frontier w DFS przed while:" << frontier.size(););

	while (stillRun && !frontier.empty()) // TODO jak zle zostaw samo stillRun
	{
			SHOW_DEBUG("\nwielkows frontier  w while:" << frontier.size(););

		// zdejmuje czowke i wrzucam do explored i przetwarzam ja teraz
		//father = frontier.front();// top();
		//explored.insert(father->puzel->hasHFunction());
		//frontier.pop_front();// pop();
        father = frontier.back();
        //explored.insert(father->puzel->hashValue);
        frontier.pop_back();

        if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;
        if (MAXIMUM_PERMITTED_RECURSION_DEPTH == father->recursionDeph)
        {
            //stillRun = false;
            SHOW_DEBUG("\n\t\t\t\t********************************** PRZEKROCZONO DOPUSZCZALNA GLEBOKOSC\n\n";);
            continue;
        }

        explored.insert(father->puzel->hashValue);

        SHOW_DEBUG("\n kglebokosc rekursjii:" << father->recursionDeph;);
		SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hashValue << "\twielkosc frontier w while:" << frontier.size(););
        SHOW_DEBUG("---------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl;);

		for (auto mov : order)
		{
			Puzzle puzelek = *father->puzel;

			if (puzelek.MoveZero(mov))
			{
				std::shared_ptr<Puzzle> copy = std::make_shared<Puzzle>(puzelek);

				std::shared_ptr<Node> nod = std::make_shared<Node>(father, copy, mov, (father->recursionDeph) + 1);

				if (nod->puzel->IsOnFinishState())
				{
                    timeEnd = std::chrono::high_resolution_clock::now();
                    isResolved = true;
					SHOW_PUZZEL("\nkoncowy puzel:";);
					SHOW_PUZZEL(*nod->puzel;);
					SHOW_DEBUG(" \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";);
					SHOW_DEBUG("\nten puzel ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " :";);

					solvedNode = nod;
					//puzelKoncowy = puzelek;
					stillRun = false;
					frontier.push_back(nod);

					break; // wyskakuje z while
				}
				bool czyJuzJest = false;
				
				if (explored.find(nod->puzel->hashValue) != std::end(explored))
				{
					SHOW_INFO("\nISTNIEJE JUZ HASH w explored: " << nod->puzel->hashValue;);
					czyJuzJest = true;
				}

				// czy potrzeba tez w frontiered sprawdzic?
				
                //TODO trzeba to uwzglednic
				if (!czyJuzJest) //  ale trzeba zmienic wtedy stack na list
				{

					for (auto x : frontier)
					{
						if ((x->puzel->hashValue) == nod->puzel->hashValue)
						{
							czyJuzJest = true;
							//if (  *nod.get() == *x.get()) czyJuzJest = true;
                            SHOW_DEBUG("\n\t\t\t\tjest juz w frontier: " << nod->puzel->hashValue << "ruch byl:" << mov << std::endl;);
							break;
						}
					}

				}
				

				if (!czyJuzJest)
				{
					frontier.push_back(nod);  // albo na poczatek wrzucaaj tj frontier.emplace(frontier.begin(),nod)

					SHOW_DEBUG("\n+++wrzucilem wezel do frontier puz nowy ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " wykonano na nim ruch:"
						<< nod->operatorUsed << " Rozmiar frontier:" << frontier.size(););
					SHOW_PUZZEL(*nod->puzel << endl;); // to chyba bez sensu
					
				}


			}

			//if (!stillRun) break; // TODO chyba mozna to skasowac bo jest break gdy finish state !!!!!!!!przenosze braeak dalej

		}



	}

    if (!isResolved)  timeEnd = std::chrono::high_resolution_clock::now();

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
			wezel = wezel->parrent;
			if (wezel->parrent == nullptr) oneMore = false;			//TODO ******************************************* blad
		}
		SHOW_DEBUG("\t\t size listrevert:" << listMoves.size(););

		std::reverse(std::begin(listMoves), std::end(listMoves)); // odwracam liste

	}

	SHOW_DEBUG("\nglebokosc:" << solvedNode->recursionDeph << std::endl;);

	if (!stillRun)//if (!frontier.empty()&& stillRun ==false)
	{
		for (auto x : listMoves)
		{
			SHOW_DEBUG(x << " ";);
		}

		solution.length_of_the_solution_found = listMoves.size();
	}
	else
	{
		solution.length_of_the_solution_found = -1;
		SHOW_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!! NIE ZNALEZIONO ROZWIAZANIA ";);
	}

	
	// *********************************************      zbieranie wynikow

	solution.time_duration_of_process = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

	
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
	
	SHOW_ENDING_INFOS("\n\n\n\n ***************************************  podsumowanie wynikow programu  ***************************************";);
	SHOW_ENDING_INFOS(endl << endl << endl << endl << "Puzel poczatkowy:\n";);
	SHOW_ENDING_INFOS(*startPuzzel << " jego hash: " << startPuzzel->hashValue << std::endl;);
	SHOW_ENDING_INFOS("\nPuzel koncowy:";);
	SHOW_ENDING_INFOS(*solvedNode->puzel << " jego hash: " << solvedNode->puzel->hashValue << std::endl;);
	SHOW_ENDING_INFOS("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
	SHOW_ENDING_INFOS("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
	SHOW_ENDING_INFOS("\n Operatory uzyte: " << solution.solution;);
	SHOW_ENDING_INFOS("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
	SHOW_ENDING_INFOS("\n liczba stanow przetworzonych: " << solution.number_of_processed_states;);
    SHOW_ENDING_INFOS("\n maksymalna glebokosc rekursji: " << solution.maximum_depth_of_recursion_achieved << std::endl;);

    solution.save();

}





