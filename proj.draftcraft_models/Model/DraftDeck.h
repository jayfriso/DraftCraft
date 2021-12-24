#pragma once

#include <vector>
#include <cstdlib>
#include "../StaticData/IStaticDataManager.h"
#include "../ViewModel/DispatcherViewModel.h"

class DraftDeck : public DispatcherViewModel
{
private:
    IStaticDataManager& m_staticDataManager;

    unsigned int m_seed;
    std::vector<unsigned int> m_cardIndices;
public:
    DraftDeck(IStaticDataManager& staticDataManager, unsigned int seed);
    const Card* drawCard();
    size_t cardsLeft() const;
};
