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

bool findElem(const Level& lvl, const Position& pos, const ObjectType& type)
{
    const auto state = lvl.getState();
    const auto its {state.equal_range(pos)};
    auto it {its.first};
    while (it != its.second && it->second.getType() != type) ++it;
    if(it != its.second) return true;

    return false;
}

bool findAnywhere(const Level& lvl, const ObjectType& type)
{
    for(const auto& elem : lvl.getState())
    {
        if(elem.second.getType() == type) return true;
    }
    return false;
}

TEST_CASE("Testing the move")
{
    REQUIRE_NOTHROW(Level(level));

    Level lvl {level};

    SECTION("Moving to an empty block")
    {
        lvl.movePlayer(Direction::RIGHT);


        REQUIRE(findElem(lvl, {11, 10}, ObjectType::BABA));
        REQUIRE_FALSE(findElem(lvl, {10, 10}, ObjectType::BABA));
    }

    SECTION("Moving to unaffected block")
    {
        lvl.movePlayer(Direction::LEFT);


        REQUIRE(findElem(lvl, {9, 10}, ObjectType::BABA));
        REQUIRE(findElem(lvl, {9, 10}, ObjectType::GRASS));
    }

    SECTION("Prohibiting moving out of bounds")
    {
        lvl.movePlayer(Direction::UP);
        for(int i = 0; i < 7; i++)
        {
            lvl.movePlayer(Direction::RIGHT);
        }

        REQUIRE(findElem(lvl, {17, 9}, ObjectType::BABA));

        lvl.movePlayer(Direction::RIGHT);

        REQUIRE(findElem(lvl, {17, 9}, ObjectType::BABA));
        REQUIRE_FALSE(findElem(lvl, {18, 9}, ObjectType::BABA));
    }

    SECTION("KILL Rule -> walking into lava")
    {
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT); // baba touches lava :(

        REQUIRE_FALSE(findAnywhere(lvl, ObjectType::BABA));
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

        REQUIRE(findElem(lvl, {10, 13}, ObjectType::ROCK));
    }

    SECTION("PUSH Rule -> Pushing TWO rocks")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);

        REQUIRE(findElem(lvl, {10, 15}, ObjectType::ROCK));
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

        REQUIRE(findElem(lvl, {6, 3}, ObjectType::PUSH));
    }
    SECTION("PUSH/STOP Rules -> Pushing rock against wall")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::LEFT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::RIGHT);

        REQUIRE(findElem(lvl, {11, 12}, ObjectType::ROCK));
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

        REQUIRE(findElem(lvl, {11, 17}, ObjectType::ROCK));
    }

    SECTION("SINK rule -> pushing rock into water")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::DOWN);

        REQUIRE_FALSE(findElem(lvl, {10, 16}, ObjectType::WATER));
        REQUIRE_FALSE(findElem(lvl, {10, 16}, ObjectType::ROCK));
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

        REQUIRE_FALSE(findElem(lvl, {10, 16}, ObjectType::WATER));
        REQUIRE_FALSE(findElem(lvl, {10, 16}, ObjectType::BABA));
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

        REQUIRE(findElem(lvl, {10, 16}, ObjectType::WATER));
        REQUIRE(findElem(lvl, {10, 16}, ObjectType::WIN));
    }

    SECTION("STOP rule -> walking into wall")
    {
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);
        lvl.movePlayer(Direction::DOWN);
        lvl.movePlayer(Direction::RIGHT);

        REQUIRE(findElem(lvl, {11, 12}, ObjectType::BABA));
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

        REQUIRE(findElem(lvl, {12, 10}, ObjectType::ROCK));
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

        REQUIRE_FALSE(findAnywhere(lvl, ObjectType::BABA));
        REQUIRE(findElem(lvl, {13, 10}, ObjectType::ROCK));
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

        REQUIRE_FALSE(findAnywhere(lvl, ObjectType::BABA));
        REQUIRE(findElem(lvl, {3, 3}, ObjectType::ROCK));
    }
    SECTION("WATER IS YOU -> water move, baba doesn't")
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

        REQUIRE(findElem(lvl, {10, 17}, ObjectType::WATER));
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

        REQUIRE(findElem(lvl, {12, 10}, ObjectType::BABA));
    }
}
