cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

#add_executable(decode main.cpp Decode.cpp Decode.h Convert.cpp Convert.h)

add_library(decode SHARED Decode.cpp Decode.h Convert.cpp Convert.h)
set(LIBRARY_OUTPUT_PATH /home/pj/pro/secure/platform/bin)
