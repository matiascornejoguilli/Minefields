#include <gtest/gtest.h>
#include <uniTestingcpp/Game.h>
#include <uniTestingcpp/Board.h>
#include <uniTestingcpp/Cell.h>
#include <uniTestingcpp/Player.h>

namespace gameTests
{
TEST(Game, should_return_false_when_trying_to_shoot_invalid_coordinate)
{
    Board board(4, 5);
    Player player(5);
    int x = player.playerMines;

    EXPECT_FALSE(shoot(7, 8, board.grid.at(0).size(), board.grid.size(), x, x, board.grid));
}
TEST(Game, should_destroy_mine_when_trying_to_guess_it)
{
    Board board(4, 5);
    Player player(5);
    setCellStatus(board.grid, 2, 3, Owner::Player);
    int minesLeft = player.playerMines;
    shoot(2, 3, board.grid.at(0).size(), board.grid.size(), minesLeft, minesLeft, board.grid);
    EXPECT_EQ(board.grid[2][3].owner, Owner::Destroy);
}
TEST(Board, should_return_false_when_trying_to_shoot_destroyed_mines)
{
    Board board(4, 5);
    Player player(5);
    setCellStatus(board.grid, 2, 3, Owner::Player);
    int minesLeft = player.playerMines;
    shoot(2, 3, board.grid.at(0).size(), board.grid.size(), minesLeft, minesLeft, board.grid);
    EXPECT_FALSE(shoot(2, 3, board.grid.at(0).size(), board.grid.size(), minesLeft, minesLeft, board.grid));
    
}
} // namespace gameTests
