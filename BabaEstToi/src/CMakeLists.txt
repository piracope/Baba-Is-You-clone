cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BabaEstToi main.cpp model/gameobject.h model/text.h observer/observer.h observer/subject.h observer/subject.cpp model/baba.h model/baba.cpp model/level.h)

install(TARGETS BabaEstToi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
