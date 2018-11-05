#pragma once

#include "Enums.h"
#include <list>
#include<vector>

class Puzzle
{
	int dimensionX; // from one if 1x1 it =1, when 2x2 it have 2
	int dimensionY;
    size_t zeroPosition; // form 0 to (dimensionX * dimensionY)-1

	std::vector<uint_fast8_t> board;

	//auto clone() -> Puzzle; TODO zamiast tu w metodzie  wykonujacej robic memcopy
public:

	Puzzle(uint_fast8_t puzzleDimensionX, uint_fast8_t puzzleDimensionY, std::vector<uint_fast8_t> org);

	Puzzle(uint_fast8_t puzzleDimensionX, uint_fast8_t puzzleDimensionY, Puzzle &puzel, Moves mov);	// wyrzucic???

	//auto DisplayElements() -> std::list<int>; // potrzeba do wyswietlania elementow //Albo jako lista list 

	// mozliwe ruchy dla tego kloca, tej ukladanki
	auto PossibleMoves() ->std::list<Moves>;

	auto IsOnFinishState() -> bool;

    // zrobic jako template  /// MOZE zwracac operator lub null
	auto MoveZero(Moves mov) -> bool;// moze rzucac wyj¹tek exception_wrong_move - wyjatki dzialaja dluzej // 

	void Fill(std::vector<uint_fast8_t> org); // chyba skasowac

	~Puzzle();

    auto CanMoveRight() -> bool;
    auto CanMoveLeft() -> bool;
    auto CanMoveUp() -> bool;
    auto CanMoveDown() -> bool;

    auto toString()-> std::string;
	//tworze
};



