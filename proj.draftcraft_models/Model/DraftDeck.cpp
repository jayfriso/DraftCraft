#include "DraftDeck.h"
#include <random>
#include <utility>

DraftDeck::DraftDeck(const IStaticDataManager& staticDataManager, unsigned int seed) : m_staticDataManager{ staticDataManager }, m_seed{ seed }
{
    std::mt19937 random{ m_seed };

    size_t deckSize = m_staticDataManager.getGameConfig().deckSize();
    size_t nonLandCardCount = deckSize - m_staticDataManager.getGameConfig().landCardCount();

    vector<const Card&> tempCardVector;
    tempCardVector.reserve(staticDataManager.getTotalCardCount() - 1);
    for (unsigned int i = 0; i < tempCardVector.capacity(); i++)
    {
        tempCardVector.push_back(staticDataManager.getCardByIndex(i + 1));
    }
    std::shuffle(tempCardVector.begin(), tempCardVector.end(), random);
    tempCardVector.resize(deckSize);
    std::fill(tempCardVector.begin() + nonLandCardCount, tempCardVector.end(), staticDataManager.getLandCard());
    std::shuffle(tempCardVector.begin(), tempCardVector.end(), random);

    m_cardStack = std::stack<const Card&, vector<const Card&>>(tempCardVector);
}

const Card& DraftDeck::drawCard()
{
    const Card& result = m_cardStack.top();
    m_cardStack.pop();
    notifyToUpdate();
    return result;
}

size_t DraftDeck::cardsLeft() const
{
    return m_cardStack.size();
}