#include "pch.h"
#include "Contex.h"


Contex::Contex(uint_fast8_t size_x, uint_fast8_t size_y, std::vector< uint_fast8_t> setup)
	:sizeX{size_x}, sizeY{size_y}
{
	start = new Puzzle(size_x, size_y, setup);
	finish = new Puzzle(size_x, size_y, setup);
	//start->Fill(setup);
}


Contex::~Contex()
{
}
