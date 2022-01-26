#pragma once
#include <vector>
#include "../StaticData/Card.h"
#include "DraftDeck.h"

using namespace std;

class DraftPile : public DispatcherViewModel
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

