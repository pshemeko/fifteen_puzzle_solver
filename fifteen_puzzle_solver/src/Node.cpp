#include "pch.h"
#include "Node.h"


Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed)
	:puzel{ puzel }, parrent{ parent }, operatorUsed{ operatorUsed }
{
    recursionDeph = 0;
}

Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed, int recursionDeph)
: puzel{ puzel }, parrent{ parent }, operatorUsed{ operatorUsed }, recursionDeph{ recursionDeph }
{
    
}

Node::Node(std::shared_ptr<Puzzle> puzel)
    : puzel{ puzel }
{
     operatorUsed = Moves::Down;
	 parrent == nullptr;
}


Node::~Node()
{
}
