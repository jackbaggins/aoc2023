#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

/*
    Essentially reusing the solution from part 1
    Removing unused portions (game total, input comparison for limits)
    Adding two parts - the multiplication of the "max" for each game, which
        ends up being the min required
    Summation of all of the totals of the powers

    I think the "gotcha" in this one may have been the size of the final number?
    This would have wrapped a signed int (4 bytes - max value of 65535)
    Using an unsigned int gives plenty of breathing room (max value of 32-bit unsigned int is 4,294,697,295)
        while using the same amount of memory
*/

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << argc;
        std::cerr << "Expects: " << argv[0] << " <inFilename>\n";
        return 1;
    }

    // Pull input from first arg
    std::ifstream inFile(argv[1]);
    std::string line;
    
    // Not sure how big the sum might be, but adding multiples on a dataset of this size could get large
    unsigned int powerCubes = 0, sumPowers = 0;

    // Start parse loop for each line
    while (getline(inFile, line))
    {
        std::string gamePossible;
        std::istringstream lineStream(line);
        std::string textHolder;
        int maxRed = 0, maxGreen = 0, maxBlue = 0, gameNumber = 0;
        
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
        
        // Do powers, add to summation
        powerCubes = (maxRed*maxGreen*maxBlue);
        sumPowers += powerCubes;

        std::cout << "Game #" << gameNumber << " Max Red: " << maxRed << ", Max Green: " << maxGreen << ", Max Blue: " << maxBlue << ", Power: " << powerCubes << " Sum: " << sumPowers << std::endl;
    }
    std::cout << "Total Sum of Powers: " << sumPowers << std::endl;
    return 0;
}
