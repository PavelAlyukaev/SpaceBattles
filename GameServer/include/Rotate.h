#pragma once

#include "Interfaces.h"

class Rotate : public Command<Rotate> {
public:
    explicit Rotate(IRotatingObject &ro) : m_ro(ro) {};

    ~Rotate() override = default;

    void Execute() override;

private:
    IRotatingObject &m_ro;
};