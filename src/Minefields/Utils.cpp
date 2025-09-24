#include <Minefields/Utils.h>

void inputBoardSize(int& height, int& width, std::ostream& outputStream, std::istream& inputStream)
{
    static const unsigned int MaxSize = 15;
    static const unsigned int MinSize = 5;
    do 
    {
        outputStream << "Enter height (" << MinSize << '-' << MaxSize << "): ";
        inputStream >> height;
    } while (height < MinSize || height > MaxSize);

    do {
        outputStream << "Enter width (" << MinSize << '-' << MaxSize << "): ";
        inputStream >> width;
    } while (width < MinSize || width > MaxSize);
}

int inputMines(Player& player, std::ostream& outputStream, std::istream& inputStream)
{
    static unsigned int const MaxMines = 4;
    static unsigned int const MinMines = 2;
    std::string message = "Enter the number of mines (" + std::to_string(MinMines) + " to " + std::to_string(MaxMines) + "): ";
    do
    {
        player.playerMines = inputInt(message, outputStream, inputStream);
    } while (player.playerMines < MinMines || player.playerMines > MaxMines);
    return player.playerMines;
}


std::pair<int, int> generateRandomCoord(int width, int height) 
{
    return { rand() % width, rand() % height };
}


int inputInt(std::string const& message, std::ostream& outputStream, std::istream& inputStream)
{
    int x = 0;
    outputStream << message;
    inputStream >> x;
    return x;
}