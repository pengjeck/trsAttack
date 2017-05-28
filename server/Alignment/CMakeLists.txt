cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

# >>>>>>>> statci alignment >>>>>>>>
add_executable(runStaticAlignment   # exe name
        staticAlignment.cpp
        staticalignment_method.h
        staticalignment_method.cpp
        alignment_method.cpp
        alignment_method.h)
target_link_libraries(runStaticAlignment ${JSONCPP_LIBRARIES} Qt5::Core)
# <<<<<<<< static alignment <<<<<<<<

# >>>>>>>> fft alignment >>>>>>>>>
add_executable(runFFT
        FFTAlignment.cpp
        fft_method.h
        fft_method.cpp
        alignment_method.cpp
        alignment_method.h)
target_link_libraries(runFFT ${JSONCPP_LIBRARIES} Qt5::Core)
# <<<<<<<< fft alignment <<<<<<<<<

# >>>>>>>>> poc alignment >>>>>>>>>>
add_executable(runPOC
        POCAlignment.cpp
        poc.cpp
        poc.h
        alignment_method.cpp
        alignment_method.h)
target_link_libraries(runPOC ${JSONCPP_LIBRARIES} Qt5::Core)
# <<<<<<<<< poc alignment <<<<<<<<<<<

add_executable(runDTW
        DTWAlignment.cpp
        dtw.cpp
        dtw.h
        alignment_method.cpp
        alignment_method.h)
target_link_libraries(runDTW ${JSONCPP_LIBRARIES} Qt5::Core)

set(EXECUTABLE_OUTPUT_PATH /home/pj/pro/js/trsapp/server/bin)
