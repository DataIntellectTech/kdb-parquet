cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(pq)

add_definitions(-DKXVER=3 -DPROVIDE_LOG_UTILITIES -DTARGET_PLATFORM_LINUX -Wno-write-strings)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Arrow CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)


include_directories(
        # Include the k.h header files
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/c/c"
        "${CMAKE_SOURCE_DIR}/include")

add_library("${PROJECT_NAME}" SHARED src/library.cpp include/library.h src/reader-writer.cc)

target_link_libraries("${PROJECT_NAME}" PRIVATE re2::re2 arrow_static parquet_static arrow_bundled_dependencies)
target_link_libraries("${PROJECT_NAME}" PRIVATE spdlog::spdlog_header_only)


