#pragma once

#include <array>
#include "DraftDeck.h"
#include "DraftPile.h"
#include "../StaticData/IStaticDataManager.h"
#include "../ViewModel/DispatcherViewModel.h"

class DraftBoard : public DispatcherViewModel
{
private:
    static constexpr int NUM_PILES = 3;

    DraftDeck m_deck;
    std::array<DraftPile, NUM_PILES> m_piles;

    int m_currentPileIndex;
    // Represents what player is currently drafting, if no player is drafting then index is -1
    int m_currentPlayerIndex;

    DraftPile& getCurrentPile();

public:
    DraftBoard(const IStaticDataManager& staticDataManager, unsigned int deckSeed);

    const array<DraftPile, NUM_PILES>& piles() const { return m_piles; }
    const DraftDeck& deck() const { return m_deck; }
    bool isDrafting() const { return m_currentPlayerIndex >= 0; }

    void startDraft(unsigned int draftingPlayerIndex);
    // Gets the card at the index and ends the draft
    const Card& draftCardAtIndex(unsigned int index);
    // Either moves to the next pile, or if no piles are left, returns a card from the deck and ends the draft
    // Returns nullptr if the player moves to the next pile
    const Card* skipPile();
};

