#include "stdafx.h"
#include "CppUnitTest.h"
#include "../fifteen_puzzle_solver/inc/Puzzle.h"
#include "../fifteen_puzzle_solver/inc/MethodBFS.h"
#include "../fifteen_puzzle_solver/inc/Methods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_puzzle
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestValue1)
		{
            Puzzle obj(2, 2, {2,2,2,2});
            Assert::AreEqual(2, obj.dimensionX);
            Assert::AreEqual(2, obj.dimensionY);
        }
        TEST_METHOD(TestValue2)
        {
            Puzzle obj(2, 3, { 2,2,2,2,2,2 });
            Assert::AreEqual(2, obj.dimensionX);
            Assert::AreEqual(3, obj.dimensionY);
        }
        TEST_METHOD(TESTIsOnFinishState)
        {
            Puzzle puz(2, 2, { 1,2,3,0 });
            Assert::IsTrue(puz.IsOnFinishState());

            Puzzle puz1(2, 2, std::vector<puzzleDataType>{2, 1, 3, 0});
            Assert::IsFalse(puz1.IsOnFinishState());// puz1.IsOnFinishState() << "\thash:" << puz1.hasHFunction() << "\t";

            Puzzle puz2(3, 3, std::vector<puzzleDataType>{1, 2, 3, 4, 5, 6, 7, 8, 0});
            Assert::IsTrue(puz2.IsOnFinishState());
        }

        TEST_METHOD(TESTSetZero)
        {
            Puzzle puz(2, 2, { 1,2,3,0 });
            Assert::AreEqual(3, (int)puz.PositionZero());

            Puzzle puz1(2, 2, { 1,0,3,2 });
            Assert::AreEqual(1, (int)puz1.PositionZero());

            Puzzle puz2(2, 3, { 1,2,3,4,0,5 });
            Assert::AreEqual(4, (int)puz2.PositionZero());

            Puzzle puz3(3, 3, { 1,2,3,4,5,6,0,8,7 });
            Assert::AreEqual(6, (int)puz3.PositionZero());
        }

        TEST_METHOD(TESTCanMove2x2)
        {
            // sprawdzam brzegowe
            Puzzle puz(2, 2, { 0,1,2,3 });
            Assert::IsFalse(puz.CanMoveUp());
            Assert::IsFalse(puz.CanMoveLeft());
            Assert::IsTrue(puz.CanMoveRight());
            Assert::IsTrue(puz.CanMoveDown());

            Puzzle puz1(2, 2, { 1,0,2,3 });
            Assert::IsFalse(puz1.CanMoveUp());
            Assert::IsTrue(puz1.CanMoveLeft());
            Assert::IsFalse(puz1.CanMoveRight());
            Assert::IsTrue(puz1.CanMoveDown());

            Puzzle puz2(2, 2, { 1,2,0,3 });
            Assert::IsTrue(puz2.CanMoveUp());
            Assert::IsFalse(puz2.CanMoveLeft());
            Assert::IsTrue(puz2.CanMoveRight());
            Assert::IsFalse(puz2.CanMoveDown());

            Puzzle puz3(2, 2, { 1,2,3,0 });
            Assert::IsTrue(puz3.CanMoveUp());
            Assert::IsTrue(puz3.CanMoveLeft());
            Assert::IsFalse(puz3.CanMoveRight());
            Assert::IsFalse(puz3.CanMoveDown());
        }

        TEST_METHOD(TESTCanMove4x4)
        {
            // sprawdzam brzegowe
            Puzzle puz(4, 4, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz.CanMoveUp());
            Assert::IsFalse(puz.CanMoveLeft());
            Assert::IsTrue(puz.CanMoveRight());
            Assert::IsTrue(puz.CanMoveDown());

            Puzzle puz1a(4, 4, { 1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz1a.CanMoveUp());
            Assert::IsTrue(puz1a.CanMoveLeft());
            Assert::IsTrue(puz1a.CanMoveRight());
            Assert::IsTrue(puz1a.CanMoveDown());

            Puzzle puz1(4, 4, { 1,2,3,0,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz1.CanMoveUp());
            Assert::IsTrue(puz1.CanMoveLeft());
            Assert::IsFalse(puz1.CanMoveRight());
            Assert::IsTrue(puz1.CanMoveDown());

            Puzzle puz2(4, 4, { 1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15 });
            Assert::IsTrue(puz2.CanMoveUp());
            Assert::IsFalse(puz2.CanMoveLeft());
            Assert::IsTrue(puz2.CanMoveRight());
            Assert::IsFalse(puz2.CanMoveDown());

            Puzzle puz3(4, 4, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 });
            Assert::IsTrue(puz3.CanMoveUp());
            Assert::IsTrue(puz3.CanMoveLeft());
            Assert::IsFalse(puz3.CanMoveRight());
            Assert::IsFalse(puz3.CanMoveDown());

            Puzzle puz4(4, 4, { 1,2,3,4,5,6,7,8,0,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz4.CanMoveUp());
            Assert::IsFalse(puz4.CanMoveLeft());
            Assert::IsTrue(puz4.CanMoveRight());
            Assert::IsTrue(puz4.CanMoveDown());

            Puzzle puz5(4, 4, { 1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz5.CanMoveUp());
            Assert::IsTrue(puz5.CanMoveLeft());
            Assert::IsFalse(puz5.CanMoveRight());
            Assert::IsTrue(puz5.CanMoveDown());

            Puzzle puz6(4, 4, { 1,2,3,4,5,6, 0,7,8,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz6.CanMoveUp());
            Assert::IsTrue(puz6.CanMoveLeft());
            Assert::IsTrue(puz6.CanMoveRight());
            Assert::IsTrue(puz6.CanMoveDown());
        }

        TEST_METHOD(TESTMoveZero)
        {
            Puzzle puz(2, 2, { 1,2,0,3 });
            Assert::IsTrue(puz.MoveZero(Moves::Right));
            Assert::IsTrue(puz.IsOnFinishState());
            
            
            //Assert::IsFalse(puz.MoveZero(Moves::Right));
            //Assert::IsFalse(puz.CanMoveRight());
            //Assert::IsTrue(puz.IsOnFinishState());


            Puzzle puz1(2, 2, { 1,2,3,0 });
            Assert::IsFalse(puz1.MoveZero(Moves::Right));
            Assert::IsFalse(puz1.MoveZero(Moves::Down));


        }

        TEST_METHOD(TESTMoveZero2x2)
        {
            // sprawdzam brzegowe
            Puzzle puz(2, 2, { 0,1,2,3 });
            Assert::IsFalse(puz.MoveZero(Moves::Up));
            Assert::IsFalse(puz.MoveZero(Moves::Left));
            Assert::IsTrue(puz.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz.MoveZero(Moves::Down));

            Puzzle puz1(2, 2, { 1,0,2,3 });
            Assert::IsFalse(puz1.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz1.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz1.MoveZero(Moves::Right));
            Assert::IsTrue(puz1.MoveZero(Moves::Down)); 

            Puzzle puz2(2, 2, { 1,2,0,3 });
            Assert::IsTrue(puz2.MoveZero(Moves::Up)); 
            Assert::IsFalse(puz2.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz2.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz2.MoveZero(Moves::Down));

            Puzzle puz3(2, 2, { 1,2,3,0 });
            Assert::IsTrue(puz3.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz3.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz3.MoveZero(Moves::Right));
            Assert::IsTrue(puz3.MoveZero(Moves::Down));
        }

        TEST_METHOD(TESTMoveZero4x4)
        {
            // sprawdzam brzegowe
            Puzzle puz(4, 4, { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz.MoveZero(Moves::Up)); 
            Assert::IsFalse(puz.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz.MoveZero(Moves::Down)); 

            Puzzle puz1a(4, 4, { 1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz1a.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz1a.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz1a.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz1a.MoveZero(Moves::Down)); 

            Puzzle puz1(4, 4, { 1,2,3,0,4,5,6,7,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz1.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz1.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz1.MoveZero(Moves::Right));
            Assert::IsTrue(puz1.MoveZero(Moves::Down)); 

            Puzzle puz2(4, 4, { 1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15 });
            Assert::IsTrue(puz2.MoveZero(Moves::Up)); 
            Assert::IsFalse(puz2.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz2.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz2.MoveZero(Moves::Down));

            Puzzle puz3(4, 4, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 });
            Assert::IsTrue(puz3.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz3.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz3.MoveZero(Moves::Right));
            Assert::IsTrue(puz3.MoveZero(Moves::Down));

            Puzzle puz3a(4, 4, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 });
            Assert::IsFalse(puz3a.MoveZero(Moves::Right));
            Assert::IsFalse(puz3a.MoveZero(Moves::Down));
            Assert::IsTrue(puz3a.MoveZero(Moves::Up));
            Assert::IsTrue(puz3a.MoveZero(Moves::Left));
            Assert::IsTrue(puz3a.MoveZero(Moves::Right));
            Assert::IsTrue(puz3a.MoveZero(Moves::Down));
            Assert::IsTrue(puz3a.IsOnFinishState());

            Puzzle puz4(4, 4, { 1,2,3,4,5,6,7,8,0,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz4.MoveZero(Moves::Up)); 
            Assert::IsFalse(puz4.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz4.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz4.MoveZero(Moves::Down)); 

            Puzzle puz5(4, 4, { 1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz5.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz5.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz5.MoveZero(Moves::Right));
            Assert::IsTrue(puz5.MoveZero(Moves::Down)); 

            Puzzle puz5a(4, 4, { 1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15 });
            Assert::IsFalse(puz5a.MoveZero(Moves::Right));
            Assert::IsTrue(puz5a.MoveZero(Moves::Up));
            Assert::IsTrue(puz5a.MoveZero(Moves::Left));
            Assert::IsTrue(puz5a.MoveZero(Moves::Right));
            Assert::IsTrue(puz5a.MoveZero(Moves::Down));


            Puzzle puz6(4, 4, { 1,2,3,4,5,6, 0,7,8,9,10,11,12,13,14,15 });
            Assert::IsTrue(puz6.MoveZero(Moves::Up)); 
            Assert::IsTrue(puz6.MoveZero(Moves::Left)); 
            Assert::IsTrue(puz6.MoveZero(Moves::Right)); 
            Assert::IsTrue(puz6.MoveZero(Moves::Down)); 
        }

        TEST_METHOD(TEST2Moves)
        {
            Puzzle puz(2, 2, { 0,1,3,2 });
            
            Assert::IsTrue(puz.MoveZero(Moves::Right));
            Assert::IsTrue(puz.MoveZero(Moves::Down));
            Assert::IsFalse(puz.MoveZero(Moves::Right));
            Assert::IsFalse(puz.MoveZero(Moves::Down));
            Assert::IsTrue(puz.IsOnFinishState());

            Puzzle puzle(4, 4, { 1,2,3,4,5,6,7,8,9,10,15,11,13,14,12,0 });
            Assert::IsTrue(puzle.MoveZero(Moves::Left));
            Assert::IsTrue(puzle.MoveZero(Moves::Up));
            Assert::IsTrue(puzle.MoveZero(Moves::Right));
            Assert::IsTrue(puzle.MoveZero(Moves::Down));
            Assert::IsTrue(puzle.IsOnFinishState());
        }

        TEST_METHOD(TESTHasHFunction2x2)
        {
            Puzzle puz(2, 2, { 0,1,3,2 });
            Puzzle puz2(2, 2, { 0,1,3,2 });
            Assert::AreEqual(puz.hasHFunction(), puz2.hasHFunction());

            puz2.MoveZero(Moves::Right);
            Assert::AreNotEqual(puz.hasHFunction(), puz2.hasHFunction());
        }
        TEST_METHOD(TESTHasHFunction4x4)
        {
            Puzzle puz(4, 4, { 1,2,3,4,5,6,7,8,9,10,15,11,13,14,12,0 });
            Puzzle puz2(4, 4, { 1,2,3,4,5,6,7,8,9,10,15,11,13,14,12,0 });
            Assert::AreEqual(puz.hasHFunction(), puz2.hasHFunction());

            puz2.MoveZero(Moves::Left);
            Assert::AreNotEqual(puz.hasHFunction(), puz2.hasHFunction());
        }


	};
}