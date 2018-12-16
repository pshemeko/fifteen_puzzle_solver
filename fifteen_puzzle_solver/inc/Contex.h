#pragma once

#include"Puzzle.h"
#include <memory>
#include <fstream>
#include <iostream>

// klasa potrzebna do inicjowania ukladanki podanymi tablicami i generowania ukladanki rozwiazanej wrzucac ja bede 
// jako Depenency Injection do klasy metod jak BFS DFS i Agwiazdka

// tworzy stan poczatkowy ukladanki Puzzle
class Contex
{
    int sizeX;
    int sizeY;

public:
	std::shared_ptr<Puzzle> start;

    auto GetStartPuzzle()  -> std::shared_ptr<Puzzle>;

	Contex(puzzleDataType size_x, puzzleDataType size_y, std::vector< puzzleDataType> setup); // chyba wywalic
    Contex() = default;

    auto set(char* name) -> void; // ustawia puzla start z pliku w lini polecen

	auto SetForTest(std::shared_ptr<Puzzle> st) -> void;

	~Contex();
};

