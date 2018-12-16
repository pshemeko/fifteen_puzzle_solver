#pragma once

#include "Enums.h"
#include <list>
#include <vector>

// disable logging info messages. comment this out to enable logging.
#define SHOW_PUZZEL(msg)
#define SHOW_INFO(msg)
#define SHOW_DEBUG(msg)
#define SHOW_ENDING_INFOS(msg)
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
typedef int HashType; // okresla jak wielka jest zakres hasha warto zmienic z unsigned long long na  int lub unsigned int na size_t lub inny
//using puzzleDataType = std::uint8_t;
typedef std::vector<puzzleDataType> Board;

static const int MAXIMUM_PERMITTED_RECURSION_DEPTH = 20;  // w tresc zadania 20

class Puzzle
{
	void setZero();
public:

	int dimensionX; // from one if 1x1 it =1, when 2x2 it have 2
	int dimensionY;
	size_t zeroPosition; // form 0 to (dimensionX * dimensionY)-1

	Board board;

	HashType hashValue;

public:

	Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, std::vector<puzzleDataType> org);

    auto PositionZero() ->  size_t;

	auto IsOnFinishState() -> bool;

    // zrobic jako template  
	auto MoveZero(Moves mov) -> bool;

	Puzzle(const Puzzle &) = default;
	Puzzle(Puzzle &&) = default;
	
	Puzzle & operator =(const Puzzle &);

	~Puzzle();

    auto CanMoveRight() -> bool;
    auto CanMoveLeft() -> bool;
    auto CanMoveUp() -> bool;
    auto CanMoveDown() -> bool;

    auto toString()-> std::string;

	auto operator==(Puzzle const& rhs) const -> bool;
	auto operator!=(Puzzle const& rhs) const -> bool;

	auto hasHFunction() ->HashType;
    friend std::ostream& operator<< (std::ostream& stream, const Puzzle& matrix);

//https://stackoverflow.com/questions/628790/have-a-good-hash-function-for-a-c-hash-table
	//https://itproblemy.pl/questions/6899392/generic-hash-function-for-all-stlcontainers
};


template <typename T>
struct Hash {
	//
	inline int operator()(const Board &v)const {
		std::hash<T> hasher;
		T seed(0);
		for (auto & it : v)
			seed ^= hasher(it) + 0x933779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};
