#pragma once

#include <typeindex>
#include <string>
#include <memory>

struct Position;
struct Velocity;
struct Angle;
struct AngleVelocity;

using ExPtr = std::shared_ptr<std::exception>;


struct IComponent
{
    virtual ~IComponent() = default;
};

struct IMovingObject
{
    virtual Position getPosition() = 0;

    virtual Velocity getVelocity() = 0;

    virtual void setPosition(const Position &) = 0;
};

struct IRotatingObject
{
    virtual Angle getAngle() = 0;

    virtual AngleVelocity getAngleVelocity() = 0;

    virtual void setAngle(const Angle &) = 0;
};

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Execute() = 0;

    [[nodiscard]] virtual std::type_index GetType() const = 0;
};

template<typename Derived>
struct Command : public ICommand
{
    [[nodiscard]] std::type_index GetType() const override
    {
        return typeid(Derived);
    }
};

struct ILog
{
    virtual void Error(std::string_view) = 0;

    virtual void Warning(std::string_view) = 0;

    virtual void Info(std::string_view) = 0;
};

struct IHandler
{
    virtual ~IHandler() = default;

    virtual std::shared_ptr<ICommand> getCommand(std::shared_ptr<ICommand> cmd, std::exception_ptr ex) = 0;
};