#pragma once

#include "../AbstractCommand.h"

class DraftAtIndexCommand : public AbstractCommand
{
private:
    unsigned int m_cardIndex;
public:
    DraftAtIndexCommand(unsigned int cardIndex, unsigned int playerIndex) : AbstractCommand{ playerIndex }, m_cardIndex{ cardIndex } {}

    virtual void ExecuteCommand(GameState& gameState) override;
};

