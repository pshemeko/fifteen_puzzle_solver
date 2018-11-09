#pragma once
#include "Puzzle.h"
#include <memory>

class Node
{
public:

	std::shared_ptr<Puzzle> puzel;
	// operator jaki zosta� u�yty by dotrzec do tego w�z�a
	Moves operatorUsed;	

	std::shared_ptr<Node> parrent;
	
	//Node();
	Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed);
    Node(std::shared_ptr<Puzzle> puzel);

    Node() = default; // potrzebny by stworzyc pierwszy weze�

	// lub
	//Node(std::shared_ptr<Node> parent,, Moves operatorUsed);

	
	~Node();
};

