#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Test of MyClass") {

    SECTION("Sum"){
        REQUIRE(1+1==2);
    }
}

/*SCENARIO("test")
{
    GIVEN("a level with baba is you")
    {
        std::string s {"5 5\nwall 2 2\nbaba 0 2 3\ntext_baba 0 3\nis 1 3\nyou 2 3\n"};
        model::Level level{s};
        WHEN("a valid move")
        {
            THEN("move")
            {
                REQUIRE_NOTHROW(level.movePlayer(model::Direction::RIGHT));
            }
        }
    }
}*/
