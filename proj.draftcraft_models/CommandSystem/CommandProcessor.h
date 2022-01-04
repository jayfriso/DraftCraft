#pragma once
#include "AbstractCommand.h"

class CommandProcessor
{
private:
    GameState& m_gameState;

    int m_currentCommandIndex;
public:
    CommandProcessor(GameState& gameState);

    void ProcessCommandFromClient(AbstractCommand& command);
};

