#pragma once


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
