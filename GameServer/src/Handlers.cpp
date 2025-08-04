#include "Handlers.h"
#include "CommandQueue.h"

std::shared_ptr<ICommand> LogHandler::getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, [[maybe_unused]] ExPtr ex)
    {
        return std::make_shared<LogHandlerCommand>(cmd, ex, m_log);
    }


    void LogHandlerCommand::Execute() {
        ExceptionHandler::Instance().RegisterHandler<LogCommand, std::exception>(std::make_unique<LogHandler>(m_log));
        CommandQueue::Instance().RegisterCommand(std::make_unique<LogCommand>(m_cmd, m_ex, m_log));
    }
