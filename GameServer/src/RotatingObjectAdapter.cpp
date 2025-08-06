#include "RotatingObjectAdapter.h"
#include "Structures.h"
#include "PropertyNames.h"

Angle RotatingObjectAdapter::getAngle()
{

    if (auto angle = m_entity.getProperty<Angle>(PName::Angle))
        return *angle;
    else
        throw std::runtime_error("It is not possible to read the angle");
}

AngleVelocity RotatingObjectAdapter::getAngleVelocity()
{
    if (auto angleVelocity = m_entity.getProperty<AngleVelocity>(PName::AngleVelocity))
        return *angleVelocity;
    else
        throw std::runtime_error("It is not possible to read the angle velocity");
}

void RotatingObjectAdapter::setAngle(const Angle &angle)
{
    if (!m_entity.hasProperty(PName::Angle))
        throw std::runtime_error("It is not possible to change the angle.");
    m_entity.setProperty<Angle>(PName::Angle, std::make_unique<Angle>(angle.a, angle.n));
}
