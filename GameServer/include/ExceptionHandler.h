#pragma once

#include <map>
#include <typeindex>
#include <memory>
#include "Interfaces.h"

struct ExceptionHandler{

    static ExceptionHandler& Instance(){
        static ExceptionHandler ex;
        return ex;
    }

    template<typename CommandType, typename ExceptionType, std::derived_from<IHandler> THandler>
    void RegisterHandler(std::unique_ptr<THandler> handler) {
        m_store[std::type_index(typeid(CommandType))][std::type_index(typeid(ExceptionType))] = std::move(handler);
    }

    template<std::derived_from<ICommand> TCommand, std::derived_from<std::exception> TException >
    std::shared_ptr<ICommand> getCommand(std::shared_ptr<TCommand> cmd, std::shared_ptr<TException> ex, std::type_index exType)
    {
        auto tiCmd = std::type_index(typeid(*cmd));
        return m_store[tiCmd][exType]->getCommand(cmd, ex);
    }

private:
    std::map<std::type_index, std::map<std::type_index, std::shared_ptr<IHandler>>> m_store;
};