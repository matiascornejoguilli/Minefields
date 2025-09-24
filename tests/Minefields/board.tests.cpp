#include <gtest/gtest.h>

#include <Minefields/Board.h>
#include <Minefields/Game.h>

namespace boardTests
{
    TEST(BoardTest, constructor_grid)
    {
        size_t width = 5;
        size_t height = 3;
        Board board(width, height);

        EXPECT_EQ(board.grid.size(), height);
        EXPECT_EQ(board.grid[0].size(), width);
        EXPECT_EQ(board.grid[1].size(), width);
        EXPECT_EQ(board.grid[2].size(), width);

        for (size_t i = 0; i < height; ++i)
        {
            for (size_t j = 0; j < width; ++j)
            {
                EXPECT_EQ(board.grid[i][j].owner, Owner::None);
                //EXPECT_EQ(board.grid[i][j].mine, Mine::status::Active);
            }
        }
    }

    TEST(Board, should_change_coord_status)
    {
        Board board(6, 5);
        setCellStatus(board.grid, 3, 4, Owner::Player);
        EXPECT_EQ(board.grid[3][4].owner, Owner::Player);
    }
} // namespace boardTests