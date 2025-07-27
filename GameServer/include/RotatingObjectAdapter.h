#pragma once
#include "Interfaces.h"
#include "UEntity.h"

struct RotatingObjectAdapter : public IRotatingObject {

    explicit RotatingObjectAdapter(UEntity& entity) : m_entity(entity) {}

    Angle getAngle() override;

    AngleVelocity getAngleVelocity() override;

    void setAngle(const Angle &) override;

private:
    UEntity& m_entity;
};

