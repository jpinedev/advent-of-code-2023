#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

const char* INPUT = "inputs/day11.txt";

struct GalaxyLoc
{
    long x, y;
};

long ManhattanDistance(const GalaxyLoc& lhs, const GalaxyLoc& rhs)
{
    return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
}

vector<GalaxyLoc> FindGalaxies()
{
    ifstream infile(INPUT);

    vector<GalaxyLoc> galaxies;

    string line;
    long y = 0;
    while (infile.good() && !infile.eof())
    {
        if (!getline(infile, line))
            break;

        auto iter = line.begin();
        auto end = line.end();
        while (iter != end)
        {
            iter = find(iter, end, '#');
            if (iter == end)
                break;

            long x = iter - line.begin();
            galaxies.push_back({x, y});
            ++iter;
        }

        ++y;
    }

    return galaxies;
}

void ExpandRow(vector<GalaxyLoc>& universe, long row, long expansionFactor)
{
    for (auto& galaxy : universe)
    {
        if (galaxy.y > row) galaxy.y += expansionFactor - 1;
    }
}
void ExpandCol(vector<GalaxyLoc>& universe, long col, long expansionFactor)
{
    for (auto& galaxy : universe)
    {
        if (galaxy.x > col) galaxy.x += expansionFactor - 1;
    }
}


void ExpandUniverse(vector<GalaxyLoc>& universe, long expansionFactor)
{
    long maxX = 0, maxY = 0;
    unordered_set<long> nonEmptyRows, nonEmptyCols;
    for (auto& galaxy : universe)
    {
        maxX = max(maxX, galaxy.x);
        maxY = max(maxY, galaxy.y);

        nonEmptyCols.insert(galaxy.x);
        nonEmptyRows.insert(galaxy.y);
    }

    for (long col = maxX; col >= 0; --col)
    {
        if (nonEmptyCols.count(col) != 0)
            continue;

        ExpandCol(universe, col, expansionFactor);
    }

    for (long row = maxY; row >= 0; --row)
    {
        if (nonEmptyRows.count(row) != 0)
            continue;

        ExpandRow(universe, row, expansionFactor);
    }
}

long SumDistancesBetweenAllGalaxies(const vector<GalaxyLoc>& universe)
{
    long sum = 0;

    for (auto firstIt = universe.begin(); firstIt != universe.end(); ++firstIt)
    {
        for (auto secondIt = firstIt + 1; secondIt != universe.end(); ++secondIt)
        {
            sum += ManhattanDistance(*firstIt, *secondIt);
        }
    }

    return sum;
}

void Part1(vector<GalaxyLoc> inputs)
{
    ExpandUniverse(inputs, 2);
    cout << "Part 1: " << SumDistancesBetweenAllGalaxies(inputs) << endl;
}


void Part2(vector<GalaxyLoc> inputs)
{
    ExpandUniverse(inputs, 1000000);
    cout << "Part 2: " << SumDistancesBetweenAllGalaxies(inputs) << endl;
}

int main()
{
  vector<GalaxyLoc> inputs = FindGalaxies();
  Part1(inputs);
  Part2(inputs);
  return 0;
}
