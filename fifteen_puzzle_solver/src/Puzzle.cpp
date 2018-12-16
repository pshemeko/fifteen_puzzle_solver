#include "pch.h"
#include "Puzzle.h"
#include "Exception_wrong_move.h"


Puzzle::Puzzle(puzzleDataType puzzleDimensionX, puzzleDataType puzzleDimensionY, std::vector<puzzleDataType> org)
	:dimensionX{ puzzleDimensionX }, dimensionY{ puzzleDimensionY }, board{ std::move(org) }
{
   
	setZero();
    hashValue = hasHFunction(); 
	
}

auto Puzzle::PositionZero() ->  size_t
{
    return zeroPosition;
}

void Puzzle::setZero()
{

	for (std::size_t i = 0; i < board.size(); ++i)
	{
		if (0 == board[i])
		{
			zeroPosition = i;
			break;
		}
	}
}



bool Puzzle::IsOnFinishState() //std::vector<puzzleDataType> org)
{

	for (size_t i = 0; i < board.size()-1; ++i)
	{
		if (board[i] != i+1) return false;
	}
    
	return true;
}

Puzzle & Puzzle::operator=(const Puzzle &p)
{

		dimensionX = p.dimensionX;
		dimensionY = p.dimensionY;
		zeroPosition = p.zeroPosition;
		board = p.board;

		return *this;

}

Puzzle::~Puzzle()
{
}


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
			//hashValue = hasHFunction();
			hashValue = Hash< HashType>()(board);
        }
    }
    if (mov == Moves::Right)
    {
        if (CanMoveRight())
        {
            std::swap(board[zeroPosition], board[zeroPosition + 1]);
            zeroPosition += 1;
            isMoved = true;
			//hashValue = hasHFunction();
			hashValue = Hash< HashType>()(board);
        }
    }
    if (mov == Moves::Up)
    {
        if (CanMoveUp())
        {
            std::swap(board[zeroPosition], board[zeroPosition - dimensionY]);
            zeroPosition -= dimensionY;
            isMoved = true;
			//hashValue = hasHFunction();
			hashValue = Hash< HashType>()(board);
        }
    }
    if (mov == Moves::Down)
    {
        if (CanMoveDown())
        {
            std::swap(board[zeroPosition], board[zeroPosition + dimensionY]);
            zeroPosition += dimensionY;
            isMoved = true;
			//hashValue = hasHFunction();
			hashValue = Hash< HashType>()(board);
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


auto Puzzle::hasHFunction() -> HashType
{
	HashType hash = 0;
	HashType two = 1;//2^0, 2^1, 2^2, 2^3....
	for (HashType i = 0; i < board.size(); ++i)
	{
		hash += two * static_cast<int>(board[i]);
		two *= 2;
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
