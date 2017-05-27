cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

file(GLOB ANALYSIS_SRC "*.h" "*.cpp")
add_library(analysis SHARED ${ANALYSIS_SRC})
find_package(Qt5Core REQUIRED)

TARGET_LINK_LIBRARIES(analysis Qt5::Core)
set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/ServerPython)
