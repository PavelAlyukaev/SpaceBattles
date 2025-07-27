#include "gtest/gtest.h"
#include "UEntity.h"
#include "PropertyNames.h"
#include "Structures.h"
#include "MovingObjectAdapter.h"
#include "Move.h"
#include "RotatingObjectAdapter.h"
#include "Rotate.h"
#include <memory>


TEST(GameServer, CorrectMoveObj) {
   UEntity entity;

    entity.setProperty<Position>(PName::Position,std::make_unique<Position>(12, 5));
    entity.setProperty<Angle>(PName::Angle, std::make_unique<Angle>(0, 360));
    entity.setProperty<Velocity>(PName::Velocity,std::make_unique<Velocity>(-7, 3));

    MovingObjectAdapter moa(entity);
    Move(moa).Execute();
    ASSERT_TRUE( moa.getPosition() == Position(5,8));
}

TEST(GameServer, IncorrectMoveObj) {
    UEntity entity;

    MovingObjectAdapter moa(entity);
    EXPECT_THROW(moa.getPosition(), std::runtime_error);
    EXPECT_THROW(moa.getVelocity(), std::runtime_error);
    EXPECT_THROW(moa.setPosition(Position(5,8)), std::runtime_error);
}

TEST(GameServer, CorrectRotateObj) {
    UEntity entity;

    entity.setProperty<Angle>(PName::Angle, std::make_unique<Angle>(0, 360));
    entity.setProperty<AngleVelocity>(PName::AngleVelocity,std::make_unique<AngleVelocity>(20));

    RotatingObjectAdapter roa(entity);
    Rotete(roa).Execute();
    ASSERT_TRUE( roa.getAngle() == Angle(20, 360));
}

TEST(GameServer, IncorrectRotateObj) {
    UEntity entity;

    RotatingObjectAdapter roa(entity);
    EXPECT_THROW(roa.getAngle(), std::runtime_error);
    EXPECT_THROW(roa.getAngleVelocity(), std::runtime_error);
    EXPECT_THROW(roa.setAngle(Angle(5,8)), std::runtime_error);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}