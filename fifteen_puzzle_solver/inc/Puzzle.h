#pragma once

#include "Enums.h"
#include <list>
#include <vector>


typedef uint16_t puzzleDataType;
//using puzzleDataType = std::uint8_t;


static const int MAXIMUM_PERMITTED_RECURSION_DEPTH = 2;


//// Nie mammyzabezpiecznie zeby nie moc stworzyc elementu klasy zle np. Puzle puz(2,2,{1,2,3});

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

    auto PositionZero() ->  size_t;

	//auto DisplayElements() -> std::list<int>; // potrzeba do wyswietlania elementow //Albo jako lista list 

	auto IsOnFinishState() -> bool;

    // zrobic jako template  /// MOZE zwracac operator lub null
	auto MoveZero(Moves mov) -> bool;// moze rzucac wyj¹tek exception_wrong_move - wyjatki dzialaja dluzej // 

	void Fill(std::vector<puzzleDataType> org); // chyba skasowac

	Puzzle(const Puzzle &) = default;
	Puzzle(Puzzle &&) = default;
	
	Puzzle & operator =(const Puzzle &);

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

	auto hasHFunction() -> size_t;
    friend std::ostream& operator<< (std::ostream& stream, const Puzzle& matrix);

    // moze zrobic wczytywanie z pliku tutaj

	// chyba nie potrzebne te nizej sa

		// mozliwe ruchy dla tego kloca, tej ukladanki
	auto PossibleMoves()->std::list<Moves>;

};



