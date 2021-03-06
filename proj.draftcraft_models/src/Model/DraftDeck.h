#pragma once

#include <stack>
#include <cstdlib>
#include <vector>
#include "../StaticData/IStaticDataManager.h"
#include "../ViewModel/DispatcherViewModel.h"

class DraftDeck : public DispatcherViewModel<DraftDeck>
{
private:
    const IStaticDataManager& m_staticDataManager;

    unsigned int m_seed;
    std::stack<const Card*, vector<const Card*>> m_cardStack;
public:
    DraftDeck(const IStaticDataManager& staticDataManager, unsigned int seed);
    const Card* drawCard();
    size_t cardsLeft() const;
};
