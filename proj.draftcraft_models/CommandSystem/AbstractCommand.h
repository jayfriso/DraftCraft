#pragma once

#include "../Model/GameState.h";

class AbstractCommand
{
    friend class CommandProcessor;
protected:
    int m_playerIndex;
    int m_commandIndex;
public:
    virtual void ExecuteCommand(GameState& gameState) = 0;
};

