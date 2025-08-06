#pragma once


#include <memory>
#include <queue>
#include "Interfaces.h"
#include "ExceptionHandler.h"

class CommandQueue : Command<CommandQueue>
{
public:
    static CommandQueue &Instance()
    {
        static CommandQueue cq;
        return cq;
    }


    void Execute() override
    {
        while (!m_commandQueue.empty())
        {
            auto command = std::move(m_commandQueue.front());
            m_commandQueue.pop();
            auto cmdType = std::type_index(typeid(*command)).name();
            try
            {
                command->Execute();
            }
            catch (std::exception& e)
            {
                auto exType = std::type_index(typeid(e)).name();

                std::exception_ptr eptr = std::current_exception();
                ExceptionHandler::Instance().getCommand(command, eptr)->Execute();
            }
        }
    }

    template<std::derived_from<ICommand> TCommand>
    void RegisterCommand(std::unique_ptr<TCommand> cmd)
    {
        auto cmdType = std::type_index(typeid(*cmd)).name();
        m_commandQueue.push(std::move(cmd));
    }

private:
    CommandQueue() = default;

    std::queue<std::shared_ptr<ICommand>> m_commandQueue;
};