#pragma once

#include <vector>
#include "Player.h"
#include "../StaticData/IStaticDataManager.h"

using namespace std;

class GameState
{
private:
    IStaticDataManager& m_staticDataManager;

    vector<Player> m_players;
    unsigned int m_clientPlayerIndex;

public:
    GameState(IStaticDataManager& staticDataManager, string player1Name, string player2Name, unsigned int clientPlayerIndex);
};

