add_library(model STATIC
    enum.h
    gameobject.h
    level.h
    filemanager.h
    baba.h
    enum.cpp
    gameobject.cpp
    level.cpp
    filemanager.cpp
    baba.cpp
)
target_link_libraries(model PRIVATE Qt6::Core)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(copy_levels_src
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)

add_dependencies(model copy_levels_src)
