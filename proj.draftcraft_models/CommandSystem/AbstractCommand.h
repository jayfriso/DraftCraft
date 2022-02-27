#pragma once

#include "../Model/GameState.h"

class AbstractCommand
{
    friend class AbstractCommandProcessor;
protected:
    unsigned int m_playerIndex;
    unsigned int m_commandIndex;
public:
    AbstractCommand(unsigned int playerIndex, unsigned int commandIndex) : m_playerIndex{ playerIndex }, m_commandIndex{ commandIndex } {}
    AbstractCommand(unsigned int playerIndex) : AbstractCommand{ playerIndex, 0 } {}

    void setCommandIndex(unsigned int index) { m_commandIndex = index; }

    virtual void ExecuteCommand(GameState& gameState) = 0;
};

