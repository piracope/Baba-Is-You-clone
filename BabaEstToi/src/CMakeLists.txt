cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


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
    controller/consolecontroller.h
    controller/consolecontroller.cpp
    view/mainwindow.cpp
    view/mainwindow.h
    view/mainwindow.ui
    view/babaChar.cpp
    view/babahChar.h
)

target_link_libraries(BabaEstToi PRIVATE Qt6::Widgets)

add_custom_target(copy_levels_src
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)

add_dependencies(BabaEstToi copy_levels_src)

install(TARGETS BabaEstToi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
