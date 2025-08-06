#include "Move.h"
#include "Structures.h"

void Move::Execute()
{
    auto [a, b] = m_mo.getPosition();
    auto [da, db] = m_mo.getVelocity();
    m_mo.setPosition({a + da, b + db});
}
