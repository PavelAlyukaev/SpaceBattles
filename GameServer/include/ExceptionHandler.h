#pragma once

#include <map>
#include <typeindex>
#include <memory>
#include "Interfaces.h"

struct ExceptionHandler
{

    static ExceptionHandler &Instance()
    {
        static ExceptionHandler ex;
        return ex;
    }

    template<typename CommandType, typename ExceptionType, std::derived_from<IHandler> THandler>
    void RegisterHandler(std::unique_ptr<THandler> handler)
    {
        auto cmdType = std::type_index(typeid(CommandType)).name();
        m_store[std::type_index(typeid(CommandType))][std::type_index(typeid(ExceptionType))] = std::move(handler);
    }

    template<std::derived_from<ICommand> TCommand>
    std::shared_ptr<ICommand> getCommand(std::shared_ptr<TCommand> cmd, std::exception_ptr eptr)
    {
        std::exception_ptr ex;
        std::shared_ptr<IHandler> result;
        auto tiCmd = std::type_index(typeid(*cmd));
        try
        {
            std::rethrow_exception(eptr);
        }
        catch (const std::exception &e)
        {

            auto exType = std::type_index(typeid(e));
            ex = std::current_exception();
            auto rrr = tiCmd.name();
            result = m_store[tiCmd][exType];
        }
        return result->getCommand(cmd, ex);
    }

private:
    std::map<std::type_index, std::map<std::type_index, std::shared_ptr<IHandler>>> m_store;
};