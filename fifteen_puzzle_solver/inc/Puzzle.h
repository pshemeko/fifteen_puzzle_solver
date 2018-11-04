#pragma once

#include "Enums.h"
#include <list>
#include<vector>

class Puzzle
{
	int dimensionX;
	int dimensionY;

	std::vector<uint_fast8_t> board;

	//auto clone() -> Puzzle; TODO zamiast tu w metodzie  wykonujacej robic memcopy
public:

	Puzzle(uint_fast8_t puzzleDimensionX, uint_fast8_t puzzleDimensionY);

	Puzzle(uint_fast8_t puzzleDimensionX, uint_fast8_t puzzleDimensionY, Puzzle &puzel, Moves mov);	// wyrzucic???

	auto DisplayElements() -> std::list<int>; // potrzeba do wyswietlania elementow //Albo jako lista list 

	// mozliwe ruchy dla tego kloca, tej ukladanki
	auto PossibleMoves() ->std::list<Moves>;

	auto IsOnFinishState() -> bool;

	auto MoveZero(Moves mov) -> bool;// moze rzucac wyj¹tek exception_wrong_move

	void Fill(std::vector<uint_fast8_t> org);

	~Puzzle();

	//tworze
};



