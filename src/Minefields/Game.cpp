#include <Minefields/Board.h>
#include <Minefields/Cell.h>
#include <Minefields/Game.h>
#include <Minefields/Mine.h>
#include <Minefields/Player.h>
#include <Minefields/Utils.h>

#include <iostream>
#include <string>
#include <vector>

void printBoard(std::vector<std::vector<Cell>> const& board)
{
    size_t height = board.size();
    size_t width = board[0].size();

    std::cout << "\n   ";
    for (size_t i = 0; i < width; ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n' << "  ";
    for (size_t i = 0; i < width; ++i)
    {
        std::cout << "--";
    }
    std::cout << '\n';

    for (size_t y = 0; y < height; ++y)
    {
        std::cout << y << "| ";
        for (size_t x = 0; x < width; ++x)
        {
            std::cout << static_cast<char>(board[y][x].owner) << ' ';
        }
        std::cout << '\n';
    }
}

void placePlayerMines(std::vector<std::vector<Cell>>& board, int mineCount)
{
    unsigned int placed = 0;
    unsigned int x = 0;
    unsigned int y = 0;
    int boardHeight = static_cast<int>(board.size());
    int boardWidth = static_cast<int>(board[0].size());
    while (placed < mineCount)
    {
        std::cout << "\n[Mines left to place: " + std::to_string(mineCount - placed) + "]\n";
        x = inputFunc("enter X: ");
        y = inputFunc("Enter Y: ");

        if (y < 0 || y >= boardHeight || x < 0 || x >= boardWidth)
        {
            std::cout << "Out of range.\n";
            continue;
        }

        if (board[y][x].owner == Owner::Disabled)
        {
            std::cout << "This cell is disabled.\n";
        }
        else if (board[y][x].owner == Owner::None)
        {
            setCellStatus(board, x, y, Owner::Player);
            placed++;
        }
        else
        {
            std::cout << "There is already a mine there.\n";
        }
    }
}

void placeCpuMines(std::vector<std::vector<Cell>>& board, int mineCount, CoordGenerator const& generateCoord)
{
    int placed = 0;

    while (placed < mineCount)
    {
        auto [x, y] = generateCoord();

        if (board[y][x].owner == Owner::Disabled)
        {
            continue;
        }

        if (board[y][x].owner == Owner::Player)
        {
            setCellStatus(board, x, y, Owner::Shared);
            placed++;
        }
        else if (board[y][x].owner == Owner::None)
        {
            setCellStatus(board, x, y, Owner::Cpu);
            placed++;
        }
    }
}
void playTurns(int height, int width, int totalMines, CoordGenerator const& generateCoord)
{
    int playerMinesLeft = totalMines;
    int cpuMinesLeft = totalMines;

    Board gameBoard(width, height);
    auto& board = gameBoard.grid;

    placePlayerMines(board, playerMinesLeft);
    placeCpuMines(board, cpuMinesLeft, generateCoord);

    while (playerMinesLeft > 0 && cpuMinesLeft > 0)
    {
        std::cout << "\n===== NEW ROUND =====\n";

        std::vector<std::vector<bool>> matrix(height, std::vector<bool>(width, false));

        std::cout << "\n--- Player's turn ---\n";
        playerTurn(board, matrix, width, height, playerMinesLeft, cpuMinesLeft);

        if (cpuMinesLeft <= 0)
        {
            break;
        }

        std::cout << "\n--- CPU's turn ---\n";
        cpuTurn(board, matrix, width, height, playerMinesLeft, cpuMinesLeft, generateCoord);

        printBoard(board);
        std::cout << "\nMines left - Player: " << playerMinesLeft << ", CPU: " << cpuMinesLeft << "\n";
    }
}
void playerTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft)
{
    bool validInput = false;

    for (int i = 0; i < playerMinesLeft; ++i)
    {
        int x = 0;
        int y = 0;
        validInput = false;
        while (!validInput)
        {
            std::cout << "Shoot " << (i + 1) << " of " << playerMinesLeft << "\n";
            std::cout << "Shoot at X: ";
            std::cin >> x;
            std::cout << "Shoot at Y: ";
            std::cin >> y;

            shoot(x, y, width, height, cpuMinesLeft, playerMinesLeft, board);
        }
    }
}

    void cpuTurn(std::vector<std::vector<Cell>> & board, std::vector<std::vector<bool>> & matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft, CoordGenerator const& generateCoord)
    {
        for (int i = 0; i < cpuMinesLeft; ++i)
        {
            int x = 0;
            int y = 0;
            do
            {
                auto [randX, randY] = generateCoord();
                y = randY;
                x = randX;
            } while (matrix[y][x]);

            matrix[y][x] = true;

            std::cout << "CPU shoots at (" << x << ", " << y << ")\n";

            if (board[y][x].owner == Owner::Player)
            {
                std::cout << "CPU destroyed one of your mines!\n";
                if (board[y][x].mine)
                    board[y][x].mine->status = Mine::Status::Destroyed;
                setCellStatus(board, x, y, Owner::Destroy);
                playerMinesLeft--;
            }
            else if (board[y][x].owner == Owner::Shared)
            {
                std::cout << "CPU destroyed shared mine!\n";
                if (board[y][x].mine)
                    board[y][x].mine->status = Mine::Status::Destroyed;
                setCellStatus(board, x, y, Owner::Destroy);
                playerMinesLeft--;
                cpuMinesLeft--;
            }
            else
            {
                std::cout << "CPU missed.\n";
                setCellStatus(board, x, y, Owner::Disabled);
            }

            if (playerMinesLeft <= 0)
            {
                break;
            }
        }
    }


    void setCellStatus(std::vector<std::vector<Cell>> & board, unsigned int x, unsigned int y, Owner owner)
    {
        board[y][x].owner = owner;
        if (owner != Owner::Disabled && owner != Owner::Destroy)
        {
            board[y][x].mine = Mine{};
        }
    }

    bool shoot(int const& x, int const& y, int const& width, int const& height, int& cpuMinesLeft, int& playerMinesLeft, std::vector<std::vector<Cell>>& board)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            std::cout << "Out of range.\n";
            return false;
        }
        if (board[y][x].owner == Owner::Disabled)
        {
            std::cout << "You already shot there.\n";
            return false;
        }
        else
        {
            if (board[y][x].owner == Owner::Cpu)
            {
                std::cout << "You hit a CPU mine!\n";
                if (board[y][x].mine)
                    board[y][x].mine->status = Mine::Status::Destroyed;

                board[y][x].owner = Owner::Destroy;
                cpuMinesLeft--;
            }
            else if (board[y][x].owner == Owner::Shared)
            {
                std::cout << "Shared mine destroyed!\n";
                if (board[y][x].mine)
                    board[y][x].mine->status = Mine::Status::Destroyed;
                board[y][x].owner = Owner::Destroy;
                playerMinesLeft--;
                cpuMinesLeft--;
            }
            else
            {
                std::cout << "Missed.\n";
                board[y][x].owner = Owner::Disabled;
            }
        }
        return true;
    }
