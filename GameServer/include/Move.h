#pragma once

#include "Interfaces.h"

class Move : public Command<Move>
{

public:
    explicit Move(IMovingObject &mo) : m_mo(mo)
    {};

    ~Move() override = default;

    void Execute() override;

private:
    IMovingObject &m_mo;
};
