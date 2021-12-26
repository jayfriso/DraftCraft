#pragma once
#include "AbstractCommand.h"

class CommandProcessor
{
private:
    GameState& m_gameState;

    int m_currentCommandIndex;
public:
    void ProcessCommandFromClient(AbstractCommand& command);
};

