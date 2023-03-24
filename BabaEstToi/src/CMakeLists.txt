cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    ../resources.qrc
)

install(TARGETS BabaEstToi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
