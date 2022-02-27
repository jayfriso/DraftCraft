#include "AbstractCommandProcessor.h"
#include "../Exceptions/ModelLogicError.h"
#include <sstream>

AbstractCommandProcessor::AbstractCommandProcessor(GameState& gameState) : m_gameState{gameState}, m_currentCommandIndex{0}
{
}

void AbstractCommandProcessor::ProcessCommandFromClient(AbstractCommand& command)
{
    m_currentCommandIndex++;
    command.m_commandIndex = m_currentCommandIndex;
    command.ExecuteCommand(m_gameState);

    // TODO : Send the command to the DB
}

void AbstractCommandProcessor::ReceiveCommandFromServer(AbstractCommand& command)
{
    if (command.m_commandIndex != m_currentCommandIndex + 1)
    {
        // TODO : Should deal with a command desync here. For now throw an exception
        std::ostringstream errorMessage{};
        errorMessage << "Received Command from server with index " << command.m_commandIndex << " but was expecting index of " << (m_currentCommandIndex + 1);
        throw ModelLogicError{ errorMessage.str()};
    }
    command.ExecuteCommand(m_gameState);
}
