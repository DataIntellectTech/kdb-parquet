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
        # Include the header files used for this library (library.h)
        "${CMAKE_SOURCE_DIR}/include")

# Create a shared library called libpq or pq.dll with the library and reader-writer files.
add_library("${PROJECT_NAME}" SHARED
        "${CMAKE_SOURCE_DIR}/src/library.cpp"
        "${CMAKE_SOURCE_DIR}/src/reader-writer.cc")

# Link against re2, arrow and spdlog. Use header only & static linking so there are no
# dependencies outside of the libpq file.
target_link_libraries("${PROJECT_NAME}" PRIVATE
        "re2::re2"
        "arrow_static"
        "spdlog::spdlog_header_only")