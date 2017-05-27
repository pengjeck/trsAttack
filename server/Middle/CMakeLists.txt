cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

file(GLOB MIDDLE_SRC "*.h" "*.cpp")
add_library(middle SHARED ${MIDDLE_SRC})

find_package(Qt5Core)

TARGET_LINK_LIBRARIES(middle Qt5::Core)

set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/ServerPython)

# configure_file(Convert.h ../include/decode/Convert.h COPYONLY)
# configure_file(Decode.h ../include/decode/Decode.h COPYONLY)

