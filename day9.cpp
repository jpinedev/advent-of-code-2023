#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

const char* INPUT = "inputs/day9.txt";

class Sequence
{
public:
    Sequence(const vector<long>& seq) : mSeq(seq) {}

    Sequence ReduceSequence() const
    {
        if (mSeq.size() <= 1)
            throw runtime_error("Cannot reduce sequence any further");

        vector<long> reduced;
        reduced.reserve(mSeq.size() - 1);

        for (size_t ii = 1; ii < mSeq.size(); ++ii)
        {
            reduced.push_back(mSeq[ii] - mSeq[ii - 1]);
        }

        return reduced;
    }

    long PredictNextNumber() const
    {
        if (IsZeros())
            return 0;

        return mSeq.back() + ReduceSequence().PredictNextNumber();
    }

    long ExtrapolatePreviousNumber() const
    {
        if (IsZeros())
            return 0;

        return mSeq.front() - ReduceSequence().ExtrapolatePreviousNumber();
    }

    bool IsZeros() const { return all_of(mSeq.begin(), mSeq.end(), [](const long& num) { return num == 0l; }); }

    const long& GetBack() const { return mSeq.back(); }

private:
    const vector<long> mSeq;
};

vector<Sequence> ParseInputs()
{
    vector<Sequence> inputs;

    ifstream infile(INPUT);

    string line;
    while (infile.good() && !infile.eof())
    {
        if (!getline(infile, line))
            break;

        vector<long> nextSeq;
        stringstream seqStr(line);

        long nextNum;
        while (seqStr >> nextNum)
        {
            nextSeq.push_back(nextNum);
        }
        inputs.emplace_back(nextSeq);
    }

    return inputs;
}

void Part1(const vector<Sequence> &inputs)
{
    long sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        sum += it->PredictNextNumber();

    cout << "Part 1: " << sum << endl;
}

void Part2(const vector<Sequence> &inputs)
{
    long sum = 0;

    for (auto it = inputs.begin(); it != inputs.end(); ++it)
        sum += it->ExtrapolatePreviousNumber();

    cout << "Part 2: " << sum << endl;
}

int main()
{
  vector<Sequence> inputs = ParseInputs();
  Part1(inputs);
  Part2(inputs);
  return 0;
}
