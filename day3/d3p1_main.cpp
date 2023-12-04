#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
    https://stackoverflow.com/questions/42754672/c-read-in-a-file-like-a-grid
    https://www.geeksforgeeks.org/how-to-concatenate-two-integer-values-into-one/
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
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < gridParts[i].length(); j++)
        {
            // cout << gridParts[i][j];
            if (isNumber(gridParts[i][j]))
            {
                int capture = {};
                int toSum = {};
                while (j < gridParts[i].size() && isNumber(gridParts[i][j]))
                {
                    capture = capture * 10 + (gridParts[i][j] - '0'); // Convert char to int and append
                    for (int di = -1; di <= 1; ++di)
                    {
                        for (int dj = -1; dj <= 1; ++dj)
                        {
                            // Skip the center cell
                            if (di == 0 && dj == 0)
                                continue;

                            int newI = i + di;
                            int newJ = j + dj;

                            // Check bounds
                            if (newI >= 0 && newI < gridParts.size() && newJ >= 0 && newJ < gridParts[newI].size())
                            {
                                // Now it's safe to access grid[newI][newJ]
                                if (isSymbol(gridParts[newI][newJ]))
                                {
                                    toSum = 1;
                                    // cout << "hit" << endl;
                                }
                            }
                        }
                    }
                    j++;

                }
                if (toSum == 1)
                {
                    // cout << capture << endl;
                    sumTotal = sumTotal + capture;
                    toSum = 0;
                }
                // cout << "Captured: " << capture << endl;
                
            }
            
        }
        
    }
    cout << "Total: " << sumTotal << endl;

    inFile.close();
    return 0;
}