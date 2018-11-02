#pragma once

#include "Enums.h""
#include <list>

class Puzzle
{
	int dimensionX;
	int dimensionY;

public:
	Puzzle(int puzzleDimensionX, int puzzleDimensionY, Puzzle &puzel, Moves mov);

	std::list<int> DisplayElements(); // potrzeba do wyswietlania elementow //Albo jako lista list 

	// mozliwe ruchy dla tego kloca, tej ukladanki
	std::list<Moves> PossibleMoves();

	bool IsOnFinishState();


	~Puzzle();

	//tworze
};



