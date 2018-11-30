#pragma once

#include "Enums.h"
#include <list>
#include <vector>

// disable logging info messages. comment this out to enable logging.
#define SHOW_PUZZEL(msg)
#define SHOW_INFO(msg)
#define SHOW_DEBUG(msg)
//#define SHOW_ENDING_INFOS(msg)
//#define SHOW_INFOS_FOR_SCRYPTS(msg)

// if LOG_INFO is disabled, we need an empty macro, else it will not compile. comment "#undef LOG_PUZZEL" out, if you want to log messages.
#ifndef SHOW_PUZZEL
#define SHOW_PUZZEL(msg) std::cout<< msg;
#endif // !SHOW

#ifndef SHOW_INFO
#define SHOW_INFO(msg) std::cout<< msg;
#endif // !SHOW_INFO

#ifndef SHOW_DEBUG
#define SHOW_DEBUG(msg) std::cout<< msg;
#endif // !SHOW_DEBUG

#ifndef SHOW_ENDING_INFOS
#define SHOW_ENDING_INFOS(msg) std::cout<< msg;
#endif // !SHOW_ENDING_INFOS

#ifndef SHOW_INFOS_FOR_SCRYPTS
#define SHOW_INFOS_FOR_SCRYPTS(msg) std::cout<< msg;
#endif // !SHOW_INFOS_FOR_SCRYPTS

typedef uint16_t puzzleDataType;
//using puzzleDataType = std::uint8_t;


static const int MAXIMUM_PERMITTED_RECURSION_DEPTH = 20;  // w tresc zadania 20


//// Nie mammyzabezpiecznie zeby nie moc stworzyc elementu klasy zle np. Puzle puz(2,2,{1,2,3});

class Puzzle
{
	void setZero();
public:

	int dimensionX; // from one if 1x1 it =1, when 2x2 it have 2
	int dimensionY;
	unsigned long long zeroPosition; // form 0 to (dimensionX * dimensionY)-1

	std::vector<puzzleDataType> board;

	size_t hashValue;

	//auto clone() -> Puzzle; TODO zamiast tu w metodzie  wykonujacej robic memcopy
public:

	Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, std::vector<puzzleDataType> org);

	//Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, Puzzle &puzel, Moves mov);	// wyrzucic???

    auto PositionZero() ->  size_t;

	auto IsOnFinishState() -> bool;

    // zrobic jako template  /// MOZE zwracac operator lub null
	auto MoveZero(Moves mov) -> bool;

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

	auto hasHFunction() -> unsigned long long;
    friend std::ostream& operator<< (std::ostream& stream, const Puzzle& matrix);

    // moze zrobic wczytywanie z pliku tutaj

	// chyba nie potrzebne te nizej sa

		// mozliwe ruchy dla tego kloca, tej ukladanki
	//auto PossibleMoves()->std::list<Moves>;

};

