#pragma once
#include <string>

using namespace std;

struct Match
{
    unsigned int deckSeed;
    string player0Id;
    string player1Id;
    unsigned int localPlayerIndex;
    string matchId;
};

class IMatchMaker
{
public:
    virtual ~IMatchMaker() = default;
    // Returns the current match, nullptr if no match is made yet
    virtual const Match* currentMatch() const = 0;
};

