cmake_minimum_required(VERSION 2.8.4)
set(PROJECT_NAME TornelTales)
project(${PROJECT_NAME})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
else()
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/debug")
endif()


set(CMAKE_MODULE_PATH "C:/SFML/cmake/Modules")
set(SFML_ROOT "C:/SFML")

set(SFML_STATIC_LIBRARIES true)

include_directories(${SFML_INCLUDE_DIR} ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DTHOR-STATIC -static")

set(COMMON_FILES
    Classes/Singleton.hpp
    global/define.hpp
    global/functions.hpp
    global/functions.cpp
    global/communication.hpp
    global/communication.cpp
    Classes/Math/math.hpp
    Classes/Math/math.cpp
    Enums/communication.hpp
    Enums/communication.cpp
    version.hpp
    version.cpp
    Classes/Skills/Skill.cpp
    Classes/Skills/Skill.hpp
    Classes/Equipment/Effects.hpp
    Classes/Equipment/Effects.cpp
    Classes/Equipment/Equipment.hpp
    Classes/Equipment/Equipment.cpp
    Classes/Indexes/Index.hpp
    Classes/Indexes/Index.cpp
    Classes/Indexes/IndexClasses.hpp
    Classes/Indexes/IndexClasses.cpp
    Classes/Indexes/IndexesIndex.hpp
    Classes/Indexes/IndexesIndex.cpp
    Classes/communication.hpp
    Classes/communication.cpp
    Enums/Equipment.hpp)

set(CLIENT_FILES
    client.cpp
    Apps/App.cpp
    Apps/App.hpp
    Apps/Combat.cpp
    Apps/Combat.hpp
    Classes/CharEntities/AIEntity.cpp
    Classes/CharEntities/AIEntity.hpp
    Classes/CharEntities/CombatEntity.cpp
    Classes/CharEntities/CombatEntity.hpp
    Classes/CharEntities/Hero.cpp
    Classes/CharEntities/Hero.hpp
    Enums/Combat.hpp)

set(SERVER_FILES
    server.cpp
    Enums/serverEvents.hpp
    Enums/serverEvents.cpp
    Classes/Server/Subservers.cpp
    Classes/Server/Subservers.hpp
    Classes/Server/ServerClient.cpp
    Classes/Server/ServerClient.hpp
    Classes/Server/fonctor.cpp
    Classes/Server/fonctor.hpp)

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

add_executable(${PROJECT_NAME} ${CLIENT_FILES} ${COMMON_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


set(PROJECT_NAME TornelServer)
project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME} ${SERVER_FILES} ${COMMON_FILES})
target_link_libraries(${PROJECT_NAME} ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})