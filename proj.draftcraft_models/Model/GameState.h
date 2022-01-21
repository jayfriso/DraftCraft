#pragma once

#include <array>
#include "../StaticData/IStaticDataManager.h"
#include "Player.h"
#include "DraftBoard.h"
#include "PhaseStack.h"
#include "../MatchMaking/IMatchMaker.h"

class GameState
{
private:
    static constexpr int NUM_PLAYERS = 2;

    const IStaticDataManager& m_staticDataManager;

    std::array<Player, NUM_PLAYERS> m_players;
    unsigned int m_localPlayerIndex;

    DraftBoard m_draftBoard;
    PhaseStack m_phaseStack;

public:
    GameState(const IStaticDataManager& staticDataManager, string player0Id, string player1Id, unsigned int localPlayerIndex, unsigned int deckSeed);
    GameState(const IStaticDataManager& staticDataManager, const Match& match) : GameState{ staticDataManager, match.player0Id, match.player1Id, match.localPlayerIndex, match.deckSeed } {}

    Player& playerAtIndex(unsigned int index) { return m_players.at(index); }
    DraftBoard& draftBoard() { return m_draftBoard; }
    PhaseStack& phaseStack() { return m_phaseStack; }
};

