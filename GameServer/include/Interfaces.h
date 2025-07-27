#pragma once

struct Position;
struct Velocity;
struct Angle;
struct AngleVelocity;


struct IComponent
{
    virtual ~IComponent() = default;
};

struct IMovingObject
{
    virtual Position getPosition() = 0;
    virtual Velocity getVelocity() = 0;
    virtual void setPosition(const Position&) = 0;
};

struct IRotatingObject
{
    virtual Angle getAngle() = 0;
    virtual AngleVelocity getAngleVelocity() = 0;
    virtual void setAngle(const Angle&) = 0;
};