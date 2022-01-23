#pragma once
#include "IMatchMaker.h"

class TestMatchMaker : public IMatchMaker
{
private:
    Match m_currentMatch;
public:
    TestMatchMaker(unsigned int deckHash, string player0Id, string player1Id, unsigned int localPlayerIndex) : 
        m_currentMatch{ deckHash, player0Id, player1Id, localPlayerIndex, "fakeMatch" } {};
    virtual ~TestMatchMaker() = default;

    virtual const Match* currentMatch() const override { return &m_currentMatch; }
};

