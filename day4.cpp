#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

const char* INPUT = "inputs/day4.txt";

#ifdef EXAMPLE
typedef array<int, 5> Winners;
typedef array<int, 8> OwnNumbers;
#else
typedef array<int, 10> Winners;
typedef array<int, 25> OwnNumbers;
#endif

struct Scratchcard
{
    size_t id;
    Winners winners;
    OwnNumbers ownNumbers;

    int TotalPoints() const
    {
        int points = 0b1; // Start with 1 bit so we can bitshift
        
        for (auto number : ownNumbers)
        {
            // Linear search should be faster than set operations at this scale
            if (find(winners.begin(), winners.end(), number) != winners.end())
                points <<= 1; // Bitshift up for another power of 2
        }

        return points >> 1; // Compensate for original bit
    }

    int CountMatches() const
    {
        int matches = 0;
        
        for (auto number : ownNumbers)
        {
            // Linear search should be faster than set operations at this scale
            if (find(winners.begin(), winners.end(), number) != winners.end())
                ++matches;
        }

        return matches;
    }
};

vector<Scratchcard> ParseInputs()
{
    vector<Scratchcard> inputs;

    ifstream infile(INPUT);

    string line;
    while (infile.good() && !infile.eof())
    {
        if (!getline(infile, line))
            break;

        inputs.emplace_back();
        Scratchcard& card = inputs.back();

        string _throwAwayInput;
        stringstream stream(line);
        stream >> _throwAwayInput >> card.id >> _throwAwayInput; // Card #:
        --card.id; // # is 1 indexed, we want 0 indexed for easier memoization

        for (auto& winner : card.winners)
        {
            stream >> winner;
        }
        stream >> _throwAwayInput; // |
        for (auto& ownNumber : card.ownNumbers)
        {
            stream >> ownNumber;
        }
    }

    return inputs;
}

void Part1(const vector<Scratchcard> &inputs)
{
    int sum = 0;

    for (auto& card : inputs)
    {
        sum += card.TotalPoints();
    }
    
    cout << "Part 1: " << sum << endl;
}

void Part2(const vector<Scratchcard> &inputs)
{
    vector<size_t> memo;
    memo.reserve(inputs.size());
    vector<int> additionalCardIds;

    for (auto& card : inputs)
    {
        memo.push_back(card.CountMatches());

        size_t numToAppend = memo.back();
        if (numToAppend == 0)
            continue;
        
        for (size_t ii = card.id + 1; ii < inputs.size() && numToAppend > 0; ++ii, --numToAppend)
        {
            additionalCardIds.push_back(ii);
        }
    }

    for (size_t ii = 0; ii < additionalCardIds.size(); ++ii)
    {
        size_t cardId = additionalCardIds.at(ii);
        size_t numToAppend = memo.at(cardId);
        
        for (size_t ii = 0; ii < numToAppend; ++ii)
        {
            additionalCardIds.push_back(cardId + ii + 1);
        }
    }
    
    cout << "Part 2: " << inputs.size() + additionalCardIds.size() << endl;
}

int main()
{
  vector<Scratchcard> inputs = ParseInputs();
  Part1(inputs);
  Part2(inputs);
  return 0;
}
