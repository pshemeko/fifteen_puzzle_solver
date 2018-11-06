#include "pch.h"
#include "Puzzle.h"
#include <numeric>

TEST(TestCaseNameMoj, TestNameMoj) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  ASSERT_FALSE(0);
}

TEST(PuzzleClassTEST, IsOnFinishStateTEST) {
	puzzleDataType x = 2;
	puzzleDataType y = 2;
	Puzzle puz(x, y, std::vector<puzzleDataType>{1,2,3,0});
	int a;
	//EXPECT_TRUE(puz.IsOnFinishState({ 1,2,3,0 }));
	//uint_fast8_t tab[] = { 1,2,3,0 };
	//std::vector<uint_fast8_t> board(x*y);
	//std::iota(std::begin(board), std::end(board) - 1, 1);
	//board.back() = 0;
	/*std::vector<uint_fast8_t> state(tab, tab + sizeof(tab) / sizeof(uint_fast8_t));
	puz.Fill(state);
	EXPECT_TRUE(puz.IsOnFinishState());
	Puzzle puz2(2, 2);
	uint_fast8_t tab2[] = { 1,2,3,4 };
	std::vector<uint_fast8_t> state2(tab2, tab2 + sizeof(tab2) / sizeof(uint_fast8_t));
	puz2.Fill(state);
	
	ASSERT_FALSE(puz.IsOnFinishState());
	*/
	
	//EXPECT_EQ(1, 1);
	//EXPECT_TRUE(true);
	//ASSERT_FALSE(0);


}