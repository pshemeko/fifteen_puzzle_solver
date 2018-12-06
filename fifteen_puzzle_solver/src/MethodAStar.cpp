#include "pch.h"
#include "MethodAStar.h"
#include "Functions.h"
#include <map>



MethodAStar::MethodAStar(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, Heuristics heuristic, std::vector<Moves> orderEnum)
	:Methods(contex, fileOutputSolution, fileAdditionalInformation), heuristic{ heuristic }, order{ orderEnum }
{
}


MethodAStar::~MethodAStar()
{
}

auto MethodAStar::run(Solution &solution) -> void
{
 
    // wskazniki na funkcje zwracajace int i pobierajaca puzla
    
    int(*wskaznikNaFunkcje)(std::shared_ptr<Puzzle> puz);
	if (heuristic == Heuristics::hamm)
	{
		wskaznikNaFunkcje = &metrykaHamington;
		SHOW_DEBUG("\n Wybrana Heurystyka: Hamilton \n\n";);
	}
	else if (heuristic == Heuristics::manh)
	{
		wskaznikNaFunkcje = &metrykaManhattan;
		SHOW_DEBUG("\n Wybrana Heurystyka: Manhatan \n\n";);
	}
	else wskaznikNaFunkcje = &metrykaNieznana;
 

	using namespace std;

 
	SHOW_INFOS_FOR_SCRYPTS("\nASTAR";);
	if (heuristic == Heuristics::hamm) SHOW_INFOS_FOR_SCRYPTS(" Heurystyka: Hamilton ";);
	if (heuristic == Heuristics::manh) SHOW_INFOS_FOR_SCRYPTS(" Heurystyka: Manhatan ";);
	SHOW_INFOS_FOR_SCRYPTS(solution.fileInput;);

    std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	            SHOW_PUZZEL("Puzel Poczatkowy:" << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl)
                    
    int MaxDepth = 0;

	//			std::chrono::time_point<std::chrono::steady_clock> timeEnd;// = std::chrono::high_resolution_clock::now();
    //std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();
    auto timeStart = std::chrono::high_resolution_clock::now();

    // jako frontier moge dac std::set lub std:: priority_queue lub std::map - ktory wybrac 
    std::multimap<int, std::shared_ptr<Node> > frontier{};
    std::list<std::shared_ptr<Node> > explored{};

	std::shared_ptr<Node> root = std::make_shared<Node>(startPuzzel); // poczatkowy wezel

    std::shared_ptr<Node> father = root;

    /// obliczamy to i wrzucamy do kontenera - to ten wzor z wykladu f(n) = g(n) + herystyka  ; g- ilos krokow jakie xzajelo dojcie tutaj
    int functionFN = father->recursionDeph + (*wskaznikNaFunkcje)(father->puzel);
                SHOW_DEBUG("recursionDepth:" << father->recursionDeph << " wartosc meryki dla root: " << (*wskaznikNaFunkcje)(father->puzel));
    int zFunckcji = (*wskaznikNaFunkcje)(startPuzzel);
                SHOW_DEBUG("\n wartosc funkcji: " << zFunckcji << endl);

    frontier.insert(std::pair<int, std::shared_ptr<Node>>(functionFN, root) );

	bool stillRun = true;

	std::shared_ptr<Node> solvedNode = root; // wezel koncowy
	            SHOW_DEBUG("\nwielkosc frontier w A* przed while:" << frontier.size());

    bool isResolved = false;

	while (stillRun && !frontier.empty())
	{
        father = frontier.begin()->second;
        explored.push_back(father);
        frontier.erase(frontier.begin());

        //for (auto x : frontier)
        //{
        //    SHOW_DEBUG( "metryka: " << x.first << " recursionDeph:" << x.second->recursionDeph << " puzel Hash: " << x.second->puzel->hashValue << std::endl;);
        //}

        SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hashValue << "\twielkosc frontier w while:" << frontier.size());
        //if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;

        SHOW_INFO("---------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl);

        for (auto mov : order)
        {
            Puzzle newPuzel = *father->puzel;

            if (newPuzel.MoveZero(mov))
            {
                std::shared_ptr<Puzzle> copy = std::make_shared<Puzzle>(newPuzel);

                std::shared_ptr<Node> nod = std::make_shared<Node>(father, copy, mov, (father->recursionDeph) + 1);

				if (MaxDepth < nod->recursionDeph) MaxDepth = nod->recursionDeph;

                if (nod->puzel->IsOnFinishState())
                {
                   // timeEnd = std::chrono::high_resolution_clock::now();
                    isResolved = true;
                    SHOW_PUZZEL("\nkoncowy puzel:";);
                    SHOW_PUZZEL(*nod->puzel;);
                    SHOW_DEBUG(" \n\n\n\t\t\t\t\t teraz uruchomil sie BREAK - IS ON FINISH STATE";);
                    SHOW_DEBUG("\nten puzel ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " :";);

                    solvedNode = nod;
                    stillRun = false;
                    /// obliczamy to i wrzucamy do kontenera - to ten wzor z wykladu f(n) = g(n) + herystyka  ; g- ilos krokow jakie xzajelo dojcie tutaj
                    int functionFN = father->recursionDeph + (*wskaznikNaFunkcje)(father->puzel);
                    SHOW_DEBUG("recursionDepth:" << father->recursionDeph << " wartosc meryki dla root: " << (*wskaznikNaFunkcje)(father->puzel));
                
                    frontier.insert(std::pair<int, std::shared_ptr<Node>>(functionFN, nod));
                
                    break; // wyskakuje z while
                }
                bool czyJuzJest = false;

                for (auto x : explored)
                {
                    if ((x->puzel->hashValue) == nod->puzel->hashValue)
                    {
                        czyJuzJest = true;
                        SHOW_INFO("\n\t******** jest juz w explored:" << nod->puzel->hashValue << "ruch byl:" << mov << std::endl;);
                        break;
                    }
                }

                if (!czyJuzJest)
                {

                    for (auto x : frontier)
                    {
                        if( x.second->puzel->hashValue == nod->puzel->hashValue)
                        {
                            czyJuzJest = true;
                            SHOW_INFO("\n\t******* jest juz w frontier:" << nod->puzel->hashValue << "ruch byl:" << mov << std::endl;);
                            break;
                        }
                    }

                }

                if (!czyJuzJest)
                {
                    int functionFN = father->recursionDeph + (*wskaznikNaFunkcje)(father->puzel);
                    SHOW_DEBUG("recursionDepth: " << father->recursionDeph << " wartosc meryki dla root: " << (*wskaznikNaFunkcje)(father->puzel));

                    frontier.insert(std::pair<int, std::shared_ptr<Node>>(functionFN, nod));

                    SHOW_DEBUG("\n+++wrzucilem wezel do frontier puz nowy ma hash: " << nod->puzel->hashValue << "  father ma hash: " << nod->parrent->puzel->hashValue << " wykonano na nim ruch:" << ToString(nod->operatorUsed) << " Rozmiar frontier:" << frontier.size(););
               
                    SHOW_PUZZEL(*nod->puzel << endl;);
                }
            
            }

            if (!stillRun) break; // przenosze braeak dalej
        }

        
    }

    //if (!isResolved)  timeEnd = std::chrono::high_resolution_clock::now();

    //******************************** PRZYGOTOWANIE WYNIKOW


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
    

    //******************************** WYSWIETLANIE WYNIKOW


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

    SHOW_ENDING_INFOS("\n\n\n\n ***************************************  podsumowanie wynikow programu  ***************************************";);
    SHOW_ENDING_INFOS("\n\n\n\nPuzel poczatkowy:\n";);
    SHOW_ENDING_INFOS(*startPuzzel << " jego hash: " << startPuzzel->hashValue << std::endl;);
    SHOW_ENDING_INFOS("\nPuzel koncowy:";);
    SHOW_ENDING_INFOS(*solvedNode->puzel << " jego hash: " << solvedNode->puzel->hashValue << std::endl;);
    SHOW_ENDING_INFOS("\n Czas rozwiazania w milisekundach: " << solution.time_duration_of_process.count(););
    SHOW_ENDING_INFOS("\n Dlugosc znalezionego rozwiazania: " << solution.length_of_the_solution_found;);
    SHOW_ENDING_INFOS("\n Operatory uzyte: " << solution.solution;);
    SHOW_ENDING_INFOS("\n liczba stanow odwierdzonych:  " << solution.number_of_visited_states;);
    SHOW_ENDING_INFOS("\n liczba stanow przetworzonych: " << solution.number_of_processed_states );
    SHOW_ENDING_INFOS("\n maksymalna glebokosc rekursji: " << solution.maximum_depth_of_recursion_achieved << std::endl;);

	SHOW_INFOS_FOR_SCRYPTS(" Czas : " << solution.time_duration_of_process.count(););
    solution.save();
 


}




