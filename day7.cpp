#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

using namespace std;

const char* INPUT = "inputs/day7.txt";

enum HandType
{
    HighCard = 0,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

enum Card
{
    C_2 = 0,
    C_3,
    C_4,
    C_5,
    C_6,
    C_7,
    C_8,
    C_9,
    C_10,
    C_J,
    C_Q,
    C_K,
    C_A
};

istream& operator>>(istream& in, Card& card)
{
    char ch;
    in >> ch;
    
    switch (ch)
    {
    case 'A':
        card = C_A;
        break;
    case 'K':
        card = C_K;
        break;
    case 'Q':
        card = C_Q;
        break;
    case 'J':
        card = C_J;
        break;
    case 'T':
        card = C_10;
        break;
    default:
        card = (Card)(ch - '2');
    }

    return in;
}

struct Hand
{
    array<Card, 5> cards;

    bool operator<(const Hand& other) const
    {
        if (type == other.type)
        {
            for (size_t ii = 0; ii < cards.size(); ++ii)
            {
                if (cards[ii] == other.cards[ii])
                    continue;

                return cards[ii] < other.cards[ii];
            }

            return false;
        }

        return type < other.type;
    }

    friend istream& operator>>(istream& in, Hand& hand)
    {
        in >> hand.cards[0] >> hand.cards[1] >> hand.cards[2] >> hand.cards[3] >> hand.cards[4];
        hand.CountCards();
        return in;
    }

private:
    HandType type{HighCard};

    void CountCards()
    {
        unordered_map<Card,unsigned int> countedCards;
        for (Card card : cards)
        {
            if (!countedCards.try_emplace(card, 1).second)
                ++countedCards[card];
        }

        switch (countedCards.size())
        {
        case 5:
            type = HighCard;
            return;
        case 4:
            type = OnePair;
            return;
        case 3:
            if (find_if(countedCards.begin(), countedCards.end(), [](auto& pair) { return pair.second == 3; }) != countedCards.end())
            {
                type = ThreeOfAKind;
                return;
            }
            type = TwoPair;
            return;
        case 2:
            if (find_if(countedCards.begin(), countedCards.end(), [](auto& pair) { return pair.second == 4; }) != countedCards.end())
            {
                type = FourOfAKind;
                return;
            }
            type = FullHouse;
            return;
        case 1:
            type = FiveOfAKind;
            return;
        }
    }
};

struct CamelCardsBid
{
    Hand hand;
    size_t bid;

    bool operator<(const CamelCardsBid& other) const { return hand < other.hand; }
};

vector<CamelCardsBid> ParseInputs()
{
    vector<CamelCardsBid> inputs;

    ifstream infile(INPUT);

    CamelCardsBid next;
    while (infile >> next.hand >> next.bid)
    {
        inputs.push_back(next);
    }

    return inputs;
}

void Part1(vector<CamelCardsBid> bids)
{
    sort(bids.begin(), bids.end());

    size_t sum = 0;
    for (size_t ii = 0; ii < bids.size(); ++ii)
        sum += (ii + 1) * bids[ii].bid;

    cout << "Part 1: " << sum << endl;
}

// void Part2(const vector<string> &inputs)
// {

// }

int main()
{
  vector<CamelCardsBid> inputs = ParseInputs();
  Part1(inputs);
  // Part2(inputs);
  return 0;
}
