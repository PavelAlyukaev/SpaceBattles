#include "Rotate.h"
#include "Structures.h"

void Rotete::Execute() {
    auto [a, b] = m_ro.getAngle();
    auto da = m_ro.getAngleVelocity();
    m_ro.setAngle({a + da.da, b});
}
