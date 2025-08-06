#pragma once

#include "Interfaces.h"
#include "UEntity.h"

struct MovingObjectAdapter : public IMovingObject
{

    explicit MovingObjectAdapter(UEntity &entity) : m_entity(entity)
    {}

    Position getPosition() override;

    Velocity getVelocity() override;

    void setPosition(const Position &) override;

private:
    UEntity &m_entity;
};
