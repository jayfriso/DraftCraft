#include "JsonStaticDataManager.h"

JsonStaticDataManager::JsonStaticDataManager() : m_cardList{}, m_gameConfig{10, 4}
{
    // Test code, should be removed
    m_cardList.push_back(Card{ "test_1", "Test Card 1" });
    m_cardList.push_back(Card{ "test_2", "Test Card 2" });
    m_cardList.push_back(Card{ "test_3", "Test Card 3" });
}

const Card* JsonStaticDataManager::getCardByIndex(int index) const
{
    return &m_cardList[index];
}
const Card* JsonStaticDataManager::getLandCard() const
{
    return &m_cardList[0];
}
const GameConfig& JsonStaticDataManager::getGameConfig() const
{
    return m_gameConfig;
}

size_t JsonStaticDataManager::getTotalCardCount() const
{
    return m_cardList.size();
}
