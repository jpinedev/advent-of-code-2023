#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const char* INPUT = "inputs/day2.txt";

struct RGBCubes
{
    uint8_t red{0}, green{0}, blue{0};
    
    void AddCubes(const char* color, uint8_t amount)
    {
        switch (*color)
        {
        case 'r':
            red += amount;
            return;
        case 'g':
            green += amount;
            return;
        case 'b':
            blue += amount;
            return;
        default:
            throw runtime_error("invalid color '" + string(color) + "'");
        }
    }

    bool operator<=(const RGBCubes& other) const { return red <= other.red && green <= other.green && blue <= other.blue; }

    RGBCubes& Max(const RGBCubes& other)
    {
        red = max<uint8_t>(red, other.red);
        green = max<uint8_t>(green, other.green);
        blue = max<uint8_t>(blue, other.blue);
        return *this;
    }

    int GetPower() const { return (int)red * green * blue; }
};

struct Game
{
    uint64_t id;
    vector<RGBCubes> subsets;

    RGBCubes GetMaxSubset() const
    {
        RGBCubes maxSoFar;

        for (auto& subset : subsets)
        {
            maxSoFar.Max(subset);
        }

        return maxSoFar;
    }

    bool IsPossible(const RGBCubes& maxCubes) const { return GetMaxSubset() <= maxCubes; }
};

RGBCubes ParseSubset(const string& subsetStr)
{
    stringstream stream(subsetStr);
    RGBCubes subset;

    int amount;
    string color;
    while (stream >> amount >> color)
    {
        subset.AddCubes(color.c_str(), (uint8_t)amount);
    }
    
    return subset;
}

vector<RGBCubes> ParseSubsets(const string& subsetsStr)
{
    vector<RGBCubes> subsets;

    for (auto it = subsetsStr.begin(); it != subsetsStr.end(); )
    {
        auto nextSplit = std::find(it, subsetsStr.end(), ';');

        subsets.push_back(ParseSubset(std::string(it, nextSplit)));

        if (nextSplit == subsetsStr.end())
            break;

        it = nextSplit + 2;
    }
    
    return subsets;
}

void ParseGame(const string& line, Game& outGame)
{
    char subsetsCStr[256];
    sscanf(line.c_str(), "Game %llu: %[^\n]", &outGame.id, subsetsCStr);

    outGame.subsets = ParseSubsets(subsetsCStr);
}

vector<Game> ParseInputs()
{
    vector<Game> inputs;

    ifstream infile(INPUT);

    string line;
    while (infile.good() && !infile.eof())
    {
        if (!getline(infile, line))
            break;

        inputs.emplace_back();
        ParseGame(line, inputs.back());
    }

    return inputs;
}

void Part1(const vector<Game> &inputs, const RGBCubes& cubesInBag)
{
    int sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        if (!it->IsPossible(cubesInBag))
            continue;

        sum += it->id;
    }

    cout << "Part 1: " << sum << endl;
}

void Part2(const vector<Game> &inputs)
{
    int sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        sum += it->GetMaxSubset().GetPower();

    cout << "Part 2: " << sum << endl;
}

int main()
{
  auto inputs = ParseInputs();
  Part1(inputs, RGBCubes{12, 13, 14});
  Part2(inputs);
  return 0;
}
