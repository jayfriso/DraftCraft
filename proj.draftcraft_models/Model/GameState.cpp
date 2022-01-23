#include "GameState.h"

// TODO : phasestack currently defaulting to setting 0 as the starting player, should be based on match
GameState::GameState(const IStaticDataManager& staticDataManager, string player0Id, string player1Id, unsigned int localPlayerIndex, unsigned int deckSeed) :
    m_staticDataManager{ staticDataManager }, 
    m_localPlayerIndex{ localPlayerIndex },
    m_draftBoard{staticDataManager, deckSeed}, 
    m_phaseStack{staticDataManager.getGameConfig(), *this, 0},
    m_players{ Player{player0Id, 0}, Player{player1Id, 1} }
{
}