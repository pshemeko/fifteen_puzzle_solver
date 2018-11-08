#include "pch.h"
#include "Configuator.h"


Configuator::Configuator(int argc, char** argv)
	:argc{ argc }, argv{argv}
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
    
}
