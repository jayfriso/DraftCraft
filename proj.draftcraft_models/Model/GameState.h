#pragma once

#include <array>
#include "../StaticData/IStaticDataManager.h"
#include "Player.h"
#include "DraftBoard.h"
#include "PhaseStack.h"

class GameState
{
private:
    static constexpr int NUM_PLAYERS = 2;

    IStaticDataManager& m_staticDataManager;

    std::array<Player, NUM_PLAYERS> m_players;
    unsigned int m_clientPlayerIndex;

    DraftBoard m_draftBoard;
    PhaseStack m_phaseStack;

public:
    GameState(IStaticDataManager& staticDataManager, string player1Name, string player2Name, unsigned int clientPlayerIndex, unsigned int deckSeed);

    Player& playerAtIndex(unsigned int index) { return m_players.at(index); }
    DraftBoard& draftBoard() { return m_draftBoard; }
    PhaseStack& phaseStack() { return m_phaseStack; }
};

