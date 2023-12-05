#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <optional>

using namespace std;

const char* INPUT = "inputs/day1.txt";

vector<string> ParseInputs()
{
    vector<string> inputs;

    ifstream infile(INPUT);

    string line;
    while (infile.good() && !infile.eof())
    {
        if (!getline(infile, line))
            break;
        inputs.push_back(line);
    }

    return inputs;
}

inline int CharToDigit(char ch) { return ch - '0'; }

// Assumes at least 2 digits in the string
int GetCalibrationValue(string str)
{
    int firstDigit = CharToDigit(*find_if(str.begin(), str.end(), [](unsigned char ch) { return isdigit(ch); }));
    int lastDigit = CharToDigit(*find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return isdigit(ch); }));

    return firstDigit * 10 + lastDigit;
}

void Part1(const vector<string> &inputs) {
    int sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        sum += GetCalibrationValue(*it);

    cout << "Part 1: " << sum << endl;
}

const array<string_view, 9> digitsAsNames{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

inline int GetDigitFromName(string_view& name)
{
    return find(digitsAsNames.begin(), digitsAsNames.end(), name) - digitsAsNames.begin() + 1;
}
inline size_t GetNameIndexFromDigit(int digit)
{
    return digit - 1;
}

optional<int> ReadAsDigit(string::const_iterator it, string::const_iterator end)
{
    if (end - it < 3u) // no digit name is less than 3 characters long
        return {};

    vector<string_view> possibleMatches(digitsAsNames.begin(), digitsAsNames.end());

    for (auto ii = 0u; ii < 5u && it != end && !possibleMatches.empty(); ++ii, ++it)
    {
        char nextCharToMatch = *it;

        auto toRemove = remove_if(possibleMatches.begin(), possibleMatches.end(), [ii, nextCharToMatch](const string_view str) { return str[ii] != nextCharToMatch; });

        if (toRemove != possibleMatches.end())
            possibleMatches.erase(toRemove, possibleMatches.end());

        if (possibleMatches.size() == 1 && possibleMatches.front().size() == ii + 1)
            break;
    }

    if (possibleMatches.empty())
        return {};

    auto& nameMatch = possibleMatches.front();
    return GetDigitFromName(nameMatch);
}

vector<int> GetAllDigitsInLine(const string line)
{
    vector<int> digits;

    for (auto it = line.begin(), itEnd = line.end(); it != itEnd; ++it)
    {
        if (isdigit((unsigned char)*it))
        {
            digits.push_back(CharToDigit(*it));
            continue;
        }

        auto digitOpt = ReadAsDigit(it, itEnd);
        if (!digitOpt.has_value())
            continue;

        int digit = digitOpt.value();
        digits.push_back(digit);
    }

    return digits;
}

// Assumes at least 1 digit (if only one digit, it will be repeated)
int GetCalibrationValue(const vector<int> digits)
{
    assert(digits.size() > 0);
    return digits.front() * 10 + digits.back();
}

void Part2(const vector<string> &inputs)
{
    int sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        sum += GetCalibrationValue(GetAllDigitsInLine(*it));

    cout << "Part 2: " << sum << endl;
}

int main() {
    vector<string> inputs = ParseInputs();
    Part1(inputs);
    Part2(inputs);
    return 0;
}
