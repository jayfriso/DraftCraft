#include "DraftSkipPileCommand.h"

void DraftSkipPileCommand::ExecuteCommand(GameState& gameState)
{
    const Card* draftedCard = gameState.draftBoard().skipPile();
    if (draftedCard != nullptr)
    {
        gameState.playerAtIndex(m_playerIndex).addCardToHand(*draftedCard);
        gameState.phaseStack().proceedToNextPhase();
    }
}
