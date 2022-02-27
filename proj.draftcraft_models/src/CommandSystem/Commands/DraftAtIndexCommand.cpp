#include "DraftAtIndexCommand.h"

void DraftAtIndexCommand::ExecuteCommand(GameState& gameState)
{
    const Card* draftedCard = gameState.draftBoard().draftCardAtIndex(m_cardIndex);
    gameState.playerAtIndex(m_playerIndex).addCardToHand(draftedCard);
    gameState.phaseStack().proceedToNextPhase();
}
