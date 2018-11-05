#pragma once

#include"Puzzle.h"
#include <memory>

// klasa potrzebna do inicjowania ukladanki podanymi tablicami i generowania ukladanki rozwiazanej wrzucac ja bede 
// jako Depenency Injection do klasy metod jak BFS DFS i Agwiazdka
class Contex
{
	puzzleDataType sizeX;
	puzzleDataType sizeY;

public:
	std::shared_ptr<Puzzle> start;
    std::shared_ptr<Puzzle> finish;

    auto GetStartPuzzle()  -> std::shared_ptr<Puzzle>;
    auto GetFinishPuzzle() -> std::shared_ptr<Puzzle>;

	Contex(puzzleDataType size_x, puzzleDataType size_y, std::vector< puzzleDataType> setup);
	~Contex();
};

