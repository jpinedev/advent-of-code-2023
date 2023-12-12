#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <memory>
#include <sstream>
#include <limits>

using namespace std;

const char* INPUT = "inputs/day5.txt";

struct Range
{
    long lower, length, newLower;

    Range(long lower, long length, long newLower) : lower(lower), length(length), newLower(newLower) {}

    bool IsInRange(long num) const { return num >= lower && num - lower < length; }

    long Map(long num) const { return num - lower + newLower; }

    bool operator<(const Range& other) const { return lower < other.lower; }
};

struct SortedMapping
{
    SortedMapping(const vector<Range>& ranges) : ranges(ranges)
    {
        sort(this->ranges.begin(), this->ranges.end());
    }
    
    long Map(long num) const
    {
        for (auto& range : ranges)
        {
            if (range.IsInRange(num))
                return range.Map(num);
        }

        return num;
    }

private:
    vector<Range> ranges;
};

struct Mappings
{
    Mappings(const array<vector<Range>, 7>& mappings) :
        seedToSoil(mappings.at(0)),
        soilToFert(mappings.at(1)),
        fertToWater(mappings.at(2)),
        waterToLight(mappings.at(3)),
        lightToTemp(mappings.at(4)),
        tempToHumid(mappings.at(5)),
        humidToLoc(mappings.at(6)),
        sortedMappings({&seedToSoil, &soilToFert, &fertToWater, &waterToLight, &lightToTemp, &tempToHumid, &humidToLoc}) {}

    const SortedMapping seedToSoil;
    const SortedMapping soilToFert;
    const SortedMapping fertToWater;
    const SortedMapping waterToLight;
    const SortedMapping lightToTemp;
    const SortedMapping tempToHumid;
    const SortedMapping humidToLoc;
    const array<const SortedMapping*,7> sortedMappings;

    long SeedToLoc(long seed) const
    {
        long soFar = seed;
        for (auto& mapping : sortedMappings)
        {
            soFar = mapping->Map(soFar);
        }
        return soFar;
    }
};

struct Inputs
{
    vector<long> seeds;
    Mappings mappings;
};

vector<long> ParseSeeds(const string& seedsLine)
{
    stringstream stream(seedsLine);

    string _ignoreLabel;
    stream >> _ignoreLabel;

    vector<long> seeds;
    long seed;
    while (stream >> seed)
    {
        seeds.push_back(seed);
    }
    return seeds;
}

Range ParseRange(const string& line)
{
    long lower, length, newLower;
    stringstream stream(line);
    stream >> newLower >> lower >> length;
    return Range(lower, length, newLower);
}

vector<Range> ParseMapping(istream& in)
{
    vector<Range> ranges;

    ws(in);
    string line;
    getline(in, line); // Ignore label line
    while (in.good() && !in.eof())
    {
        if (!getline(in, line) || line.empty())
            break;

        ranges.push_back(ParseRange(line));
    }

    return ranges;
}

Inputs ParseInputs()
{
    ifstream infile(INPUT);

    string line;
    getline(infile, line);

    vector<long> seeds = ParseSeeds(line);
    array<vector<Range>, 7> mappings;

    for (long ii = 0; ii < 7; ++ii)
    {
        mappings.at(ii) = ParseMapping(infile);
    }

    return Inputs{seeds, Mappings(mappings)};
}

void Part1(const Inputs& inputs)
{
    long lowest = numeric_limits<long>::max();
    for (auto seed : inputs.seeds)
    {
        long location = inputs.mappings.SeedToLoc(seed);
        if (location < lowest)
            lowest = location;
    }

    cout << "Part 1: " << lowest << endl;
}

// void Part2(const vector<string> &inputs)
// {

// }

int main()
{
  Inputs inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
