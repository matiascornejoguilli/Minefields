#include <gtest/gtest.h>

#include "Minefields/Utils.h"
#include <sstream>
#include <string>
/*
TEST(inputBoardSizeTest, check_valid_inputs)
{
    std::stringstream input;
    int height = 6;
    int width = 6;
    input << height;
    input << width;

    std::ostringstream output;

    //EXPECT_NO_FATAL_FAILURE(inputBoardSize(height, width, output, input));
}

TEST(inputMinesTest, check_valid_inputs)
{
    std::stringstream input("2");
    std::ostringstream output;
    Player player;
    
    EXPECT_EQ(inputMines(player, output, input), 2);
}


TEST(inputMinesTest, check_invalid_inputs)
{
    std::stringstream input("1");
    std::ostringstream output;
    Player player;

    EXPECT_EQ(inputMines(player, output, input), 0);
}*/

TEST(InputIntTest, check_valid_input)
{
    std::stringstream input("42");
    std::ostringstream output;

    int result = inputInt("Ingrese un número: ", output, input);

    EXPECT_EQ(result, 42);
    EXPECT_EQ(output.str(), "Ingrese un número: ");
}

TEST(InputIntTest, check_invalid_input)
{
    std::stringstream input("abc\n42");
    std::ostringstream output;

    int result = inputInt("Ingrese un número: ", output, input);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output.str(), "Ingrese un número: ");
}

TEST(InputIntTest, check_empty_input)
{
    std::stringstream input("");
    std::ostringstream output;

    int result = inputInt("Ingrese un número: ", output, input);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output.str(), "Ingrese un número: ");
}