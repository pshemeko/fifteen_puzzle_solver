
#include "pch.h"
#include <iostream>
#include <vector>
#include "Puzzle.h"
#include "Contex.h"
#include "Configuator.h"

int main(int argc, char** argv)
{

		Contex con;
		Configuator conf(argc, argv,con);

		conf.set();
        Methods *met = conf.returnMethod();	

        Solution solu(argv[3], argv[4], argv[5]);
		solu.open();
		met->run(solu);
		solu.close();

		//system("pause");
    return 0;
}

