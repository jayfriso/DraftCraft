#include "DraftBoard.h"
#include "GameState.h"
#include "../Exceptions/ModelLogicError.h"

DraftBoard::DraftBoard(const IStaticDataManager& staticDataManager, unsigned int deckSeed) : 
	m_deck{ staticDataManager, deckSeed }, 
	m_piles{ DraftPile{ m_deck } ,DraftPile{ m_deck } ,DraftPile{ m_deck } }, 
	m_currentPileIndex{ 0 }, 
	m_currentPlayerIndex{ -1 }
{
}

DraftPile& DraftBoard::getCurrentPile()
{
	if (!isDrafting())
	{
		throw ModelLogicError("Getting draft pile but DraftBoard is not currently in drafting mode.");
	}
	return m_piles.at(m_currentPileIndex);
}

void DraftBoard::startDraft(unsigned int draftingPlayerIndex)
{
	m_currentPlayerIndex = draftingPlayerIndex;
	m_currentPileIndex = 0;
	notifyToUpdate();
}

const Card& DraftBoard::draftCardAtIndex(unsigned int index)
{
	const Card& draftedCard = getCurrentPile().draftCardAtIndex(index);
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
		draftedCard = &(m_deck.drawCard());
		m_currentPlayerIndex = -1;
	}
	notifyToUpdate();
	return draftedCard;
}
