#include <catch2/catch_test_macros.hpp>
#include "MyClass.h"

TEST_CASE( "Test of MyClass") {
    MyClass myClass;

    SECTION("Sum"){
        REQUIRE(myClass.sum(2,2) == 4);
    }
    SECTION("Wrong Sum"){
        REQUIRE_FALSE(myClass.sum(2,2) == 5);
    }
}
