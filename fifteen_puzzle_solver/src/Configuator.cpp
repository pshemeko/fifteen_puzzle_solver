#include "pch.h"
#include "Configuator.h"


Configuator::Configuator(int argc, char** argv, Contex conteks)
	:argc{ argc }, argv{argv}, conteks{conteks}
{
}


Configuator::~Configuator()
{
}

Configuator::Configuator(Contex con) // TODO zmien na konstruktor by bral z parametrow programu dane
: conteks{ con } 
{	
		argc = 0;
		// argv = (char**)malloc(sizeof(char*)); // const_cast<char **>();
		// argv[0] = const_cast<char *>("a");
		fileWithStartPuzzel = const_cast<char *>("brak.txt");
		fileOutputSolution = const_cast<char *>("brak1.txt");
		fileAdditionalInformation = const_cast<char *>("brak2.txt");
		order = const_cast<char *>("dupaRight");
		//orderEnum.push_back(Moves::Down);

}

void Configuator::set()
{
    if (argv[1] == std::string("bfs")) strategy = Strategy::bfs;
    if (argv[1] == std::string("dfs")) strategy = Strategy::dfs;
    if (argv[1] == std::string("astr")) strategy = Strategy::astr;
    
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
/*
    std::cout << std::endl<<argv[2] << std::endl;
    for (auto x : orderEnum)
    {
        std::cout << x << ", ";
    }
    std::cout << std::endl << argv[1] << std::endl;
    if (argv[1] == const_cast<char *>("bfs")) std::cout << "\nsparsowalo dan3e bfs\n";
*/

    fileWithStartPuzzel = argv[3];
    fileOutputSolution = argv[4];
    fileAdditionalInformation = argv[5];
	
	conteks.set(fileWithStartPuzzel); // teraz w conteks.start mamy ustawienia poczatkowe ukladanki
    //conteks.set(const_cast<char *>("4x4_02_00001.txt"));

	//TODO tutaj tworz reszte rzeczy tj Methods potem na tej metodzie rób run oraz tworz Solution j¹ przekaz do run
    
}

auto Configuator::setTest() -> void	// TODO TYMCZASOWO uzywam tej funkcji do testowania
{
    strategy = Strategy::bfs;
    heuristic = Heuristics::hamm;
	orderEnum.push_back(Moves::Down);
	orderEnum.push_back(Moves::Up);
    orderEnum.push_back(Moves::Left);
    orderEnum.push_back(Moves::Right);
    
    
    conteks.set(const_cast<char *>("4x4_04_00019.txt"));
    
    fileOutputSolution = const_cast<char *>("jeden.txt");
    fileAdditionalInformation = const_cast<char *>("dwa.txt");

}

auto Configuator::returnMethod() -> Methods*	//TODO rozbuduj dla pozostalych metod
{
    if (strategy == Strategy::dfs)
    {
        Methods *metho = new MethodDFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);

        return metho;
    }
	if (strategy == Strategy::bfs)
	{
		Methods *metho = new MethodBFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);
        //Methods *metho = new MethodDFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);

		return metho;
	}
    	// TODO usun to i zmien na A gwiazdka
	 Methods *metho = new MethodDFS(conteks, fileOutputSolution, fileAdditionalInformation, orderEnum);
	 return metho;
}
