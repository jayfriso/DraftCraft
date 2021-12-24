#include "DraftBoard.h"

DraftBoard::DraftBoard(IStaticDataManager& staticDataManager, unsigned int deckSeed) : m_deck{staticDataManager, deckSeed}
{
	for (size_t i = 0; i < DraftBoard::NUM_PILES; i++)
	{
		m_piles.push_back(DraftPile{ m_deck });
	}
}
