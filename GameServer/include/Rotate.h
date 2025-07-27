#pragma once

#include "Interfaces.h"

class Rotete {
public:
    explicit Rotete(IRotatingObject& ro) : m_ro(ro){};

    void Execute();
private:
    IRotatingObject& m_ro;
};


