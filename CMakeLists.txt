cmake_minimum_required(VERSION 3.14)
include(ExternalProject)

project(pq)

add_definitions(-DKXVER=3)

set(ARROW_TAG "apache-arrow-5.0.0")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

# Add the arrow github repository as a submodule and configure for a static build.
ExternalProject_Add(ApacheArrow
        GIT_REPOSITORY
            "https://github.com/apache/arrow.git"
        GIT_TAG
            "${ARROW_TAG}"
        SOURCE_SUBDIR
            "cpp"
        CMAKE_ARGS
            "-DARROW_BUILD_SHARED=OFF"
            "-DARROW_BUILD_STATIC=ON"
            "-DARROW_COMPUTE=ON"
            "-DARROW_CSV=ON"
            "-DARROW_DATASET=ON"
            "-DARROW_DEPENDENCY_SOURCE=BUNDLED"
            "-DARROW_DEPENDENCY_USE_SHARED=OFF"
            "-DARROW_FILESYSTEM=ON"
            "-DARROW_HDFS=ON"
            "-DARROW_JEMALLOC=ON"
            "-DARROW_JSON=ON"
            "-DARROW_ORC=ON"
            "-DARROW_PARQUET=ON"
            "-DARROW_PLASMA=ON"
            "-DARROW_WITH_BROTLI=ON"
            "-DARROW_WITH_BZ2=ON"
            "-DARROW_WITH_LZ4=ON"
            "-DARROW_WITH_SNAPPY=ON"
            "-DARROW_WITH_ZLIB=ON"
            "-DARROW_WITH_ZSTD=ON"
            "-DORC_SOURCE=BUNDLED"
            "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}")

include_directories(
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/c/c"
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_BINARY_DIR}/include")

link_directories(
        "${CMAKE_BINARY_DIR}/lib")

# Create a shared library called libpq or pq.dll with the library and reader-writer files.
add_library("${PROJECT_NAME}" SHARED
        "${CMAKE_SOURCE_DIR}/src/library.cpp"
        "${CMAKE_SOURCE_DIR}/src/reader-writer.cc")

add_dependencies("${PROJECT_NAME}"
        ApacheArrow)

# Link against re2, arrow and spdlog. Use header only & static linking so there are no
# dependencies outside of the libpq file.
target_link_libraries("${PROJECT_NAME}" PRIVATE
        "parquet"
        "arrow"
        "arrow_dataset"
        "arrow_bundled_dependencies"
        "Threads::Threads")

