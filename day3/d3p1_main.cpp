#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
    Referenced documentation that was helpful
    https://stackoverflow.com/questions/42754672/c-read-in-a-file-like-a-grid
    https://www.geeksforgeeks.org/how-to-concatenate-two-integer-values-into-one/
    https://sentry.io/answers/char-to-int-in-c-and-cpp/

    Thought process/notes
    Pull all in to string vector (2d)
    Check each character in vector
    For each character, if it's a number, start grabbing and concat-ing
        While grabbing numbers, do checks all around to see if there's a symbol
        BOUNDS BOUNDS BOUNDS
        If symbol, set hit marker to 1
        If hit marker is 1, add to a running sum
*/

bool isSymbol(char checkChar)
{
    return !isdigit(checkChar) && checkChar != '.';
}

bool isNumber(char checkChar)
{
    return isdigit(checkChar);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << argc;
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
                int toSum = {};

                // If a number is hit, start accumulating it
                while (j < gridParts[i].size() && isNumber(gridParts[i][j]))
                {
                    // Subract 0 is ASCII convert char to int https://sentry.io/answers/char-to-int-in-c-and-cpp
                    capture = capture * 10 + (gridParts[i][j] - '0');

                    // For each number that's hit, check all 8 sides
                    // Also account for bounds - idk if this is the best way to do this, gave headache
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
                                // Set toSum to 1, because the number touches a symbol
                                if (isSymbol(gridParts[newI][newJ]))
                                {
                                    toSum = 1;
                                }
                            }
                        }
                    }
                    j++;
                }
                // If the number touched a symbol (toSum == 1), add the accumulated integer to a running total
                if (toSum == 1)
                {
                    sumTotal = sumTotal + capture;
                    toSum = 0;
                }
            }
        }
    }
    cout << "Total: " << sumTotal << endl;

    inFile.close();
    return 0;
}