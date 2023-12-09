import sys

# Thoughts/notes
#   Split the strings
#   Convert to integers
#   Put matches in a set()
#   Push number of matches to geometric series formula
#   Keep running total of the returned series output

# Geometrics series https://www.cuemath.com/geometric-series-formula/
def geometricSeries(setCount):
    points = (2**(setCount - 1))
    return points

def findWinningNumberss(filePath):
    totalPoints = 0
    with open(filePath, 'r') as file:
        for line in file:
            # Text parsing, split by characters in input, convert from string to int
            label, numbers = line.split(':')
            leftPart, rightPart = numbers.split('|')
            leftNumbers = [int(num) for num in leftPart.split() if num.isdigit()]
            rightNumbers = [int(num) for num in rightPart.split() if num.isdigit()]

            # Identify winning number matches and output
            # https://realpython.com/python-sets/
            winningMatches = set(leftNumbers).intersection(rightNumbers)
            if winningMatches:
                print(f"Common numbers for {label}: {winningMatches}")
                points = geometricSeries(len(winningMatches))
                totalPoints += points
                print(f"Total Points: {totalPoints}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python d4p1_main.py <filePath>")
        sys.exit(1)

    totalPoints = 0
    filePath = sys.argv[1]
    findWinningNumberss(filePath)

if __name__ == "__main__":
    main()
