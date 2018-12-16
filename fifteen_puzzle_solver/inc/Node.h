#pragma once
#include "Puzzle.h"
#include <memory>

class Node
{
public:

	std::shared_ptr<Puzzle> puzel;

	Moves operatorUsed;	

	std::shared_ptr<Node> parrent;

    int recursionDeph; // glebokos
	
    Node(std::shared_ptr<Puzzle> puzel);
    Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed, int recursionDeph);


    Node() = default; // potrzebny by stworzyc pierwszy weze³ TODO Chyba wywalic
	Node(const Node &) = default;
	Node(Node &&) = default;

	~Node();
};




