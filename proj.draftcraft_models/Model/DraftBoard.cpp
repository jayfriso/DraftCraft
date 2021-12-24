#include "DraftBoard.h"
#include "GameState.h"

DraftBoard::DraftBoard(IStaticDataManager& staticDataManager, GameState& gameState, unsigned int deckSeed) : m_gameState{gameState}, m_deck { staticDataManager, deckSeed }, m_currentPileIndex{ 0 }, m_currentPlayerIndex{ -1 }
{
	for (size_t i = 0; i < DraftBoard::NUM_PILES; i++)
	{
		m_piles.push_back(DraftPile{ m_deck });
	}
}

Player& DraftBoard::getDraftingPlayer()
{
	if (!isDrafting())
	{
		// TODO throw exception here for when not drafting
	}
	return m_gameState.playerAtIndex(m_currentPlayerIndex);
}

DraftPile& DraftBoard::getCurrentPile()
{
	if (!isDrafting())
	{
		// TODO throw exception here for when not drafting
	}
	return m_piles.at(m_currentPileIndex);
}

void DraftBoard::startDraft(unsigned int draftingPlayerIndex)
{
	m_currentPlayerIndex = draftingPlayerIndex;
	m_currentPileIndex = 0;
	notifyToUpdate();
}

void DraftBoard::draftCardAtIndex(unsigned int index)
{
	const Card* draftedCard = getCurrentPile().draftCardAtIndex(index);
	getDraftingPlayer().addCardToHand(draftedCard);
	m_currentPlayerIndex = -1;
	notifyToUpdate();
}
void DraftBoard::skipPile()
{
	getCurrentPile().addCardToPile();
	if (m_currentPileIndex + 1 < DraftBoard::NUM_PILES)
	{
		m_currentPileIndex++;
	}
	else
	{
		const Card* draftedCard = m_deck.drawCard();
		getDraftingPlayer().addCardToHand(draftedCard);
		m_currentPlayerIndex = -1;
	}
	notifyToUpdate();
}
