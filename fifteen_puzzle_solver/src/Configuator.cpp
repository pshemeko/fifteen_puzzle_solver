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

    if (argv[1] == "bfs") strategy = Strategy::bfs;
    if (argv[1] == "dfs") strategy = Strategy::dfs;
    if (argv[1] == "astr") strategy = Strategy::astr;

    if (argv[2] == "hamm") { heuristic = Heuristics::hamm; }
    else if (argv[2] == "manh") { heuristic = Heuristics::manh; }
    else
    {
        order = argv[2];
        for (size_t i = 0; i < 4; ++i)
        {
            if (order[i] == 'L') orderEnum.push_back(Moves::Left);
            if (order[i] == 'l') orderEnum.push_back(Moves::Left);
            if (order[i] == 'R') orderEnum.push_back(Moves::Right);
            if (order[i] == 'r') orderEnum.push_back(Moves::Right);
            if (order[i] == 'U') orderEnum.push_back(Moves::Up);
            if (order[i] == 'u') orderEnum.push_back(Moves::Up);
            if (order[i] == 'D') orderEnum.push_back(Moves::Down);
            if (order[i] == 'd') orderEnum.push_back(Moves::Down);
        }
    }

    fileWithStartPuzzel = argv[3];
    fileOutputSolution = argv[4];
    fileAdditionalInformation = argv[5];
	
	conteks.set(fileWithStartPuzzel); // teraz w conteks.start mamy ustawienia poczatkowe ukladanki
    //conteks.set(const_cast<char *>("4x4_02_00001.txt"));

	//TODO tutaj tworz reszte rzeczy tj Methods potem na tej metodzie rób run oraz tworz Solution j¹ przekaz do run
    
}

auto Configuator::setTest() -> void
{
    strategy = Strategy::bfs;
    heuristic = Heuristics::hamm;
    orderEnum.push_back(Moves::Left);
    orderEnum.push_back(Moves::Right);
    orderEnum.push_back(Moves::Up);
    orderEnum.push_back(Moves::Down);
    conteks.set(const_cast<char *>("4x4_02_00001.txt"));
    
    fileOutputSolution = const_cast<char *>("jeden.txt");
    fileAdditionalInformation = const_cast<char *>("dwa.txt");

}

auto Configuator::returnMethod() -> Methods*	//TODO rozbuduj dla pozostalych metod
{
	if (strategy == Strategy::bfs)
	{
		Methods *metho = new MethodBFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);

		return metho;
	}
	
}
