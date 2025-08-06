#pragma once

#include <iostream>
#include <format>
#include <utility>
#include "Interfaces.h"

struct LogCommand : public Command<LogCommand>
{

public:
    template<std::derived_from<ILog> TLog, std::derived_from<ICommand> TCommand>
    LogCommand(std::shared_ptr<TCommand> cmd, std::exception_ptr ex, std::shared_ptr<TLog> log)
            : m_failedCommand(typeid(*cmd).name()), m_exception(ex), m_log(log)
    {}

    void Execute() override
    {
        try
        {
            std::rethrow_exception(m_exception);
        }
        catch (std::exception &e)
        {
            m_log->Error(std::format("Logging exception: {}  from command type: {}", e.what(), m_failedCommand));
        }
    }

private:
    std::string m_failedCommand;
    std::exception_ptr m_exception;
    std::shared_ptr<ILog> m_log;
};

struct RetryCommand : public Command<RetryCommand>
{
public:
    template<std::derived_from<ICommand> TCommand>
    RetryCommand(std::shared_ptr<TCommand> cmd)
            :   m_cmd(cmd)
    {}

    void Execute() override
    {
        m_cmd->Execute();
    }

private:
    std::shared_ptr<ICommand> m_cmd;
};

