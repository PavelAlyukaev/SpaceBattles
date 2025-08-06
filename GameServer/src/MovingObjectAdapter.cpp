#include "MovingObjectAdapter.h"
#include "Structures.h"
#include "PropertyNames.h"

Position MovingObjectAdapter::getPosition()
{

    if (auto position = m_entity.getProperty<Position>(PName::Position))
        return *position;
    else
        throw std::runtime_error("It is not possible to read the position");
}

Velocity MovingObjectAdapter::getVelocity()
{
    if (auto velocity = m_entity.getProperty<Velocity>(PName::Velocity))
        return *velocity;
    else
        throw std::runtime_error("It is not possible to read the velocity");
}

void MovingObjectAdapter::setPosition(const Position &pos)
{
    if (!m_entity.hasProperty(PName::Position))
        throw std::runtime_error("It is not possible to change the position.");
    m_entity.setProperty<Position>(PName::Position, std::make_unique<Position>(pos.x, pos.y));
}
