#include <gtest/gtest.h>
#include <Minefields/Board.h>
#include <Minefields/Game.h>

/* TEST(Board, should_change_coord_status)
{
    Board board(6,5);
    setCellStatus(board.grid, 3, 4, Owner::Player); 
    //board.grid[3][4].owner = Owner::Player; //this returns true
    EXPECT_EQ(board.grid[3][4].owner, Owner::Player);
}
TEST(Board, should_return_nullptr_when_trying_to_access_invalid_coordinate)
{
    Board board(4, 4);

} */

namespace boardTests
{
TEST(Board, should_change_coord_status)
{
    Board board(6, 5);
    setCellStatus(board.grid, 3, 4, Owner::Player);
    //board.grid[3][4].owner = Owner::Player; //this returns true
    EXPECT_EQ(board.grid[3][4].owner, Owner::Player);
}
} // namespace boardTests
