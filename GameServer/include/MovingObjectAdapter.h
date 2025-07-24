#pragma once
#include "Interfaces.h"
#include "UEntity.h"

struct MovingObjectAdapter : public IMovingObject {

    MovingObjectAdapter(const UEntity &entity) : m_entity(entity) {}

    Position getPosition() override;

    void setVelocity(const Velocity &) override;

    void setPosition(const Position &) override;

private:
    UEntity m_entity;
};
