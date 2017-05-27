cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

include_directories(../include)
file(GLOB LOCATION_SRC "*.h" "*.cpp")

add_library(location SHARED ${LOCATION_SRC})
set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/ServerPython)

find_package(Qt5Core)

TARGET_LINK_LIBRARIES(location Qt5::Core)

target_link_libraries(location /home/pj/pro/secure/platform/ServerPython/libalignment.so
        /home/pj/pro/secure/platform/ServerPython/libanalysis.so
        /home/pj/pro/secure/platform/ServerPython/libmiddle.so)
