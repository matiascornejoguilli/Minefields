#include <gtest/gtest.h>
#include <uniTestingcpp/Board.h>

namespace boardTesting
{
	TEST(Board, should)
	{
        Board board(5, 6);
        ASSERT_TRUE(board.grid.size() == 6);

	}

}