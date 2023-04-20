cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BabaEstToiTests
    testLevel.cpp
    ../src/model/enum.h
    ../src/model/enum.cpp
    ../src/model/gameobject.h
    ../src/model/gameobject.cpp
    ../src/model/level.h
    ../src/model/level.cpp
)
target_include_directories(BabaEstToiTests PRIVATE
    ../src
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_custom_target(copy_levels_test
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)

add_dependencies(BabaEstToi copy_levels_test)


target_link_libraries(BabaEstToiTests PRIVATE Catch2::Catch2WithMain)
