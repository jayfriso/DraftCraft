#pragma once
#include "IStaticDataManager.h"

#include <vector>

using namespace std;

class JsonStaticDataManager : public IStaticDataManager
{
private:
    vector<Card> m_cardList;
    GameConfig m_gameConfig;
public:
    JsonStaticDataManager();
    virtual ~JsonStaticDataManager() = default;

    // IStaticDataManager
    virtual const Card* getCardByIndex(int index) const override;
    virtual const GameConfig& getGameConfig() const override;
    virtual size_t getTotalCardCount() const override;
};

