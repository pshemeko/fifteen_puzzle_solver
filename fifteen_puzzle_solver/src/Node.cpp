#include "pch.h"
#include "Node.h"


Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Puzzle> puzel, Moves operatorUsed)
	:puzel{ puzel }, parrent{ parent }, operatorUsed{ operatorUsed }
{
}


Node::~Node()
{
}
