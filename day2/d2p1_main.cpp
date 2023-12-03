#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

/*
    Thought process/notes
    Read input from cmd as first argument
    Also take in the provided maximums as command line arguments
    Determine maximum values of Red, Green, and Blue from each row/groups
    Compare max to find which rows are possible or impossible
    Add together sum of each row
*/

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        std::cout << argc;
        std::cerr << "Expects: " << argv[0] << " <inFilename> -R <RedLimiter (Int)> -G <GreenLimiter (int)> -B <BlueLimiter (int)>\n";
        return 1;
    }

    // Init command line arguments used to check maxes later
    int rCheck = 0, gCheck = 0, bCheck = 0;

    // Parsing command line arguments
    for (auto i = 2; i < argc; i += 2)
    {
        std::string arg = argv[i];
        if (arg == "-R")
        {
            rCheck = std::stoi(argv[i + 1]);
        }
        else if (arg == "-G")
        {
            gCheck = std::stoi(argv[i + 1]);
        }
        else if (arg == "-B")
        {
            bCheck = std::stoi(argv[i + 1]);
        }
    }

    // Pull input from first arg
    std::ifstream inFile(argv[1]);
    std::string line;
    int gameTotal = 0;

    // Start parse loop for each line
    while (getline(inFile, line))
    {
        std::string gamePossible;
        std::istringstream lineStream(line);
        std::string textHolder;
        int gameNumber = 0;
        int maxRed = 0, maxGreen = 0, maxBlue = 0;

        // Extract the game number, and store for use later in gameNumber
        lineStream >> textHolder >> gameNumber;
        
        // Move the lineStream up to the colon
        getline(lineStream, textHolder, ':');
        int cubeCount = 0;

        // Read in each game group and extract text and integers
        // ALSO ACCOUNT FOR COMMAS IN THE CUBE COLORS - THIS TOOK SO LONG TO FIGURE OUT...
        while (getline(lineStream, textHolder, ';'))
        {
            std::istringstream colorStream(textHolder);
            std::string cubeColor;
            while (colorStream >> cubeCount >> cubeColor)
            {
                if (cubeColor == "red" || cubeColor == "red,")
                {
                    maxRed = std::max(maxRed, cubeCount);
                    // std::cout << maxRed << std::endl;
                }
                else if (cubeColor == "green" || cubeColor == "green,")
                {
                    maxGreen = std::max(maxGreen, cubeCount);
                }
                else if (cubeColor == "blue" || cubeColor == "blue,")
                {
                    maxBlue = std::max(maxBlue, cubeCount);
                }
            }
        }
        // Do checks of each game compared to parameter set limits
        if (maxBlue <= bCheck && maxRed <= rCheck && maxGreen <= gCheck)
        {
            gameTotal += gameNumber;
            gamePossible = "yes";
        }
        else
        {
            gamePossible = "no";
        }

        std::cout << "Game #" << gameNumber << " Max Red: " << maxRed << ", Max Green: " << maxGreen << ", Max Blue: " << maxBlue << ", Game Total: " << gameTotal << " -- Game Possible? " << gamePossible << std::endl;
    }
    std::cout << "Overall possible game total: " << gameTotal << std::endl;
    return 0;
}
