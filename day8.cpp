#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

const char* INPUT = "inputs/day8.txt";

typedef uint16_t ID_t;
typedef pair<ID_t, ID_t> Node;

istream& ReadId(istream& in, ID_t& id)
{
    id = 0;
    char ch;
    for (int ii = 0; ii < 3; ++ii)
    {
        in >> ch;
        id = id * 26 + ch - 'A';
    }
    return in;
}

const ID_t AAA = 0;
const ID_t ZZZ = (25 * 26 + 25) * 26 + 25;

ostream& PrintId(ostream& out, ID_t id)
{
    char idChars[4];
    idChars[3] = '\0';
    for (int ii = 2; ii >= 0; --ii)
    {
        idChars[ii] = id % 26 + 'A';
        id /= 26;
    }
    out << idChars;
    return out;
}

istream& operator>>(istream& in, Node& node)
{
    char ch;
    in >> ch; // '('
    ReadId(in, node.first);
    in >> ch; // ','
    ReadId(in, node.second);
    ws(in);
    in >> ch; // ')'
    return in;
}

struct Inputs
{
    unordered_map<ID_t, Node> nodes;
    vector<bool> directions;
};

Inputs ParseInputs()
{
    Inputs inputs;

    ifstream infile(INPUT);

    string line;
    getline(infile, line);
    for (char ch : line) { inputs.directions.push_back(ch == 'R'); }
    getline(infile, line);

    ID_t id;
    char _ignoreEquals;
    Node node;
    while (infile.good() && !infile.eof() && ReadId(infile, id) >> _ignoreEquals >> node)
    {
        inputs.nodes.emplace(id, node);
    }

    return inputs;
}

void Part1(const Inputs &inputs)
{
    size_t totalSteps = 0;

    ID_t curr = AAA;

    while (curr != ZZZ)
    {
        if (inputs.directions[totalSteps % inputs.directions.size()])
            curr = inputs.nodes.at(curr).second;
        else
            curr = inputs.nodes.at(curr).first;

        ++totalSteps;
    }

    cout << "Part 1: " << totalSteps << endl;
}

// void Part2(const vector<string> &inputs)
// {

// }

int main()
{
  auto inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
