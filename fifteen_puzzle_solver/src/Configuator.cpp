#include "pch.h"
#include "Configuator.h"


Configuator::Configuator(int argc, char** argv, Contex conteks)
	:argc{ argc }, argv{argv}, conteks{conteks}
{
}


Configuator::~Configuator()
{
}


void Configuator::set()
{
	if (argv[1] == std::string("bfs")) 
	{
		strategy = Strategy::bfs;
	}else if (argv[1] == std::string("dfs")) 
	{
		strategy = Strategy::dfs;
	}else if (argv[1] == std::string("astr")) 
	{ 
		strategy = Strategy::astr; 
	}
	else throw "Wybano zly parametr 1 rodzaj algorytmu";
    
    if (argv[2] == std::string("hamm"))
	{ 
		heuristic = Heuristics::hamm;
	} else if (argv[2] == std::string("manh")) {
		heuristic = Heuristics::manh; 
	} else
		{
			order = argv[2];
			for (size_t i = 0; i < 4; ++i)
			{
				if (order[i] == 'L') orderEnum.push_back(Moves::Left);
				else if (order[i] == 'l') orderEnum.push_back(Moves::Left);
				else if (order[i] == 'R') orderEnum.push_back(Moves::Right);
				else if (order[i] == 'r') orderEnum.push_back(Moves::Right);
				else if (order[i] == 'U') orderEnum.push_back(Moves::Up);
				else if (order[i] == 'u') orderEnum.push_back(Moves::Up);
				else if (order[i] == 'D') orderEnum.push_back(Moves::Down);
				else if (order[i] == 'd') orderEnum.push_back(Moves::Down);
				else throw "wybrano zly parametr 3 porzadek lub heurystyka";
			}
		}

    // gdy strategia A* musze miec domyslne kolejnosci  operatorow
    if (Strategy::astr == strategy)
    {
        orderEnum.push_back(Moves::Left);
        orderEnum.push_back(Moves::Right);
        orderEnum.push_back(Moves::Up);
        orderEnum.push_back(Moves::Down);
    }

    fileWithStartPuzzel = argv[3];
    fileOutputSolution = argv[4];
    fileAdditionalInformation = argv[5];
	
	conteks.set(fileWithStartPuzzel); // teraz w conteks.start mamy ustawienia poczatkowe ukladanki
 
}


auto Configuator::returnMethod() -> Methods*	//TODO rozbuduj dla pozostalych metod
{

	if (strategy == Strategy::dfs)
	{
		Methods *metho = new MethodDFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);

		return metho;
	}
	else if (strategy == Strategy::bfs)
	{
		Methods *metho = new MethodBFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);

		return metho;
	}
	else if (strategy == Strategy::astr)
	{
		Methods *metho = new MethodAStar(conteks, fileOutputSolution, fileAdditionalInformation, heuristic, orderEnum);

		return metho;
	}
	else throw "blad nie ma takiej strategii:";

}


//
//void Configuator::setForTest()
//{
//	if (argv[1] == std::string("bfs")) strategy = Strategy::bfs;
//	if (argv[1] == std::string("dfs")) strategy = Strategy::dfs;
//	if (argv[1] == std::string("astr")) strategy = Strategy::astr;
//
//	if (argv[2] == "hamm") { heuristic = Heuristics::hamm; }
//	else if (argv[2] == "manh") { heuristic = Heuristics::manh; }
//	else
//	{
//		order = argv[2];
//		for (size_t i = 0; i < 4; ++i)
//		{
//			if (order[i] == 'L') orderEnum.push_back(Moves::Left);
//			if (order[i] == 'l') orderEnum.push_back(Moves::Left);
//			if (order[i] == 'R') orderEnum.push_back(Moves::Right);
//			if (order[i] == 'r') orderEnum.push_back(Moves::Right);
//			if (order[i] == 'U') orderEnum.push_back(Moves::Up);
//			if (order[i] == 'u') orderEnum.push_back(Moves::Up);
//			if (order[i] == 'D') orderEnum.push_back(Moves::Down);
//			if (order[i] == 'd') orderEnum.push_back(Moves::Down);
//		}
//	}
//
//	fileWithStartPuzzel = argv[3];
//	fileOutputSolution = argv[4];
//	fileAdditionalInformation = argv[5];
//
//	Puzzle puz(4, 4, { 1, 2, 3, 4, 5, 6, 7, 0, 9, 10, 11, 8, 13, 14, 15, 12});
//	std::shared_ptr<Puzzle> sh_p_puzel = std::make_shared<Puzzle>(puz);
//	conteks.SetForTest(sh_p_puzel);
//
//}
//
//auto Configuator::setTest() -> void	// TODO TYMCZASOWO uzywam tej funkcji do testowania
//{
//    strategy = Strategy::bfs;
//    heuristic = Heuristics::hamm;
//	orderEnum.push_back(Moves::Down);
//	orderEnum.push_back(Moves::Up);
//    orderEnum.push_back(Moves::Left);
//    orderEnum.push_back(Moves::Right);
//    
//    
//    conteks.set(const_cast<char *>("4x4_04_00019.txt"));
//    
//    fileOutputSolution = const_cast<char *>("jeden.txt");
//    fileAdditionalInformation = const_cast<char *>("dwa.txt");
//
//}
