#include "pch.h"
#include "Contex.h"
#include <numeric>


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

auto Contex::GetFinishPuzzle()->std::shared_ptr<Puzzle>
{
    return finish;
}

Contex::~Contex()
{
}
