#pragma once
#include <string>

class Exception_wrong_move
{
	std::string name;
public:

	Exception_wrong_move(std::string name);
	~Exception_wrong_move();
};



Exception_wrong_move::Exception_wrong_move(std::string name)
{
	name = name;
};


Exception_wrong_move::~Exception_wrong_move()
{
}
