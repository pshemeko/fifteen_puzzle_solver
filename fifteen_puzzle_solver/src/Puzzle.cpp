#include "pch.h"
#include "Puzzle.h"
#include "Exception_wrong_move.h"
//#include "D:\Politechnika - Informatyka\III rok\Vsem\git\SISE\fifteen_puzzle_solver\fifteen_puzzle_solver\Exception_wrong_move.h"



Puzzle::Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, std::vector<puzzleDataType> org)
	:dimensionX{ puzzleDimensionX }, dimensionY{ puzzleDimensionY }, board{ std::move(org) }
{
    //if (puzzleDimensionX*puzzleDimensionY != org.size()) { throw Exception_wrong_move("zly wymiar vektora lub wymiary x,y"); };
	setZero();
	//TODO dokonczyc konstruktor
}

auto Puzzle::PositionZero() ->  size_t
{
    return zeroPosition;
}

void Puzzle::setZero()
{
	// or give it to autput function
	for (std::size_t i = 0; i < board.size(); ++i)
	{
		if (0 == board[i])
		{
			zeroPosition = i;
			break;
		}
	}
}

void Puzzle::Fill(std::vector<puzzleDataType> org)
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

std::list<Moves> Puzzle::PossibleMoves()
{
    std::list<Moves> l;
    if ( CanMoveLeft() )    l.push_back(Moves::Left);
    if ( CanMoveRight() )   l.push_back(Moves::Right);
    if ( CanMoveUp() )      l.push_back(Moves::Up);
    if ( CanMoveDown() )    l.push_back(Moves::Down);
    return l;
}

bool Puzzle::IsOnFinishState() //std::vector<puzzleDataType> org)
{
	/*for (uint_fast8_t i = 0; i< board.size()-1; ++i)
	{
		if (i+1 != board[i]) return false;
	}
	if (board[board.size() - 1] != 0) return false;
	return true;
	*/

	for (size_t i = 0; i < board.size()-1; ++i)
	{
		if (board[i] != i+1) return false;
	}
    
	return true;
}

Puzzle::~Puzzle()
{
}

//
//bool Puzzle::MoveZero(Moves mov)
//{
//}

auto Puzzle::CanMoveRight() -> bool
{
    return (zeroPosition + 1) % dimensionY != 0;
}

auto Puzzle::CanMoveLeft() -> bool
{
    return zeroPosition % dimensionY != 0;
}

auto Puzzle::CanMoveUp() -> bool
{
    return zeroPosition > dimensionY - 1; // TODO sprawdz
}

auto Puzzle::CanMoveDown() -> bool
{
    return zeroPosition < board.size() - dimensionY;
}



auto Puzzle::MoveZero(Moves mov) -> bool// moze rzucac wyj¹tek exception_wrong_move
{
    bool isMoved = false;
    if (mov == Moves::Left)
    {
        if (CanMoveLeft())
        {
            std::swap(board[zeroPosition], board[zeroPosition - 1]);
            zeroPosition -= 1;
            isMoved = true;
        }
    }
    if (mov == Moves::Right)
    {
        if (CanMoveRight())
        {
            std::swap(board[zeroPosition], board[zeroPosition + 1]);
            zeroPosition += 1;
            isMoved = true;
        }
    }
    if (mov == Moves::Up)
    {
        if (CanMoveUp())
        {
            std::swap(board[zeroPosition], board[zeroPosition - dimensionY]);
            zeroPosition -= dimensionY;
            isMoved = true;
        }
    }
    if (mov == Moves::Down)
    {
        if (CanMoveDown())
        {
            std::swap(board[zeroPosition], board[zeroPosition + dimensionY]);
            zeroPosition += dimensionY;
            isMoved = true;
        }
    }
    return isMoved;
}

auto Puzzle::toString()->std::string
{
    std::string s;

    for (size_t i = 0; i < board.size(); ++i)
    {
        s += (int)board[i] + "\t";
        if ( 0 == i % dimensionY) s += "\n";
    }
    return s;
}


auto Puzzle::operator==(Puzzle const& rhs) const -> bool
{
	return this->board == rhs.board;
}

auto Puzzle::operator!=(Puzzle const& rhs) const -> bool
{
	return !(operator==(rhs));
}

auto Puzzle::hasHFunction() -> double
{
	double hash = 0.0;
	double two = 1.0;//2^0, 2^1, 2^2, 2^3....
	for (size_t i = 0; i < board.size(); ++i)
	{
		hash += two * static_cast<int>(board[i]);
		two *= 2.0;
	}
	return hash;
}

std::ostream& operator<<(std::ostream& os, const Puzzle& puz) 
{
    for (size_t i = 0; i < puz.board.size(); ++i)
    {
        if (i % (puz.dimensionY) == 0) os << "\n";
        os << puz.board[i] << "\t";
        
    }
    
    return os;
}
