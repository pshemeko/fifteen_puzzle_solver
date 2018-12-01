#pragma once
#include <ostream>
//#include <sstream> 

//const char* enumMoves2str[] = {
//  "Left", /* VALUE1 */
//  "Right", /* VALUE2 */
//  "Up",
//  "Down"
//};

enum Moves
{
	Left = 0,
	Right,
	Up,
	Down

};

enum Strategy
{
	bfs = 5,
	dfs,
	astr
};

enum Heuristics
{
	hamm,
	manh
};


std::string static ToString(Moves m)
{
	std::string s;
	switch (m)
	{
	case Moves::Left:	s = "L"; break;
	case Moves::Right:	s = "R"; break;
	case Moves::Up:		s = "U"; break;
	case Moves::Down:	s = "D"; break;

	default: s = "Nieznany"; break;

	}
	return s;
}


/*
//! Function for using name of enum LogLevel
const char *toString(Moves log);
const char *toDescription(Moves log);

inline std::ostream &operator<<(std::ostream &os, Moves err)
{
    return os << toString(err);
}
*/
