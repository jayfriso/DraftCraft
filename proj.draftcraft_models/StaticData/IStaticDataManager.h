#pragma once

#include "Card.h"
#include "GameConfig.h"


class IStaticDataManager
{
public :
    virtual ~IStaticDataManager() = default;

    // We return the card as a pointer, as data is stored only once in the staticdatamanager. Once the data is loaded, it will not change throughout lifetime of application.
    virtual const Card* getCardByIndex(int index) const = 0;
    virtual size_t getTotalCardCount() const = 0;

    virtual const GameConfig& getGameConfig() const = 0;
};

