cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# >>>>>> dpa >>>>>>>>
add_executable(runDPA
        DPAAnalysis.cpp
        dpa_method.cpp
        dpa_method.h
        analysis_method.cpp
        analysis_method.h)
target_link_libraries(runDPA ${JSONCPP_LIBRARIES} Qt5::Core)
# <<<<<< dpa <<<<<<<<

# >>>>>> cpa >>>>>>>>
add_executable(runCPA
        CPAAnalysis.cpp
        cpa_method.cpp
        cpa_method.h
        analysis_method.cpp
        analysis_method.h)
target_link_libraries(runCPA ${JSONCPP_LIBRARIES} Qt5::Core)
# <<<<<< cpa <<<<<<<<

set(EXECUTABLE_OUTPUT_PATH /home/pj/pro/js/trsapp/server/bin)
