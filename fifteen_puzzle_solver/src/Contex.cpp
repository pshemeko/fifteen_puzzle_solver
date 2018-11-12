#include "pch.h"
#include "Contex.h"
#include <numeric>
#include <vector>
#include <Puzzle.h>
//#include "Exception_wrong_move.h"

Contex::Contex(puzzleDataType size_x, puzzleDataType size_y, std::vector< puzzleDataType> setup)
	:sizeX{size_x}, sizeY{size_y}
{
    //Puzzle pu = Puzzle(size_x, size_y, setup);
	//start = std::make_shared< pu>;

    start = std::shared_ptr<Puzzle>(new Puzzle(size_x, size_y, setup));
	//finish =  Puzzle(size_x, size_y, setup);
	//start->Fill(setup);

    auto initVector = std::vector<puzzleDataType>(size_x * size_y);
    std::iota(std::begin(initVector), std::end(initVector) - 1, 1);
    initVector.back() = 0;
    finish = std::shared_ptr<Puzzle>(new Puzzle(size_x, size_y, initVector));
	
}

auto Contex::GetStartPuzzle()->std::shared_ptr<Puzzle>
{
    return start;
}

//
//auto Contex::GetFinishPuzzle()->std::shared_ptr<Puzzle>
//{
//    return finish;
//}

auto Contex::set(char* name) -> void
{
    std::ifstream file;
	
    file.open(name);
	if (file.is_open())
		{

			file >> sizeX;
			file >> sizeY;
			int a;
			std::vector<puzzleDataType> data;
			std::shared_ptr<Puzzle> wsk;
			for (size_t i = 0; i < sizeX*sizeY; ++i)
			{
				file >> a;
				data.push_back(a);

				//TODO teraz robie

				//ale sutasdfa
			}
			Puzzle pp = Puzzle(sizeX, sizeY, data);

			wsk = std::make_shared<Puzzle>(pp);
			swap(start, wsk);

		}
	else { 
		//throw new Exception_wrong_move("Nie udalo sie otworzyc pliku"); 
		std::string ss = name;
		
		throw "Plik o nazwie " + ss + " nie istnieje!!!!!!!!!!!!!!!";
		std::abort();
	}
	//std::cout << std::endl <<" wielkosc tablicy data:"<< data.size() << std::endl;
	//for (size_t i = 0; i < data.size(); ++i)
	//{
	//	std::cout << data[i] << "\t";
	//}

}

Contex::~Contex()
{
}
