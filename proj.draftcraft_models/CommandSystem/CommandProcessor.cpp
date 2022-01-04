#include "CommandProcessor.h"

CommandProcessor::CommandProcessor(GameState& gameState) : m_gameState{gameState}, m_currentCommandIndex{0}
{
}

void CommandProcessor::ProcessCommandFromClient(AbstractCommand& command)
{
    m_currentCommandIndex++;
    command.m_commandIndex = m_currentCommandIndex;
    command.ExecuteCommand(m_gameState);

    // TODO : Send the command to the DB
}
