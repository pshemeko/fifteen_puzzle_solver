#pragma once

#include"Puzzle.h"
#include <memory>

// klasa potrzebna do inicjowania ukladanki podanymi tablicami i generowania ukladanki rozwiazanej wrzucac ja bede 
// jako Depenency Injection do klasy metod jak BFS DFS i Agwiazdka
class Contex
{
	uint_fast8_t sizeX;
	uint_fast8_t sizeY;

public:
	std::shared_ptr<Puzzle> start;
    std::shared_ptr<Puzzle> finish;

    auto GetStartPuzzle()  -> std::shared_ptr<Puzzle>;
    auto GetFinishPuzzle() -> std::shared_ptr<Puzzle>;

	Contex(uint_fast8_t size_x, uint_fast8_t size_y, std::vector< uint_fast8_t> setup);
	~Contex();
};

