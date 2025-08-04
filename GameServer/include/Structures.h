#pragma once
#include "Interfaces.h"

struct Position : public IComponent {
    int x = 0;
    int y = 0;
    Position(int x, int y) : x(x), y(y) {}
    ~Position() override = default;
    auto operator ==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Velocity : public  IComponent {
    int dx = 0;
    int dy = 0;
    Velocity(int dx, int dy) : dx(dx), dy(dy) {}
    ~Velocity() override = default;

};

struct Angle: public  IComponent {
    int a = 0;
    int n = 0;
    Angle(int a, int n) : a(a), n(n) {}
    ~Angle() override = default;
    auto operator ==(const Angle& other) const
    {
        return a == other.a && n == other.n;
    }
};

struct AngleVelocity: public  IComponent {
    int da = 0;
    AngleVelocity(int da) : da(da) {}
    ~AngleVelocity() override = default;
};

struct Log: public ILog
{
    void Error(std::string_view s) override {m_logMessage = s;}
    void Warning(std::string_view s) override {m_logMessage = s;}
    void Info(std::string_view s) override {m_logMessage = s;}
    std::string GetLogMessage(){return m_logMessage; }

private:
    std::string m_logMessage;
};