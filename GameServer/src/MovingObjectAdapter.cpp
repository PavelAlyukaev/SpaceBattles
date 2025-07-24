#include "MovingObjectAdapter.h"
#include "Structures.h"
#include "PropertyNames.h"
#include <cmath>

Position MovingObjectAdapter::getPosition() {
    return *m_entity.getProperty<Position>(PName::Position);
}

void MovingObjectAdapter::setVelocity(const Velocity& v) {
    *m_entity.getProperty<Velocity>(PName::Velocity) = v;
}

void MovingObjectAdapter::setPosition(const Position &) {
    const auto position = m_entity.getProperty<Position>(PName::Position);
    const auto angle = m_entity.getProperty<Angle>(PName::Angle);

    auto nx = position->x * cos(angle->a / angle->n * M_PI / 180);
    auto ny = position->y * sin(angle->a / angle->n * M_PI / 180);

    auto dfd = std::make_unique<Position>(nx, ny);
    m_entity.setProperty<Position>(PName::Position, std::make_unique<Position>(nx, ny));
}
