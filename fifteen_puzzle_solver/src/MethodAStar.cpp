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

// TODO Zrobic jako wskaznik na funcje i 2 funkcje
auto MethodAStar::run(Solution &sol) -> void
{
 
    // wskazniki na funkcje zwracajace int i pobierajaca puzla
    heuristic;
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

	std::chrono::time_point<std::chrono::steady_clock> timeStart = std::chrono::high_resolution_clock::now();

	//TODO  zaimplementoac caly algorytm
	std::shared_ptr<Puzzle> startPuzzel = contex.GetStartPuzzle();

	int MaxDepth = 0;

	cout << endl << "\n**************************************  ASTAR **************************************\n";

    if (heuristic == Heuristics::hamm) SHOW_DEBUG(" Wybrana Heurystyka: Hamilton \n\n";);
    if (heuristic == Heuristics::manh) SHOW_DEBUG(" Wybrana Heurystyka: Manhatan \n\n";);
    

	            SHOW_PUZZEL("Puzel Poczatkowy:" << *startPuzzel << " jego hash: " << startPuzzel->hasHFunction() << std::endl)

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
                int ile = 5;

	while (stillRun && !frontier.empty())
	{
                    ile--;
        father = frontier.begin()->second;
        explored.push_back(father);
        frontier.erase(frontier.begin());

        for (auto x : frontier)
        {
            cout << "metryka: " << x.first << " recursionDeph:" << x.second->recursionDeph << " puzel Hash: " << x.second->puzel->hasHFunction() << endl;
        }

        SHOW_DEBUG("\n----Pobralem wezel: " << father->puzel->hasHFunction() << "\twielkosc frontier w while:" << frontier.size());
        if (MaxDepth < father->recursionDeph) MaxDepth = father->recursionDeph;

        SHOW_INFO("---------- wezel father ma depth: " << father->recursionDeph << " frontier ma rozmiar: " << frontier.size() << endl);

        for (auto mov : order)
        {
            Puzzle newPuzel = *father->puzel;

            if (newPuzel.MoveZero(mov))
            {
                std::shared_ptr<Puzzle> copy = std::make_shared<Puzzle>(newPuzel);

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
                    /// obliczamy to i wrzucamy do kontenera - to ten wzor z wykladu f(n) = g(n) + herystyka  ; g- ilos krokow jakie xzajelo dojcie tutaj
                    int functionFN = father->recursionDeph + (*wskaznikNaFunkcje)(father->puzel);
                    SHOW_DEBUG("recursionDepth:" << father->recursionDeph << " wartosc meryki dla root: " << (*wskaznikNaFunkcje)(father->puzel));
                
                    frontier.insert(std::pair<int, std::shared_ptr<Node>>(functionFN, nod));
                
                    break; // wyskakuje z while
                }
                bool czyJuzJest = false;

                for (auto x : explored)
                {
                    if ((x->puzel->hasHFunction()) == nod->puzel->hasHFunction())
                    {
                        czyJuzJest = true;
                        SHOW_INFO("\n\t******** jest juz w explored:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;);
                        break;
                    }
                }

                if (!czyJuzJest)
                {

                    for (auto x : frontier)
                    {
                        if( x.second->puzel->hasHFunction() == nod->puzel->hasHFunction())
                        {
                            czyJuzJest = true;
                            SHOW_INFO("\n\t******* jest juz w frontier:" << nod->puzel->hasHFunction() << "ruch byl:" << mov << std::endl;);
                            break;
                        }
                    }

                }

                if (!czyJuzJest)
                {
                    int functionFN = father->recursionDeph + (*wskaznikNaFunkcje)(father->puzel);
                    SHOW_DEBUG("recursionDepth:" << father->recursionDeph << " wartosc meryki dla root: " << (*wskaznikNaFunkcje)(father->puzel));

                    frontier.insert(std::pair<int, std::shared_ptr<Node>>(functionFN, nod));

                    SHOW_DEBUG("\n+++wrzucilem wezel do frontier puz nowy ma hash" << nod->puzel->hasHFunction() << "  father ma hash: " << nod->parrent->puzel->hasHFunction() << " wykonano na nim ruch:"
                        << nod->operatorUsed << " Rozmiar frontier:" << frontier.size(););
               
                    SHOW_PUZZEL(*nod->puzel << endl;);
                }
            
            }

            if (!stillRun) break; // przenosze braeak dalej
        }

        




    }

    //******************************** WYSWIETLANIE 

 


}




