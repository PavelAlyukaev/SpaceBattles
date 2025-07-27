#pragma once

#include "Interfaces.h"

class Move {

public:
    explicit Move(IMovingObject& mo) : m_mo(mo){};

    void Execute();
private:
    IMovingObject& m_mo;
};
