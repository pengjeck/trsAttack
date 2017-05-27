cmake_minimum_required(VERSION 3.6)
project(proprocess)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

add_library(kits parameter.cpp parameter.h Basic.cpp Basic.h)
set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/ServerPython)

find_package(Qt5Core REQUIRED)

TARGET_LINK_LIBRARIES(kits Qt5::Core)
target_link_libraries(kits ${JSONCPP_LIBRARIES})
