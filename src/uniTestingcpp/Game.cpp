#include <iostream>
#include <vector>
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Utils.h"
#include "Mine.h"
#include "Cell.h"

void printBoard(const std::vector<std::vector<Cell>>& board) 
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
        unsigned int  x = 0;
        unsigned int y = 0;
        int boardHeight = static_cast<int>(board.size());
        int boardWidth = static_cast<int>(board[0].size());
        while (placed < mineCount) 
        {
            std::cout << "\n[Mines left to place: " << (mineCount - placed) << "]\n";
            std::cout << "Enter X: "; 
            std::cin >> x;
            std::cout << "Enter Y: ";
            std::cin >> y;

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
                board[y][x].owner = Owner::Player;
                board[y][x].mine = Mine{};
                placed++;
            } 
            else 
            {
                std::cout << "There is already a mine there.\n";
            }
        }
}

void placeCpuMines(std::vector<std::vector<Cell>>& board, int mineCount, const CoordGenerator& generateCoord)
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
            board[y][x].owner = Owner::Shared;
            board[y][x].mine = Mine{};
            placed++;
        } 
        else if (board[y][x].owner == Owner::None)
        {
            board[y][x].owner = Owner::Cpu;
            board[y][x].mine = Mine{};
            placed++;
        }
    }
}

void playTurns(int height, int width, int totalMines, const CoordGenerator& generateCoord)
{
    int playerMinesLeft = totalMines;
    int cpuMinesLeft = totalMines;
    bool validInput = false;

    Board gameBoard(width, height);
    auto& board = gameBoard.grid;

    placePlayerMines(board, playerMinesLeft);
    placeCpuMines(board, cpuMinesLeft, generateCoord);

    while (playerMinesLeft > 0 && cpuMinesLeft > 0) 
    {
        std::cout << "\n===== NEW ROUND =====\n";

        std::vector<std::vector<bool>> matrix(height, std::vector<bool>(width, false));

        std::cout << "\n--- Player's turn ---\n";
        for (int i = 0; i < playerMinesLeft; ++i) 
        {
            int x = 0;
            int y = 0;
            validInput = false;
            while (!validInput)
            {
                std::cout << "Shot " << (i + 1) << " of " << playerMinesLeft << "\n";
                std::cout << "Shoot at X: "; 
                std::cin >> x;
                std::cout << "Shoot at Y: ";
                std::cin >> y;

                if (x < 0 || x >= width || y < 0 || y >= height)
                {
                    std::cout << "Out of range.\n";
                    continue;
                }
                if (matrix[y][x]) 
                {
                    std::cout << "You already shot there.\n";
                    continue;
                }
                else 
                {
                    validInput = true;
                }
            }

            matrix[y][x] = true;

            if (board[y][x].owner == Owner::Cpu) 
            {
                std::cout << "You hit a CPU mine!\n";
                if (board[y][x].mine) board[y][x].mine->status = Mine::Status::Destroyed;
                board[y][x].owner = Owner::Destroy;
                cpuMinesLeft--;
            } 
            else if (board[y][x].owner == Owner::Shared) 
            {
                std::cout << "Shared mine destroyed!\n";
                if (board[y][x].mine) board[y][x].mine->status = Mine::Status::Destroyed;
                board[y][x].owner = Owner::Destroy;
                playerMinesLeft--;
                cpuMinesLeft--;
            } 
            else 
            {
                std::cout << "Missed.\n";
                board[y][x].owner = Owner::Disabled;
            }

            if (cpuMinesLeft <= 0)
            {
                break;
            } 
        }

        if (cpuMinesLeft <= 0) 
        {
            break;
        }

        std::cout << "\n--- CPU's turn ---\n";
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
                if (board[y][x].mine) board[y][x].mine->status = Mine::Status::Destroyed;
                board[y][x].owner = Owner::Destroy;
                playerMinesLeft--;
            } 
            else if (board[y][x].owner == Owner::Shared) 
            {
                std::cout << "CPU destroyed shared mine!\n";
                if (board[y][x].mine) board[y][x].mine->status = Mine::Status::Destroyed;
                board[y][x].owner = Owner::Destroy;
                playerMinesLeft--;
                cpuMinesLeft--;
            } 
            else 
            {
                std::cout << "CPU missed.\n";
                board[y][x].owner = Owner::Disabled;
            }

            if (playerMinesLeft <= 0) 
            {
                break;
            }    
        }

        printBoard(board);
        std::cout << "\nMines left - Player: " << playerMinesLeft << ", CPU: " << cpuMinesLeft << "\n";
    }
        
    std::cout << "\n===== GAME OVER =====\n";
    if (playerMinesLeft == 0 && cpuMinesLeft == 0) 
    {
        std::cout << "It's a tie!\n";
    } 
    else if (playerMinesLeft == 0) 
    {
        std::cout << "CPU wins!\n";
    } 
    else
    {
        std::cout << "You win!\n";
    }
}
