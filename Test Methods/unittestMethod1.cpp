#include "stdafx.h"
#include "CppUnitTest.h"
#include "../fifteen_puzzle_solver/inc/Configuator.h"
#include "../fifteen_puzzle_solver/inc/Contex.h"
#include "../fifteen_puzzle_solver/inc/MethodDFS.h"
#include "../fifteen_puzzle_solver/inc/MethodBFS.h"

#include <iostream>
#include <vector>
#include "../fifteen_puzzle_solver/inc/Puzzle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMethods
{		
	TEST_CLASS(UnitTestmethodBFS)
	{
	public:

		
		TEST_METHOD(TestMethodBFSrun)
		{
			/*
			Contex con;

			int argc = 6;
			char* argvTmp[6] = { "prog", "bfs","LRDU", "../../Test Methods/4x4_02_00001.txt", "dupa.txt", "dodatkowe.txt" };
			char ** argv = argvTmp;
			Configuator conf(argc, argv, con);

			//conf.setForTest();
			conf.set();
			Methods *met = conf.returnMethod();	// to wrzucic 


			//Solution solu(const_cast<char *>("jeden.txt"), const_cast<char *>("dwa.txt"));
			Solution solu(argv[4], argv[5]);
			met->run(solu);
			solu.solution;
			
			std::string tmp = "DD";
			//Assert::AreEqual(tmp, solu.solution);
			
			*/

			// TODO: W tym miejscu dodaj kod testowy
		}

	};
	TEST_CLASS(UnitTestmethodDFS)
	{
	public:

		TEST_METHOD(TestMethodDFSrun)
		{


			// TODO: W tym miejscu dodaj kod testowy
		}

	};
}