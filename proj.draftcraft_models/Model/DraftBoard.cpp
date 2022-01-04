#include "DraftBoard.h"
#include "GameState.h"

DraftBoard::DraftBoard(IStaticDataManager& staticDataManager, unsigned int deckSeed) : m_deck { staticDataManager, deckSeed }, m_currentPileIndex{ 0 }, m_currentPlayerIndex{ -1 }
{
	for (size_t i = 0; i < DraftBoard::NUM_PILES; i++)
	{
		m_piles.push_back(DraftPile{ m_deck });
	}
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

const Card* DraftBoard::draftCardAtIndex(unsigned int index)
{
	const Card* draftedCard = getCurrentPile().draftCardAtIndex(index);
	m_currentPlayerIndex = -1;
	notifyToUpdate();
	return draftedCard;
}
const Card* DraftBoard::skipPile()
{
	getCurrentPile().addCardToPile();
	const Card* draftedCard{ nullptr };
	if (m_currentPileIndex + 1 < DraftBoard::NUM_PILES)
	{
		m_currentPileIndex++;
	}
	else
	{
		draftedCard = m_deck.drawCard();
		m_currentPlayerIndex = -1;
	}
	notifyToUpdate();
	return draftedCard;
}
