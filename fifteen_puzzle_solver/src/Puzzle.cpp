#include "pch.h"
#include "Puzzle.h"
#include "Exception_wrong_move.h"
//#include "D:\Politechnika - Informatyka\III rok\Vsem\git\SISE\fifteen_puzzle_solver\fifteen_puzzle_solver\Exception_wrong_move.h"



Puzzle::Puzzle(uint_fast8_t puzzleDimensionX, uint_fast8_t puzzleDimensionY, std::vector<uint_fast8_t> org)
	:dimensionX{ puzzleDimensionX }, dimensionY{ puzzleDimensionY }, board{ std::move(org) }
{
	
	
	//TODO dokonczyc konstruktor
}

void Puzzle::Fill(std::vector<uint_fast8_t> org)
{
	if (org.size() != board.size()) throw Exception_wrong_move("Wrong numbers of Parametrs in Puzzle::Fill");
	else
	{
		board.swap(org);
	}
}
//
//std::list<int> Puzzle::DisplayElements()
//{
//
//}
//
//std::list<Moves> Puzzle::PossibleMoves()
//{
//
//}

bool Puzzle::IsOnFinishState()
{
	//bool good = true;
	for (uint_fast8_t i = 0; i< board.size()-1; i++)
	{
		if (i+1 != board[i]) return false;
	}
	if (board[board.size() - 1] != 0) return false;
	return true;
}

Puzzle::~Puzzle()
{
}

//
//bool Puzzle::MoveZero(Moves mov)
//{
//}

