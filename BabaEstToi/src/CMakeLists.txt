cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

add_custom_target(copy_levels
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)

add_executable(BabaEstToi
    main.cpp
    model/enum.h
    model/enum.cpp
    model/gameobject.h
    model/gameobject.cpp
    model/baba.h
    model/baba.cpp
    model/level.h
    model/level.cpp
    model/filemanager.h
    model/filemanager.cpp
    observer/observer.h
    observer/subject.h
    observer/subject.cpp
    view/view.h
    view/view.cpp
    controller/controller.h
    controller/controller.cpp
)

add_dependencies(BabaEstToi copy_levels)

install(TARGETS BabaEstToi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
