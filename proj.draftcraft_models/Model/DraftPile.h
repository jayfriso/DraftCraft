#pragma once
#include <vector>
#include <cmath>
#include "../StaticData/Card.h"
#include "DraftDeck.h"
#include "../ViewModel/DispatcherViewModel.h"

using namespace std;

class DraftCard
{
private:
    const Card* m_card;
    int m_seenFlags;
public:
    DraftCard(const Card* card) : m_card{ card }, m_seenFlags{ 0 } {}
    bool getSeenByPlayer(unsigned int playerIndex) const 
    {
        (m_seenFlags & (int)std::exp2(playerIndex)) > 0;
    }
    void setSeenByPlayer(unsigned int playerIndex)
    {
        m_seenFlags = m_seenFlags | (int)exp2(playerIndex);
    }
};

class DraftPile : public DispatcherViewModel<DraftPile>
{
private:
    DraftDeck& m_draftDeck;
    vector<const Card*> m_cardsInPile;
    
public:
    DraftPile(DraftDeck& draftDeck);
    
    const vector<const Card*>& cardsInPile() const { return m_cardsInPile; }

    // Get the card at the index and reset the pile
    const Card* draftCardAtIndex(unsigned int index);
    void addCardToPile();
};

