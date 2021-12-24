#include "GameState.h"

GameState::GameState(IStaticDataManager& staticDataManager, string player1Name, string player2Name, unsigned int clientPlayerIndex, unsigned int deckSeed) : m_staticDataManager{ staticDataManager }, m_clientPlayerIndex{m_clientPlayerIndex}, m_draftBoard{staticDataManager, *this, deckSeed}
{
    m_players.push_back(Player{ player1Name, 0 });
    m_players.push_back(Player{ player2Name, 1 });
}