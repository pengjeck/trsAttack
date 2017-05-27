cmake_minimum_required(VERSION 3.6)
project(platform)

add_executable(test_server test/test_main.cpp)
find_package(Pistache)

target_link_libraries(test_server ${Pistache_LIBRARIES})

file(GLOB LIBS "../bin/*.so")
file(GLOB JSON_SRC "json/*.h")
SET(SRC ${JSON_SRC}
        StatsEndpoint.cpp
        StatsEndpoint.h)
add_library(server SHARED ${SRC})
target_link_libraries(server ${LIBS})
target_link_libraries(server ${Pistache_LIBRARIES})
set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/bin)
find_package(Qt5Core REQUIRED)
TARGET_LINK_LIBRARIES(server Qt5::Core)