#include "DraftDeck.h"
#include <random>

DraftDeck::DraftDeck(IStaticDataManager& staticDataManager, unsigned int seed) : m_staticDataManager{ staticDataManager }, m_cardIndices(staticDataManager.getGameConfig().deckSize(), 0), m_seed{ seed }
{
    std::mt19937 random{ m_seed };

    unsigned int landCardCount = m_staticDataManager.getGameConfig().landCardCount();
    unsigned int nonLandCardCount = m_cardIndices.size() - landCardCount;

    // Get all card indices, shuffle, and then pick the first X where X is the amount of non land cards we want
    vector<unsigned int> nonLandCardIndices (staticDataManager.getTotalCardCount() - 1);
    for (unsigned int i = 0; i < nonLandCardIndices.size(); i++)
    {
        nonLandCardIndices.at(i) = i + 1;
    }
    std::shuffle(nonLandCardIndices.begin(), nonLandCardIndices.end(), random);
    nonLandCardIndices.resize(nonLandCardCount);

    // Add the non land cards to the beginning of the result list
    // Rest of the list is filled with 0s (representing land cards) so a shuffle and should be done
    std::copy(nonLandCardIndices.begin(), nonLandCardIndices.end(), m_cardIndices.begin());
    std::shuffle(m_cardIndices.begin(), m_cardIndices.end(), random);
}

const Card* DraftDeck::drawCard()
{
    unsigned int cardIndex = m_cardIndices.at(m_cardIndices.size() - 1);
    m_cardIndices.pop_back();
    flagViewDirty();
    return m_staticDataManager.getCardByIndex(cardIndex);
}

size_t DraftDeck::cardsLeft() const
{
    return m_cardIndices.size();
}