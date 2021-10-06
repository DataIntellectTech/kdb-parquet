cmake_minimum_required(VERSION 3.14)
include(ExternalProject)

project(pq)

set(PQ_MAJOR 1)
set(PQ_MINOR 0)
set(PQ_PATCH 0)
set(PQ_VERSION_STR "${PQ_MAJOR}.${PQ_MINOR}.${PQ_PATCH}")

string(TIMESTAMP PQ_BUILD_DATE "%Y.%m.%d")
string(TIMESTAMP PQ_BUILD_TIME "%H.%M.%S")

add_definitions(-DKXVER=3)

set(ARROW_TAG "apache-arrow-5.0.0")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

# -------------------------------------------------------------------------------
# Configure external Apache Arrow target
# -------------------------------------------------------------------------------

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
            "-DARROW_COMPUTE=OFF"
            "-DARROW_CSV=ON"
            "-DARROW_DATASET=ON"
            "-DARROW_DEPENDENCY_SOURCE=BUNDLED"
            "-DARROW_DEPENDENCY_USE_SHARED=OFF"
            "-DARROW_FILESYSTEM=ON"
            "-DARROW_HDFS=OFF"
            "-DARROW_JEMALLOC=ON"
            "-DARROW_JSON=OFF"
            "-DARROW_ORC=OFF"
            "-DARROW_PARQUET=ON"
            "-DARROW_PLASMA=OFF"
            "-DARROW_WITH_BROTLI=ON"
            "-DARROW_WITH_BZ2=ON"
            "-DARROW_WITH_LZ4=ON"
            "-DARROW_WITH_SNAPPY=ON"
            "-DARROW_WITH_ZLIB=ON"
            "-DARROW_WITH_ZSTD=ON"
            "-DORC_SOURCE=BUNDLED"
            "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}")

# -------------------------------------------------------------------------------
# Setup include/link directories
# -------------------------------------------------------------------------------
include_directories(
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/c/c" # headers from kx third party dependency (k.h)
        "${CMAKE_BINARY_DIR}/include"           # binary dir contains headers installed by the ApacheArrow target
        "${CMAKE_SOURCE_DIR}/include")          # this is the headers for the library itself (library.h)

link_directories(
        "${CMAKE_BINARY_DIR}/lib")              # libraries from ApacheArrow target (libarrow.a, libparquet.a etc...)

# Copy configuration header file and replace all of the cmake variable with
configure_file("${CMAKE_SOURCE_DIR}/include/config.h" "${CMAKE_BINARY_DIR}/include/config.h")

# -------------------------------------------------------------------------------
# Build Targets
# -------------------------------------------------------------------------------

# Create a shared library called libpq.so (linux/osx) or pq.dll (windows).
add_library("${PROJECT_NAME}" SHARED
        "${CMAKE_SOURCE_DIR}/src/library.cpp"
        "${CMAKE_SOURCE_DIR}/src/reader-writer.cc")

# ApacheArrow target must be built first before we can build libpq.
add_dependencies("${PROJECT_NAME}"
        ApacheArrow)

# Link against the static ApacheArrow binaries which should leave us with no dynamically linked dependencies
# outside of usual libc.
target_link_libraries("${PROJECT_NAME}" PRIVATE
        "parquet"
        "arrow"
        "arrow_dataset"
        "arrow_bundled_dependencies"
        "Threads::Threads")

# -------------------------------------------------------------------------------
# Post-Build Packaging
# -------------------------------------------------------------------------------
add_custom_target(create_zip COMMAND
        ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_BINARY_DIR}/libpq-${PQ_VERSION_STR}-${ARROW_TAG}.tar.gz"
        "${CMAKE_SOURCE_DIR}/README.md"
        "${CMAKE_BINARY_DIR}/*.so")

add_dependencies(create_zip
        "${PROJECT_NAME}")