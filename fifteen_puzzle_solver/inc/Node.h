#pragma once
#include "Puzzle.h"
#include <memory>

class Node
{
public:

	std::shared_ptr<Puzzle> puzel;
	// operator jaki zosta³ u¿yty by dotrzec do tego wêz³a
	Moves operatorUsed;	

	std::shared_ptr<Node> parrent;

    int recursionDeph; // glebokos
	
	//Node();
	Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed);
    Node(std::shared_ptr<Puzzle> puzel);
    Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed, int recursionDeph);


    Node() = default; // potrzebny by stworzyc pierwszy weze³ TODO Chyba wywalic
	//Node(Node const &)=default;
	// lub
	//Node(std::shared_ptr<Node> parent,, Moves operatorUsed);

	//friend bool operator ==(const Node &n1, const Node &n2);

	~Node();
};

//
//bool operator ==(const Node &n1, const Node &n2)
//{
//	return n1.puzel->hasHFunction() == n2.puzel->hasHFunction();
//}


