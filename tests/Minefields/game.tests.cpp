#include <gtest/gtest.h>

#include <Minefields/Board.h>
#include <Minefields/Cell.h>
#include <Minefields/Game.h>
#include <Minefields/Player.h>

namespace gameTests
{ /*
TEST(gameTests, check_placecpuMines)
{
    std::vector<std::vector<Cell>> board;
    int mineCount = 1;
    CoordGenerator generateCoord = []() -> std::pair<int, int> { return {1, 1}; };
    placeCpuMines(board, mineCount, generateCoord);
    EXPECT_EQ(static_cast<int>(board[1][1].owner), static_cast<int>(Owner::Cpu));
}

TEST(gameTests, check_if_placecpuMines_changes_the_mine)
{
    size_t width = 3;                                                       // Ancho del tablero
    size_t height = 3;                                                      // Alto del tablero
    std::vector<std::vector<Cell>> board(height, std::vector<Cell>(width)); // Inicializa el tablero
    int mineCount = 1;
    CoordGenerator generateCoord = []() -> std::pair<int, int> { return {1, 1}; };
    placeCpuMines(board, mineCount, generateCoord);
    EXPECT_EQ(static_cast<int>(board[1][1].owner), static_cast<int>(Owner::Cpu));
}*/
TEST(gameTests, should_return_false_when_trying_to_shoot_invalid_coordinate)
{
    Board board(4, 5);
    Player player(5);
    int x = player.playerMines;

    EXPECT_FALSE(shoot(7, 8, board.grid.at(0).size(), board.grid.size(), x, x, board.grid));
}
/*
TEST(gameTests, should_destroy_mine_when_trying_to_guess_it)
{
    Board board(4, 5);
    Player player(5);
    setCellStatus(board.grid, 2, 3, Owner::Player);
    EXPECT_EQ(board.grid[2][3].owner, 'J');
    int minesLeft = player.playerMines;
    shoot(2, 3, board.grid.at(0).size(), board.grid.size(), minesLeft, minesLeft, board.grid);
    EXPECT_EQ(static_cast<int>(board.grid[2][3].owner), static_cast<int>(Owner::Destroy));
}*/
} // namespace gameTests