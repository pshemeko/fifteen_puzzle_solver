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
	bfs,
	dfs,
	astr
};

enum Heuristics
{
	hamm,
	manh
};

/*
//! Function for using name of enum LogLevel
const char *toString(Moves log);
const char *toDescription(Moves log);

inline std::ostream &operator<<(std::ostream &os, Moves err)
{
    return os << toString(err);
}
*/