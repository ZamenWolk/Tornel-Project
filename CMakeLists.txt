cmake_minimum_required(VERSION 2.8.4)
set(PROJECT_NAME TornelTales)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
project(${PROJECT_NAME})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/Debug")
else()
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/Release")
endif()


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../SFML-updated/cmake/Modules")
set(SFML_ROOT "../SFML-updated")

set(SFML_STATIC_LIBRARIES true)

include_directories(${SFML_INCLUDE_DIR} ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DTHOR-STATIC")

set(SOURCE_FILES
    src/AIControlledEntity.cpp
    src/AIControlledEntity.hpp
    src/Combat.hpp
    src/constants.cpp
    src/constants.hpp
    src/Equipement.hpp
    src/Hero.hpp
    src/Index.hpp
    src/main.cpp
    src/mathfuncs.hpp
    src/operators.cpp
    src/operators.hpp
    src/Skill.hpp
    version.hpp)

set(SERVER_FILES
    server/FightSubserver.cpp
    server/FightSubserver.hpp
    server/fonctor.hpp
    server/main.cpp
    server/ServerClients.hpp
    server/structures.hpp
    version.hpp
    src/constants.cpp
    src/constants.hpp
    src/operators.cpp
    src/operators.hpp)

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
                 optimized THOR_LIBRARY_RELEASE})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


set(PROJECT_NAME TornelServer)
project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSERVER")

add_executable(${PROJECT_NAME} ${SERVER_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})