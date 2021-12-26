#include "CommandProcessor.h"

void CommandProcessor::ProcessCommandFromClient(AbstractCommand& command)
{
    m_currentCommandIndex++;
    command.m_commandIndex = m_currentCommandIndex;
    command.ExecuteCommand(m_gameState);
}
