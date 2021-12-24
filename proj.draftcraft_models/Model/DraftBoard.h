#pragma once

#include <vector>
#include "DraftDeck.h"
#include "DraftPile.h"
#include "../StaticData/IStaticDataManager.h"
#include "../ViewModel/DispatcherViewModel.h"

using namespace std;

// Forward Declaration
class GameState;
class Player;

class DraftBoard : public DispatcherViewModel
{
private:
    static constexpr int NUM_PILES = 3;

    GameState& m_gameState;

    DraftDeck m_deck;
    vector<DraftPile> m_piles;

    int m_currentPileIndex;
    // Represents what player is currently drafting, if no player is drafting then index is -1
    int m_currentPlayerIndex;

    Player& getDraftingPlayer();
    DraftPile& getCurrentPile();

public:
    DraftBoard(IStaticDataManager& staticDataManager, GameState& gameState, unsigned int deckSeed);

    const vector<DraftPile>& piles() const { return m_piles; }
    const DraftDeck& deck() const { return m_deck; }
    bool isDrafting() const { return m_currentPlayerIndex >= 0; }

    void startDraft(unsigned int draftingPlayerIndex);
    void draftCardAtIndex(unsigned int index);
    void skipPile();
};

