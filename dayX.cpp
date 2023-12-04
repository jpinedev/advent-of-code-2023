#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const char* INPUT = "inputs/dayX.txt";

vector<string> parseInputs() {
  vector<string> inputs;

  ifstream infile(INPUT);

  string line;
  while (infile.good() && !infile.eof()) {
    if (!getline(infile, line)) break;
    inputs.push_back(line);
  }

  return inputs;
}

void part1(const vector<string> &inputs) {
  for (auto it = inputs.begin(); it != inputs.end(); ++it)
    cout << *it << endl;
}

// void part2(const vector<string> &inputs) {

// }

int main() {
  vector<string> inputs = parseInputs();
  part1(inputs);
  // part2(inputs);
  return 0;
}
