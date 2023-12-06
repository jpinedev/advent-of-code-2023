#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <functional>
#include <cassert>

using namespace std;

const char* INPUT = "inputs/day3.txt";

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

inline bool IsNumber(char ch)
{
    return isdigit((unsigned char)ch);
}

inline bool IsEmpty(char ch)
{
    return ch == '.';
}

inline bool IsSymbol(char ch)
{
    return !IsNumber(ch) && !IsEmpty(ch);
}

struct EngineLocation
{
private:
    const vector<string>& engine;

public:
    vector<string>::const_iterator row;
    string::const_iterator col;

    EngineLocation(const vector<string>& engine) : engine(engine), row(engine.begin()), col(row->begin()) {}
    EngineLocation(const vector<string>& engine, vector<string>::const_iterator row, string::const_iterator col) : engine(engine), row(row), col(col) {}
    EngineLocation(const EngineLocation& toCopy) : engine(toCopy.engine), row(toCopy.row), col(toCopy.col) {}
    
    EngineLocation End() const { return EngineLocation(engine, engine.end(), engine.back().end()); }
    EngineLocation PrevRow() const
    {
        if (row == engine.begin())
            throw range_error("Tried to decrement before begin iterator");

        auto prevRow = row - 1;
        return EngineLocation(engine, prevRow, prevRow->begin() + (col - row->begin()));
    }
    EngineLocation NextRow() const
    {
        auto nextRow = row + 1;
        if (nextRow == engine.end())
            return End();

        return EngineLocation(engine, nextRow, nextRow->begin() + (col - row->begin()));
    }

    EngineLocation& operator++()
    {
        if (col == row->end() && row != engine.end())
            throw range_error("Bad iterator");

        if (row == engine.end())
            throw range_error("Tried to increment beyond end iterator");

        ++col;
        if (col != row->end())
            return *this;

        ++row;
        if (row == engine.end())
            return *this = End();
        
        col = row->begin();
        return *this;
    }
    EngineLocation& operator--()
    {
        if (col == row->begin())
        {
            if (row == engine.begin())
                throw range_error("Tried to decrement before begin iterator");
            
            --row;
            col = row->end() - 1;
            return *this;
        }
        
        --col;
        return *this;
    }

    // Assumes EngineLocations are part of the same engine.
    EngineLocation& operator=(const EngineLocation& other)
    {
        assert(engine.data() == other.engine.data());
        row = other.row;
        col = other.col;
        return *this;
    }

    bool operator!=(const EngineLocation& other) const { return row != other.row || col != other.col; }

    const char& operator*() const { return *col; }
};

EngineLocation SeekNext(EngineLocation loc, function<bool(char)> predicate)
{
    auto end = loc.End();
    while (loc != end)
    {
        auto locCpy = loc;
        ++loc;
        if (predicate(*locCpy))
            return locCpy;
        // ++loc;
    }

    return end;
}

inline EngineLocation SeekNextNumber(EngineLocation loc) { return SeekNext(loc, IsNumber); }

inline EngineLocation SeekNextNonNumber(EngineLocation loc) { return SeekNext(loc, not_fn(IsNumber)); }

struct EngineRange
{
private:
    const vector<string>& engine;
    vector<string>::const_iterator row;

public:
    EngineLocation begin;
    EngineLocation end;

    EngineRange(const vector<string>& engine, EngineLocation begin, EngineLocation end) : engine(engine), begin(begin), end(end)
    {
        assert(begin.row == end.row);
        row = begin.row;
    }

    bool SearchAroundRange(function<bool(char)> predicate) const
    {
        if (row != engine.begin())
        {
            auto topLeft = begin.PrevRow().col;
            if (begin.col != row->begin())
                --topLeft;

            auto topRight = end.PrevRow().col;
            if (end.col != row->end())
                ++topRight;
            
            if (Any(topLeft, topRight, predicate))
                return true;
        }

        if (begin.col != row->begin())
        {
            auto left = begin;
            --left;

            if (predicate(*left))
                return true;
        }
        if (end.col != row->end())
        {
            if (predicate(*end))
                return true;
        }

        if (row + 1 != engine.end())
        {
            auto bottomLeft = begin.NextRow().col;
            if (begin.col != row->begin())
                --bottomLeft;

            auto bottomRight = end.NextRow().col;
            if (end.col != row->end())
                ++bottomRight;
            
            if (Any(bottomLeft, bottomRight, IsSymbol))
                return true;
        }

        return false;
    }

private:
    bool Any(const string::const_iterator& begin, const string::const_iterator& end, function<bool(char)> predicate) const
    {
        for (auto loc = begin; loc != end; ++loc)
        {
            if (predicate(*loc))
                return true;
        }
        return false;
    }
    
};

int EngineRangeAsNumber(const EngineRange& range)
{
    int number = 0;

    EngineLocation loc = range.begin;
    while (loc != range.end)
    {
        if (loc.row != range.end.row)
            break;

        assert(IsNumber(*loc));
        number *= 10;
        number += *loc - '0';
        ++loc;
    }

    return number;
}

void Part1(const vector<string> &engine)
{
    int sum = 0;

    EngineLocation startLoc(engine);
    EngineLocation endLoc = startLoc.End();

    for (EngineLocation nextNumber = SeekNextNumber(startLoc); nextNumber != endLoc; nextNumber = SeekNextNumber(nextNumber))
    {
        auto numberEnd = SeekNextNonNumber(nextNumber);

        auto rangeEnd = (numberEnd.row != nextNumber.row) ? EngineLocation(engine, nextNumber.row, nextNumber.row->end()) : numberEnd;
        EngineRange numberRange(engine, nextNumber, rangeEnd);
        nextNumber = numberEnd;

        if (numberRange.SearchAroundRange(IsSymbol))
            sum += EngineRangeAsNumber(numberRange);
    }
    
    cout << "Part 1: " << sum << endl;
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
