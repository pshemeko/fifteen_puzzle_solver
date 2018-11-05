#pragma once

#include "Enums.h"
#include <list>
#include<vector>


typedef uint16_t puzzleDataType;
//using puzzleDataType = std::uint8_t;

class Puzzle
{
	void setZero();
public:

	int dimensionX; // from one if 1x1 it =1, when 2x2 it have 2
	int dimensionY;
    size_t zeroPosition; // form 0 to (dimensionX * dimensionY)-1

	std::vector<puzzleDataType> board;

	//auto clone() -> Puzzle; TODO zamiast tu w metodzie  wykonujacej robic memcopy
public:

	Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, std::vector<puzzleDataType> org);

	Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, Puzzle &puzel, Moves mov);	// wyrzucic???

	//auto DisplayElements() -> std::list<int>; // potrzeba do wyswietlania elementow //Albo jako lista list 

	// mozliwe ruchy dla tego kloca, tej ukladanki
	auto PossibleMoves() ->std::list<Moves>;

	auto IsOnFinishState(std::vector<puzzleDataType> org) -> bool;

    // zrobic jako template  /// MOZE zwracac operator lub null
	auto MoveZero(Moves mov) -> bool;// moze rzucac wyj¹tek exception_wrong_move - wyjatki dzialaja dluzej // 

	void Fill(std::vector<puzzleDataType> org); // chyba skasowac

	Puzzle(Puzzle const &) = default;
	Puzzle(Puzzle &&) = default;

	~Puzzle();

    auto CanMoveRight() -> bool;
    auto CanMoveLeft() -> bool;
    auto CanMoveUp() -> bool;
    auto CanMoveDown() -> bool;

    auto toString()-> std::string;
	//tworze

	// operators

	auto operator==(Puzzle const& rhs) const -> bool;
	auto operator!=(Puzzle const& rhs) const -> bool;
};



