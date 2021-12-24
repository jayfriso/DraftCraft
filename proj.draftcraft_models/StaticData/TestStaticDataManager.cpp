#include "TestStaticDataManager.h"

TestStaticDataManager::TestStaticDataManager(unsigned int numTestCards, GameConfig& gameConfigRef) : m_gameConfigRef{ gameConfigRef }
{
    for (unsigned int i = 0; i < numTestCards; i++)
    {
        m_cardList.push_back(Card{ "test_" + std::to_string(i), "Test Card " + std::to_string(i) });
    }
}

const Card* TestStaticDataManager::getCardByIndex(int index) const
{
    return &m_cardList[index];
}
size_t TestStaticDataManager::getTotalCardCount() const
{
    return m_cardList.size();
}