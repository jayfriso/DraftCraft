#include "TestStaticDataManager.h"

TestStaticDataManager::TestStaticDataManager(unsigned int numTestCards) : 
    m_gameConfig{  100, 40}
{
    m_cardList.reserve(numTestCards);
    for (unsigned int i = 0; i < numTestCards; i++)
    {
        m_cardList.push_back(Card{ "test_" + std::to_string(i), "Test Card " + std::to_string(i) });
    }
}

const Card* TestStaticDataManager::getCardByIndex(int index) const
{
    return &m_cardList[index];
}
const Card* TestStaticDataManager::getLandCard() const
{
    return &m_cardList[0];
}
size_t TestStaticDataManager::getTotalCardCount() const
{
    return m_cardList.size();
}