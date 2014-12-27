cmake_minimum_required(VERSION 2.8.4)
set(PROJECT_NAME TornelTales)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
project(${PROJECT_NAME})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/Debug")
endif()


set(CMAKE_MODULE_PATH "C:/SFML/cmake/Modules")
set(SFML_ROOT "C:/SFML")

set(SFML_STATIC_LIBRARIES true)

include_directories(${SFML_INCLUDE_DIR} ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DTHOR-STATIC")

set(SOURCE_FILES
    src/AIControlledEntity.cpp
    src/AIControlledEntity.hpp
    src/Combat.hpp
    src/Combat.cpp
    src/constants.cpp
    src/constants.hpp
    src/Equipment.hpp
    src/Equipment.cpp
    src/Effects.hpp
    src/Effects.cpp
    src/Hero.hpp
    src/Hero.cpp
    src/Index.hpp
    src/Index.cpp
    src/IndexClasses.hpp
    src/IndexClasses.cpp
    src/main.cpp
    src/mathfuncs.hpp
    src/mathfuncs.cpp
    src/operators.cpp
    src/operators.hpp
    src/Skill.hpp
    src/Skill.cpp
    src/Screen.cpp
    src/Screen.hpp
    version.hpp
    communication.cpp
    communication.hpp
    enums.hpp
    src/IndexesIndex.hpp
    src/IndexesIndex.cpp
    src/Menu.hpp
    src/Menu.cpp
    define.hpp
    timeFunc.hpp)

set(SERVER_FILES
    src/constants.cpp
    src/constants.hpp
    src/operators.cpp
    src/operators.hpp
    src/Equipment.hpp
    src/Equipment.cpp
    src/Effects.hpp
    src/Effects.cpp
    src/IndexesIndex.hpp
    src/IndexesIndex.cpp
    src/IndexClasses.hpp
    src/IndexClasses.cpp
    src/Skill.cpp
    src/Skill.hpp
    src/AIControlledEntity.cpp
    src/AIControlledEntity.hpp
    src/Index.cpp
    src/Index.hpp
    src/Combat.cpp
    src/Combat.hpp
    src/mathfuncs.hpp
    src/mathfuncs.cpp
    server/FightSubserver.cpp
    server/FightSubserver.hpp
    server/fonctor.hpp
    server/fonctor.cpp
    server/main.cpp
    server/ServerClients.hpp
    server/ServerClients.cpp
    server/structures.hpp
    server/structures.cpp
    version.hpp
    communication.cpp
    communication.hpp
    enums.hpp
    define.hpp
    timeFunc.hpp)

find_package(SFML COMPONENTS network audio graphics window system REQUIRED)

find_library(THOR_LIBRARY_RELEASE
             NAMES thor-s
             PATH_SUFFIXES lib64 lib
             PATHS ${FIND_SFML_PATHS})

find_library(THOR_LIBRARY_DEBUG
             NAMES thor-s-d
             PATH_SUFFIXES lib64 lib
             PATHS ${FIND_SFML_PATHS})

set(THOR_LIBRARY debug ${THOR_LIBRARY_DEBUG}
                 optimized ${THOR_LIBRARY_RELEASE})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


set(PROJECT_NAME TornelServer)
project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME} ${SERVER_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})