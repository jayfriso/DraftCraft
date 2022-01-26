#pragma once
#include "IStaticDataManager.h"
#include <vector>

using namespace std;

class TestStaticDataManager : public IStaticDataManager
{
private: 
    vector<Card> m_cardList;
    // Reference to the gameconfig that comes from the test class
    GameConfig m_gameConfig;
public:
    TestStaticDataManager(unsigned int numTestCards);
    virtual ~TestStaticDataManager() = default;

    virtual const Card* getCardByIndex(int index) const override;
    virtual const Card* getLandCard() const override;
    virtual size_t getTotalCardCount() const override;
    virtual const GameConfig& getGameConfig() const override { return m_gameConfig; }
};

