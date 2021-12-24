#include "DraftPile.h"

DraftPile::DraftPile(DraftDeck& draftDeck) : m_draftDeck{ draftDeck }
{
    addCardToPile();
}

const Card* DraftPile::draftCardAtIndex(unsigned int index)
{
    // TODO : Add exception for index here
    const Card* result{ m_cardsInPile.at(index) };
    m_cardsInPile.clear();
    addCardToPile();
    return result;
}

void DraftPile::addCardToPile()
{
    m_cardsInPile.push_back(m_draftDeck.drawCard());
    notifyToUpdate();
}