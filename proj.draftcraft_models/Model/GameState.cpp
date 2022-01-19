#include "GameState.h"

// TODO : phasestack currently defaulting to setting 0 as the starting player, should be based on match
GameState::GameState(IStaticDataManager& staticDataManager, string player1Name, string player2Name, unsigned int clientPlayerIndex, unsigned int deckSeed) : 
    m_staticDataManager{ staticDataManager }, 
    m_clientPlayerIndex{m_clientPlayerIndex}, 
    m_draftBoard{staticDataManager, deckSeed}, 
    m_phaseStack{staticDataManager.getGameConfig(), *this, 0},
    m_players{ Player{player1Name, 0}, Player{player2Name, 1} }
{
}