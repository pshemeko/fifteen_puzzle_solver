#include "pch.h"
#include "Contex.h"
#include <numeric>
#include <vector>
#include <Puzzle.h>

Contex::Contex(puzzleDataType size_x, puzzleDataType size_y, std::vector< puzzleDataType> setup)
	:sizeX{size_x}, sizeY{size_y}
{
    start = std::shared_ptr<Puzzle>(new Puzzle(size_x, size_y, setup));

    auto initVector = std::vector<puzzleDataType>(size_x * size_y);
    std::iota(std::begin(initVector), std::end(initVector) - 1, 1);
    initVector.back() = 0;
	
}

auto Contex::GetStartPuzzle()->std::shared_ptr<Puzzle>
{
    return start;
}



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
			}
			Puzzle pp = Puzzle(sizeX, sizeY, data);

			wsk = std::make_shared<Puzzle>(pp);
			swap(start, wsk);

		}
	else { 
		std::string ss = name;
		
		throw "Plik o nazwie " + ss + " nie istnieje!!!!!!!!!!!!!!!";
		std::abort();
	}
}

auto Contex::SetForTest(std::shared_ptr<Puzzle> st) -> void
{
	start = st;
}

Contex::~Contex()
{
}
