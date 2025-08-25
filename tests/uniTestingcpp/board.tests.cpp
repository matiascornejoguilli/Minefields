#include <gtest/gtest.h>
#include <uniTestingcpp/Board.h>
#include <uniTestingcpp/Game.h>
#include <uniTestingcpp/utils.h>



namespace boardTests
{
TEST(Board, should_change_coord_status)
{
    Board board(6, 5);
    setCellStatus(board.grid, 3, 4, Owner::Player);
    //board.grid[3][4].owner = Owner::Player; //this returns true
    EXPECT_EQ(board.grid[3][4].owner, Owner::Player);
}
TEST(Board, should_change_board_size)
{
    size_t width = 2;
    size_t heigth = 3;
    Board board{width, heigth};
    EXPECT_EQ(board.grid.size(), heigth);
    EXPECT_EQ(board.grid[0].size(), width);
}

} // namespace boardTests
