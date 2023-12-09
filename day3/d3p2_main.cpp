#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
    Takes a single input and returns


    Referenced documentation that was helpful
    https://stackoverflow.com/questions/42754672/c-read-in-a-file-like-a-grid
    https://www.geeksforgeeks.org/how-to-concatenate-two-integer-values-into-one/
    https://sentry.io/answers/char-to-int-in-c-and-cpp/

    Thought process/notes
    Pull all in to string vector (2d)
    Check each character in vector
    For each character, if it's a number, start grabbing and concat-ing
        After number has been contatenated; do checks all around to see if there's a symbol
        BOUNDS BOUNDS BOUNDS checking
        If symbol, set hit marker to 1
        Pass the location of the star to a vector array
        Pass the accumulated integer to a vector array
        When complete, pass the array of coordinates and integers to function
        Function will find all values where element [0] and [1] match (the coordinates of the star)
            Then take the [3] element and multiply them together
            While adding to a running total sum
*/

// Global vector, catches the star hit coordinates, along with the touching number
vector<vector<int>> starCoords;

// takes in no values, uses global starCoords vector array
// finds matches, multiplies, adds to total sum
// Returns the total of the multiples
unsigned long multiplyMatchingCoords()
{
    unsigned long sumTotal = {};
    for (size_t i = 0; i < starCoords.size(); ++i)
    {
        for (size_t j = i + 1; j < starCoords.size(); ++j)
        {
            // Coord check for match
            if (starCoords[i][0] == starCoords[j][0] && starCoords[i][1] == starCoords[j][1])
            {
                // Multiply integers that share a star touch
                // Also gives some output that was used for debugging initially, left it in
                int product = starCoords[i][2] * starCoords[j][2];
                cout << "Matching Coords: (" << starCoords[i][0] << ", " << starCoords[i][1]
                     << ") - Product: " << product << endl;
                sumTotal = sumTotal += product;
            }
        }
    }
    return sumTotal;
}

// Push discovered star coords and captured integers to array
void outStarCoords(int starI, int starJ, int capture)
{
    starCoords.push_back({starI, starJ, capture});
}

bool isStar(char checkChar)
{
    return checkChar == '*';
}

bool isNumber(char checkChar)
{
    return isdigit(checkChar);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Expects: " << argv[0] << " <inFilename>\n";
        return 1;
    }

    ifstream inFile(argv[1]);
    vector<string> gridParts;
    string lineBuffer;

    // Read the file in to a string vector
    // String types are already a vector, so a vector
    // Of strings is a 2d vector by default
    // Calculate row count for use later
    int rowCount = {};
    int numCapture = {};
    int strToNum = {};
    while (getline(inFile, lineBuffer))
    {
        gridParts.push_back(lineBuffer);
        rowCount++;
    }

    int sumTotal = {};
    // Each line of the inFile
    for (int i = 0; i < rowCount; i++)
    {
        // Rows of array
        for (int j = 0; j < gridParts[i].length(); j++)
        {
            // Columns of array
            if (isNumber(gridParts[i][j]))
            {
                int capture = {};
                int touchStar = {};
                int newI = {};
                int newJ = {};

                // Used so that the j (rows) variable can be reset after the number has been accumulated and stored
                int startJ = 0;

                // If a number is hit, start accumulating it
                while (j < gridParts[i].size() && isNumber(gridParts[i][j]))
                {
                    // Subract 0 is ASCII convert char to int https://sentry.io/answers/char-to-int-in-c-and-cpp
                    capture = capture * 10 + (gridParts[i][j] - '0');
                    j++;
                    startJ++;
                }

                // Reset j to init value, number has been captured
                j = j - startJ;

                while (j < gridParts[i].size() && isNumber(gridParts[i][j]))
                {
                    // For each number that's hit, check all 8 sides
                    // Also account for bounds - probably more effecient way to do this
                    for (int di = -1; di <= 1; ++di)
                    {
                        for (int dj = -1; dj <= 1; ++dj)
                        {
                            // Don't check the grabbed number - both [i][j] with no -- or ++
                            if (di == 0 && dj == 0)
                                continue;

                            int newI = i + di;
                            int newJ = j + dj;

                            // Check bounds - newI and newJ are negative, we're outside the array - segfault
                            if (newI >= 0 && newI < gridParts.size() && newJ >= 0 && newJ < gridParts[newI].size())
                            {
                                // Safe to access the adjacent value
                                // Set touchStar to 1, because the number touches a star
                                // touchStar is used as a flag to prevent star coords from being
                                // added multiple times for each number.
                                // if it touches once, that's all we need
                                if (isStar(gridParts[newI][newJ]) && touchStar != 1)
                                {
                                    outStarCoords(newI, newJ, capture);
                                    touchStar = 1;
                                }
                            }
                        }
                    }
                    j++;
                }
            }
        }
    }
    
    // Answer out
    unsigned long total = multiplyMatchingCoords();
    cout << "Sum Total of Products: " << total << endl;
    inFile.close();
    return 0;
}