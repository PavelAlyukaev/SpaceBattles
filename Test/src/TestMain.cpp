#include "gtest/gtest.h"
#include "UEntity.h"
#include "PropertyNames.h"
#include "Structures.h"
#include "MovingObjectAdapter.h"
#include "Move.h"
#include "RotatingObjectAdapter.h"
#include "Rotate.h"
#include "ExceptionHandler.h"
#include "CommandQueue.h"
#include "Commands.h"
#include "Handlers.h"
#include <memory>
#include <queue>


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
    Rotate(roa).Execute();
    ASSERT_TRUE( roa.getAngle() == Angle(20, 360));
}

TEST(GameServer, IncorrectRotateObj) {
    UEntity entity;

    RotatingObjectAdapter roa(entity);
    EXPECT_THROW(roa.getAngle(), std::runtime_error);
    EXPECT_THROW(roa.getAngleVelocity(), std::runtime_error);
    EXPECT_THROW(roa.setAngle(Angle(5,8)), std::runtime_error);
}
/***************/

std::queue<std::unique_ptr<ICommand>> commandQueue;

class TestException : public std::exception {
private:
    std::string message;

public:
    explicit TestException() : message("Test exception") {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

struct TestCommand : public Command<TestCommand>
{
    void Execute() override
    {
        throw TestException();
    }

    ~TestCommand()override= default;
};

struct TestHandlerCommand : public Command<TestHandlerCommand>
{
    TestHandlerCommand(bool& flag) : m_flag(flag){}

    void Execute() override {m_flag = !m_flag;}
private:

    bool& m_flag;
};

struct TestHandler : public IHandler
{
    explicit TestHandler(bool& flag) : m_flag(flag){}

    std::shared_ptr<ICommand> getCommand([[maybe_unused]]std::shared_ptr<ICommand> cmd, [[maybe_unused]] ExPtr ex) override
    {
       return std::make_shared<TestHandlerCommand>(m_flag);
    }
private:
    bool& m_flag;
};


TEST(GameServer, ExceptionHandler) {

    bool flag = false;
    ExceptionHandler::Instance().RegisterHandler<TestCommand, TestException>(std::make_unique<TestHandler>(flag));
      ASSERT_FALSE( flag);

    auto te = std::make_shared<TestException>();
    auto ww = ExceptionHandler::Instance().getCommand(std::make_shared<TestCommand>(), te,std::type_index(typeid(TestException)));
    ww->Execute();
    ASSERT_TRUE( flag);
}


TEST(GameServer, CommandQueue) {

    bool flag = false;
    ExceptionHandler::Instance().RegisterHandler<TestCommand, TestException>(std::make_unique<TestHandler>(flag));
    CommandQueue::Instance().RegisterCommand(std::make_unique<TestCommand>());
    ASSERT_FALSE( flag);
    CommandQueue::Instance().Execute();
    ASSERT_TRUE( flag);
    CommandQueue::Instance().RegisterCommand(std::make_unique<TestCommand>());
    CommandQueue::Instance().RegisterCommand(std::make_unique<TestCommand>());
    CommandQueue::Instance().Execute();
    ASSERT_TRUE( flag);
}

TEST(GameServer, LogCommand) {

    const auto tc = std::make_shared<TestCommand>();
    const auto log = std::make_shared<Log>();
    auto ex = std::make_shared<TestException>();

    auto lc = LogCommand(tc, ex, log);
    lc.Execute();
    ASSERT_TRUE( log->GetLogMessage().find("Logging exception: Test exception  from command type: ")!= std::string::npos);
    ASSERT_TRUE( log->GetLogMessage().find("TestCommand")!= std::string::npos);
}

TEST(GameServer, LogCommandHandler) {

    const auto log = std::make_shared<Log>();
    ExceptionHandler::Instance().RegisterHandler<TestCommand, TestException>(std::make_unique<LogHandler>(log));
    CommandQueue::Instance().RegisterCommand(std::make_unique<TestCommand>());
    CommandQueue::Instance().Execute();
    auto rr = log->GetLogMessage();

    ASSERT_TRUE( log->GetLogMessage().find("Logging exception: Test exception  from command type: ")!= std::string::npos);
    ASSERT_TRUE( log->GetLogMessage().find("TestCommand")!= std::string::npos);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}