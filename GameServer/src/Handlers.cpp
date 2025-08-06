#include "Handlers.h"
#include "CommandQueue.h"

std::shared_ptr<ICommand> LogHandler::getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, std::exception_ptr ex)
{
    return std::make_shared<LogHandlerCommand>(cmd, ex, m_log);
}


void LogHandlerCommand::Execute()
{
    ExceptionHandler::Instance().RegisterHandler<LogCommand, std::exception_ptr>(std::make_unique<LogHandler>(m_log));
    try
    {
        std::rethrow_exception(m_ex);
    }
    catch (const std::exception &e)
    {
        auto ex = std::current_exception();
        CommandQueue::Instance().RegisterCommand(std::make_unique<LogCommand>(m_cmd, ex, m_log));
    }

}

std::shared_ptr<ICommand> RetryHandler::getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, std::exception_ptr ex)
{
    CommandQueue::Instance().RegisterCommand(std::make_unique<RetryCommand>(cmd));
    return std::make_shared<RetryCommand>(cmd);
}

std::shared_ptr<ICommand> DoubleRetryHandler::getCommand(std::shared_ptr<ICommand> cmd, std::exception_ptr ex)
{
    return std::shared_ptr<RetryCommand>();
}
