#pragma once
#include "AbstractCommand.h"

class CommandProcessor
{
private:
    GameState& m_gameState;

    int m_currentCommandIndex;
public:
    CommandProcessor(GameState& gameState);

    int currentCommandIndex() const { return m_currentCommandIndex; };

    void ProcessCommandFromClient(AbstractCommand& command);
    void ReceiveCommandFromServer(AbstractCommand& command);
};

