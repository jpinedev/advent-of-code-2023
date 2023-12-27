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

void ExpandRow(vector<GalaxyLoc>& universe, long row)
{
    for (auto& galaxy : universe)
    {
        if (galaxy.y > row) ++galaxy.y;
    }
}
void ExpandCol(vector<GalaxyLoc>& universe, long col)
{
    for (auto& galaxy : universe)
    {
        if (galaxy.x > col) ++galaxy.x;
    }
}


void ExpandUniverse(vector<GalaxyLoc>& universe)
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

        ExpandCol(universe, col);
    }

    for (long row = maxY; row >= 0; --row)
    {
        if (nonEmptyRows.count(row) != 0)
            continue;

        ExpandRow(universe, row);
    }
}

void Part1(const vector<GalaxyLoc> &inputs)
{
    long sum = 0;

    for (auto firstIt = inputs.begin(); firstIt != inputs.end(); ++firstIt)
    {
        // cout << firstIt - inputs.begin() + 1 << ":\n";
        for (auto secondIt = firstIt + 1; secondIt != inputs.end(); ++secondIt)
        {
            sum += ManhattanDistance(*firstIt, *secondIt);
        }
    }

    cout << "Part 1: " << sum << endl;
}

// void Part2(const vector<string> &inputs)
// {

// }

int main()
{
  vector<GalaxyLoc> inputs = FindGalaxies();

  ExpandUniverse(inputs);
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
