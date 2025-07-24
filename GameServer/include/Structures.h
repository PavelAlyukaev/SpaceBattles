#pragma once
#include "Interfaces.h"

struct Position : public IComponent {
    int x = 0;
    int y = 0;
    Position(int x, int y) : x(x), y(y) {}
};

struct Velocity : public  IComponent {
    int dx = 0;
    int dy = 0;
    Velocity(int dx, int dy) : dx(dx), dy(dy) {}
};

struct Angle: public  IComponent {
    int a = 0;
    int n = 0;
    Angle(int a, int n) : a(a), n(n) {}
};

struct AngleVelocity: public  IComponent {
    int da = 0;
    int n = 0;
    AngleVelocity(int da, int n) : da(da), n(n) {}
};