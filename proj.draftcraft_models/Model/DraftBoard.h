#pragma once

#include <vector>
#include "DraftDeck.h"
#include "DraftPile.h"
#include "../StaticData/IStaticDataManager.h"

using namespace std;

class DraftBoard
{
private:
    static constexpr int NUM_PILES = 3;

    DraftDeck m_deck;
    vector<DraftPile> m_piles;
public:
    DraftBoard(IStaticDataManager& staticDataManager, unsigned int deckSeed);

    const vector<DraftPile>& piles() const { return m_piles; }
    const DraftDeck& deck() const { return m_deck; }
};

