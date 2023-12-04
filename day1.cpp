#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

const char* INPUT = "inputs/day1.txt";

vector<string> ParseInputs() {
  vector<string> inputs;

  ifstream infile(INPUT);

  string line;
  while (infile.good() && !infile.eof()) {
    if (!getline(infile, line)) break;
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

// void Part2(const vector<string> &inputs) {

// }

int main() {
  vector<string> inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
