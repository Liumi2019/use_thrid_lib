cmake_minimum_required(VERSION 3.10)
project(testThirdLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O2")

include_directories(thirdLib)
aux_source_directory(thirdLib SRC)
add_library(srcLib STATIC ${SRC})

include_directories(thirdLib/pb_src)
aux_source_directory(thirdLib/pb_src PB_SRC)
add_library(pb_srcLib STATIC ${PB_SRC})

include_directories(mydebug)
aux_source_directory(mydebug DEBUG_SRC)
add_library(debug_srcLib STATIC ${DEBUG_SRC})

include_directories(mediapipe)
aux_source_directory(mediapipe MEDIAPIPE_SRC)
add_library(mediapipe_srcLib STATIC ${MEDIAPIPE_SRC})

add_executable(testThirdLib main.cpp)

target_link_libraries(testThirdLib
                        srcLib
                        pb_srcLib
                        mediapipe_srcLib
                        debug_srcLib
                        glog
                        gtest
                        pthread
                        protobuf
                        absl)
