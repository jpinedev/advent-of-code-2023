#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const char* INPUT = "inputs/day6.txt";

struct Race
{
    size_t time;
    size_t distanceToBeat;
};

vector<Race> ParseInputs()
{
    vector<Race> inputs;

    ifstream infile(INPUT);

    string timesLine, distancesLine;
    getline(infile, timesLine);
    getline(infile, distancesLine);

    string _ignoreFirst;
    stringstream times(timesLine), distances(distancesLine);
    times >> _ignoreFirst;
    distances >> _ignoreFirst;

    Race nextRace;
    while (times >> nextRace.time && distances >> nextRace.distanceToBeat)
    {
        inputs.push_back(nextRace);
    }

    return inputs;
}

size_t CountWinningStrategies(const Race& race)
{
    size_t count = 0;

    for (size_t msCharging = 1; msCharging < race.time; ++msCharging)
    {
        if (msCharging * (race.time - msCharging) > race.distanceToBeat)
            ++count;
    }

    return count;
}

void Part1(const vector<Race> &inputs)
{
    size_t product = 1;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        product *= CountWinningStrategies(*it);

    cout << "Part 1: " << product << endl;
}

// void Part2(const vector<Race> &inputs)
// {

// }

int main()
{
  vector<Race> inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
