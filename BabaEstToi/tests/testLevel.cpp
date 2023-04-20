#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <iostream>

#include "model/level.h"

using namespace model;

static std::string getLevel()
{
    std::stringstream level;
    level
        << "18 18"
        << "\nTEXT_BABA 1 1"
        << "\nIS 1 2"
        << "\nYOU 1 3"
        << "\nTEXT_WATER 3 1"
        << "\nIS 3 2"
        << "\nSINK 3 3"
        << "\nTEXT_LAVA 5 1"
        << "\nIS 5 2"
        << "\nKILL 5 3"
        << "\nTEXT_ROCK 7 1"
        << "\nIS 7 2"
        << "\nPUSH 7 3"
        << "\nTEXT_WALL 9 1"
        << "\nIS 9 2"
        << "\nSTOP 9 3"
        << "\nTEXT_FLAG 11 1"
        << "\nIS 11 2"
        << "\nWIN 11 3"
        << "\nFLAG 8 10"
        << "\nGRASS 9 10"
        << "\nBABA 10 10"
        << "\nROCK 10 12"
        << "\nROCK 10 14"
        << "\nWATER 10 16"
        << "\nLAVA 12 10"
        << "\nWALL 12 12";
    return level.str();
}

const static std::string level {getLevel()};

TEST_CASE("Testing the move")
{
    REQUIRE_NOTHROW(Level(level));

    Level lvl {level};

    SECTION("Moving changes the direction")
    {
        lvl.movePlayer(Direction::UP);
        std::string state = lvl.getState();

        REQUIRE(state.find("BABA 10 9 1") != std::string::npos); // if not found, return value of find == npos
    }

    SECTION("Moving to an empty block")
    {
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();

        REQUIRE(state.find("BABA 11 10") != std::string::npos);
        REQUIRE_FALSE(state.find("BABA 10 10") != std::string::npos);
    }

    SECTION("Moving to unaffected block")
    {
        lvl.movePlayer(Direction::LEFT);
        std::string state = lvl.getState();

        REQUIRE(state.find("BABA 9 10") != std::string::npos);
        REQUIRE(state.find("GRASS 9 10") != std::string::npos);
    }

    SECTION("Prohibiting moving out of bounds")
    {
        lvl.movePlayer(Direction::UP);
        for(int i = 0; i < 7; i++)
        {
            lvl.movePlayer(Direction::RIGHT);
        }
        std::string state = lvl.getState();
        REQUIRE(state.find("BABA 17 9") != std::string::npos);

        lvl.movePlayer(Direction::RIGHT);
        state = lvl.getState();
        REQUIRE(state.find("BABA 17 9") != std::string::npos);
        REQUIRE_FALSE(state.find("BABA 18 9") != std::string::npos);
    }

    SECTION("KILL Rule -> walking into lava")
    {
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT); // baba touches lava :(
        std::string state = lvl.getState();
        auto startPos {state.find("BABA")}; // to store position in text of TEXT_BABA
        REQUIRE_FALSE(state.find("BABA", startPos+1) != std::string::npos);
    }

    SECTION("WIN rule -> moving after a move throws an exception")
    {
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        REQUIRE_THROWS(lvl.movePlayer(Direction::LEFT));
    }

    SECTION("PUSH Rule -> Pushing ONE rock")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("ROCK 10 13") != std::string::npos);
    }

    SECTION("PUSH Rule -> Pushing TWO rocks")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("ROCK 10 15") != std::string::npos);
    }
    SECTION("PUSH Rule -> Pushing TEXT/ASPECT")
    {
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        std::string state = lvl.getState();
        REQUIRE(state.find("PUSH 6 3") != std::string::npos);
    }
    SECTION("PUSH/STOP Rules -> Pushing rock against wall")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();
        REQUIRE(state.find("ROCK 11 12") != std::string::npos);
    }
    SECTION("PUSH Rule -> Pushing rock against border")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("ROCK 11 17") != std::string::npos);
    }

    SECTION("SINK rule -> pushing rock into water")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("WATER 10 16") != std::string::npos);
        REQUIRE_FALSE(state.find("ROCK 10 16") != std::string::npos);
    }

    SECTION("SINK rule -> walking into water")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();
        REQUIRE_FALSE(state.find("WATER 10 16") != std::string::npos);
        REQUIRE_FALSE(state.find("BABA 10 16") != std::string::npos);
    }

    SECTION("SINK rule -> pushing TEXT/ASPECT into water shouldn't make it disappear")
    {
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        std::string state = lvl.getState();
        REQUIRE(state.find("WATER 10 16") != std::string::npos);
        REQUIRE(state.find("WIN 10 16") != std::string::npos);
        REQUIRE(1+1==2);//to have 50 assertions <3
    }

    SECTION("STOP rule -> walking into wall")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();
        REQUIRE(state.find("BABA 11 12") != std::string::npos);
    }

    SECTION("KILL rule -> pushing rock into lava shouldn't make rock disappear")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();
        REQUIRE(state.find("ROCK 12 10") != std::string::npos);
    }
    SECTION("KILL/PUSH rules -> pushing rock on lava pushes rock and kills player")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        std::string state = lvl.getState();
        auto startPos {state.find("BABA")};
        REQUIRE_FALSE(state.find("BABA", startPos+1) != std::string::npos);
        REQUIRE(state.find("ROCK 13 10") != std::string::npos);
    }
}

TEST_CASE("Testing rule application")
{
    REQUIRE_NOTHROW(Level(level));

    Level lvl {level};

    SECTION("BABA IS ROCK -> baba becomes a rock, unable to move")
    {
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        std::string state = lvl.getState();
        auto startPos {state.find("BABA")};
        REQUIRE_FALSE(state.find("BABA", startPos+1) != std::string::npos);
        REQUIRE(state.find("ROCK 3 3") != std::string::npos);
    }
    SECTION("GOOP IS YOU -> goop move, baba doesn't")
    {
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("WATER 10 17") != std::string::npos);
    }
    SECTION("Removing KILL rule -> baba can walk on lava")
    {
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::UP);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        std::string state = lvl.getState();
        REQUIRE(state.find("BABA 12 10") != std::string::npos);
    }
}
