#pragma once


#include <memory>
#include <queue>
#include "Interfaces.h"
#include "ExceptionHandler.h"

class CommandQueue : Command<CommandQueue>
{
public:
    static CommandQueue& Instance(){
        static CommandQueue cq;
        return cq;
    }


    void Execute() override{
        while (!m_commandQueue.empty()) {
            auto command = std::move(m_commandQueue.front());
            m_commandQueue.pop();

            try {
                command->Execute();
            } catch (const std::exception &ex) {

                auto mex = std::make_shared<std::exception>(ex);
                ExceptionHandler::Instance().getCommand(command, mex,std::type_index(typeid(ex)))->Execute();
            }
        }
    }
    template< std::derived_from<ICommand> TCommand>
    void RegisterCommand(std::unique_ptr<TCommand> cmd){
        m_commandQueue.push(std::move(cmd));
    }

private:
    CommandQueue() = default;
    std::queue<std::shared_ptr<ICommand>> m_commandQueue;
};