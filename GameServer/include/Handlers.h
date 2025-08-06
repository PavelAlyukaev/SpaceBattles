#include "Interfaces.h"
#include "ExceptionHandler.h"
#include "Commands.h"

struct LogHandler : public IHandler
{
    template<std::derived_from<ILog> TLog>
    explicit LogHandler(std::shared_ptr<TLog> log) : m_log(log)
    {}

    std::shared_ptr<ICommand> getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, std::exception_ptr ex) override;

private:
    std::shared_ptr<ILog> m_log;
};

struct LogHandlerCommand : public Command<LogHandlerCommand>
{
    template<std::derived_from<ILog> TLog, std::derived_from<ICommand> TCommand>
    explicit
    LogHandlerCommand(std::shared_ptr<TCommand> cmd, std::exception_ptr ex, std::shared_ptr<TLog> log): m_log(log),
                                                                                                        m_cmd(cmd),
                                                                                                        m_ex(ex)
    {}

    void Execute() override;

private:
    std::shared_ptr<ILog> m_log;
    std::shared_ptr<ICommand> m_cmd;
    std::exception_ptr m_ex;

};

struct RetryHandler : public IHandler
{
    explicit RetryHandler() = default;

    std::shared_ptr<ICommand> getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, std::exception_ptr ex) override;
};

struct DoubleRetryHandler : public IHandler
{
    explicit DoubleRetryHandler() = default;

    std::shared_ptr<ICommand> getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, std::exception_ptr ex) override;
};
