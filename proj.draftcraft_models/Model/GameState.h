#pragma once

#include <vector>
#include "../StaticData/IStaticDataManager.h"
#include "Player.h"
#include "DraftBoard.h"

using namespace std;

class GameState
{
private:
    IStaticDataManager& m_staticDataManager;

    vector<Player> m_players;
    unsigned int m_clientPlayerIndex;

    DraftBoard m_draftBoard;

public:
    GameState(IStaticDataManager& staticDataManager, string player1Name, string player2Name, unsigned int clientPlayerIndex, unsigned int deckSeed);

    Player& playerAtIndex(unsigned int index) { return m_players.at(index); }
    DraftBoard& draftBoard() { return m_draftBoard; }
};

