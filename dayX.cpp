#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const char* INPUT = "inputs/dayX.txt";

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

void Part1(const vector<string> &inputs)
{
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        cout << *it << endl;
}

// void Part2(const vector<string> &inputs)
// {

// }

int main()
{
  vector<string> inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
