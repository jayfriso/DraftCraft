#pragma once
#include "../AbstractCommand.h"

class DraftSkipPileCommand : public AbstractCommand
{
public:
    DraftSkipPileCommand(unsigned int playerIndex) : AbstractCommand{ playerIndex } {}
    virtual void ExecuteCommand(GameState& gameState) override;
};

