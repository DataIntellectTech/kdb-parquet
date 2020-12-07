cmake_minimum_required(VERSION 3.17)
project(PQ)
SET(CMAKE_BUILD_TYPE Debug)
add_definitions(-DKXVER=3 -DPROVIDE_LOG_UTILITIES -DTARGET_PLATFORM_LINUX -Wno-write-strings -std=c++11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set( CMAKE_VERBOSE_MAKEFILE on )
#set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
link_directories("${CMAKE_SOURCE_DIR}/rawlibs/arrow-apache-arrow-2.0.0/cpp/build/debug/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
add_library(PQ SHARED src/library.cpp include/library.h src/reader-writer.cc)

include_directories(PQ
        SYSTEM PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/rawlibs/arrow-apache-arrow-2.0.0/cpp/src/")


target_link_libraries(PQ
        PRIVATE
        arrow parquet)


