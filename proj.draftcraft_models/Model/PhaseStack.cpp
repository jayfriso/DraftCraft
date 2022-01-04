#include "PhaseStack.h"
#include "GameState.h"

void PhaseStack::fillStartingDraftPhases()
{
    for (size_t i = 0; i < m_gameConfig.startingHandSize(); i++)
    {
        m_phaseStack.push_back(Phase{ PhaseType::Draft, (m_startingPlayerIndex + 1) % 2 });
        m_phaseStack.push_back(Phase{ PhaseType::Draft, m_startingPlayerIndex });
    }
}

void PhaseStack::fillGenericTurnPhases()
{
    // TODO : Need to add logic to fill generic turns
}

void PhaseStack::modifyGSUponPhaseOnset(const Phase& phase)
{
    switch (phase.phaseType)
    {
        case PhaseType::Draft:
            m_gameState.draftBoard().startDraft(phase.playerIndex);
            break;
    }
}

PhaseStack::PhaseStack(const GameConfig& gameConfig, GameState& gameState, unsigned int startingPlayerIndex) : m_startingPlayerIndex{startingPlayerIndex}, m_gameConfig{gameConfig}, m_gameState{gameState}
{
    fillStartingDraftPhases();
    modifyGSUponPhaseOnset(getCurrentPhase());
}

const Phase& PhaseStack::getCurrentPhase() const
{
    return m_phaseStack.back();
}

const Phase& PhaseStack::proceedToNextPhase()
{
    m_phaseStack.pop_back();
    if (m_phaseStack.size() == 0)
    {
        if (m_turnPlayerIndex == -1)
            m_turnPlayerIndex = m_startingPlayerIndex;
        else
            m_turnPlayerIndex = (m_turnPlayerIndex + 1) % 2;

        fillGenericTurnPhases();
    }
    const Phase& newPhase{ getCurrentPhase() };
    modifyGSUponPhaseOnset(newPhase);
    return newPhase;
}
