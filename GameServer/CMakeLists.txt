cmake_minimum_required(VERSION 3.24)
project(GameServer)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
        include/UEntity.h
        src/UEntity.cpp
        src/Structures.cpp
        include/Structures.h
        include/Interfaces.h
        src/MovingObjectAdapter.cpp
        include/PropertyNames.h
        include/RotatingObjectAdapter.h
        src/RotatingObjectAdapter.cpp
        src/RotatingObjectAdapter.cpp
        src/Rotate.cpp
        include/Move.h
        src/Move.cpp
)
MESSAGE(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameServer/include)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()