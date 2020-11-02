# Options used to build arrow:

## Compile and link options:
### Compiler flags to append when compiling Arrow
set(ARROW_CXXFLAGS "")
### Build static libraries
set(ARROW_BUILD_STATIC "ON")
### Build shared libraries
set(ARROW_BUILD_SHARED "ON")
### Arbitrary string that identifies the kind of package
### (for informational purposes)
set(ARROW_PACKAGE_KIND "")
### The Arrow git commit id (if any)
set(ARROW_GIT_ID "")
### The Arrow git commit description (if any)
set(ARROW_GIT_DESCRIPTION "")
### Exclude deprecated APIs from build
set(ARROW_NO_DEPRECATED_API "OFF")
### Use ccache when compiling (if available)
set(ARROW_USE_CCACHE "ON")
### Use ld.gold for linking on Linux (if available)
set(ARROW_USE_LD_GOLD "OFF")
### Use precompiled headers when compiling
set(ARROW_USE_PRECOMPILED_HEADERS "OFF")
### Compile-time SIMD optimization level
set(ARROW_SIMD_LEVEL "SSE4_2")
### Max runtime SIMD optimization level
set(ARROW_RUNTIME_SIMD_LEVEL "MAX")
### Arm64 arch and extensions
set(ARROW_ARMV8_ARCH "armv8-a")
### Build with Altivec if compiler has support
set(ARROW_ALTIVEC "ON")
### Build Arrow libraries with RATH set to $ORIGIN
set(ARROW_RPATH_ORIGIN "OFF")
### Build Arrow libraries with install_name set to @rpath
set(ARROW_INSTALL_NAME_RPATH "ON")
### Pass -ggdb flag to debug builds
set(ARROW_GGDB_DEBUG "ON")

## Test and benchmark options:
### Build the Arrow examples
set(ARROW_BUILD_EXAMPLES "ON")
### Build the Arrow googletest unit tests
set(ARROW_BUILD_TESTS "OFF")
### Enable timing-sensitive tests
set(ARROW_ENABLE_TIMING_TESTS "ON")
### Build the Arrow integration test executables
set(ARROW_BUILD_INTEGRATION "OFF")
### Build the Arrow micro benchmarks
set(ARROW_BUILD_BENCHMARKS "OFF")
### Build the Arrow micro reference benchmarks
set(ARROW_BUILD_BENCHMARKS_REFERENCE "OFF")
### Linkage of Arrow libraries with unit tests executables.
set(ARROW_TEST_LINKAGE "shared")
### Build Arrow Fuzzing executables
set(ARROW_FUZZING "OFF")
### Enable unit tests which use large memory
set(ARROW_LARGE_MEMORY_TESTS "OFF")

## Lint options:
### Only define the lint and check-format targets
set(ARROW_ONLY_LINT "OFF")
### If off, 'quiet' flags will be passed to linting tools
set(ARROW_VERBOSE_LINT "OFF")
### Build with C++ code coverage enabled
set(ARROW_GENERATE_COVERAGE "OFF")

## Checks options:
### Run the test suite using valgrind --tool=memcheck
set(ARROW_TEST_MEMCHECK "OFF")
### Enable Address Sanitizer checks
set(ARROW_USE_ASAN "OFF")
### Enable Thread Sanitizer checks
set(ARROW_USE_TSAN "OFF")
### Enable Undefined Behavior sanitizer checks
set(ARROW_USE_UBSAN "OFF")

## Project component options:
### Build Arrow commandline utilities
set(ARROW_BUILD_UTILITIES "OFF")
### Build the Arrow Compute Modules
set(ARROW_COMPUTE "ON")
### Build the Arrow CSV Parser Module
set(ARROW_CSV "OFF")
### Build the Arrow CUDA extensions (requires CUDA toolkit)
set(ARROW_CUDA "OFF")
### Build the Arrow Dataset Modules
set(ARROW_DATASET "OFF")
### Build the Arrow Filesystem Layer
set(ARROW_FILESYSTEM "OFF")
### Build the Arrow Flight RPC System (requires GRPC, Protocol Buffers)
set(ARROW_FLIGHT "OFF")
### Build the Gandiva libraries
set(ARROW_GANDIVA "OFF")
### Build the Arrow HDFS bridge
set(ARROW_HDFS "OFF")
### Build the HiveServer2 client and Arrow adapter
set(ARROW_HIVESERVER2 "OFF")
### Build the Arrow IPC extensions
set(ARROW_IPC "ON")
### Build the Arrow jemalloc-based allocator
set(ARROW_JEMALLOC "ON")
### Build the Arrow JNI lib
set(ARROW_JNI "OFF")
### Build Arrow with JSON support (requires RapidJSON)
set(ARROW_JSON "OFF")
### Build the Arrow mimalloc-based allocator
set(ARROW_MIMALLOC "OFF")
### Build the Parquet libraries
set(ARROW_PARQUET "ON")
### Build the Arrow ORC adapter
set(ARROW_ORC "OFF")
### Build the plasma object store along with Arrow
set(ARROW_PLASMA "OFF")
### Build the plasma object store java client
set(ARROW_PLASMA_JAVA_CLIENT "OFF")
### Build the Arrow CPython extensions
set(ARROW_PYTHON "OFF")
### Build Arrow with S3 support (requires the AWS SDK for C++)
set(ARROW_S3 "OFF")
### Build Arrow with TensorFlow support enabled
set(ARROW_TENSORFLOW "OFF")
### Build the Arrow testing libraries
set(ARROW_TESTING "OFF")

## Thirdparty toolchain options:
### Method to use for acquiring arrow's build dependencies
set(ARROW_DEPENDENCY_SOURCE "AUTO")
### Show output from ExternalProjects rather than just logging to files
set(ARROW_VERBOSE_THIRDPARTY_BUILD "OFF")
### Link to shared libraries
set(ARROW_DEPENDENCY_USE_SHARED "ON")
### Rely on boost shared libraries where relevant
set(ARROW_BOOST_USE_SHARED "ON")
### Rely on Brotli shared libraries where relevant
set(ARROW_BROTLI_USE_SHARED "ON")
### Rely on Bz2 shared libraries where relevant
set(ARROW_BZ2_USE_SHARED "ON")
### Rely on GFlags shared libraries where relevant
set(ARROW_GFLAGS_USE_SHARED "ON")
### Rely on gRPC shared libraries where relevant
set(ARROW_GRPC_USE_SHARED "ON")
### Rely on lz4 shared libraries where relevant
set(ARROW_LZ4_USE_SHARED "ON")
### Rely on OpenSSL shared libraries where relevant
set(ARROW_OPENSSL_USE_SHARED "ON")
### Rely on Protocol Buffers shared libraries where relevant
set(ARROW_PROTOBUF_USE_SHARED "ON")
### Rely on thrift shared libraries where relevant
set(ARROW_THRIFT_USE_SHARED "ON")
### Rely on utf8proc shared libraries where relevant
set(ARROW_UTF8PROC_USE_SHARED "ON")
### Rely on snappy shared libraries where relevant
set(ARROW_SNAPPY_USE_SHARED "ON")
### Rely on utf8proc shared libraries where relevant
set(ARROW_UTF8PROC_USE_SHARED "ON")
### Rely on zstd shared libraries where relevant
set(ARROW_ZSTD_USE_SHARED "ON")
### Build libraries with glog support for pluggable logging
set(ARROW_USE_GLOG "OFF")
### Build with backtrace support
set(ARROW_WITH_BACKTRACE "ON")
### Build with Brotli compression
set(ARROW_WITH_BROTLI "OFF")
### Build with BZ2 compression
set(ARROW_WITH_BZ2 "OFF")
### Build with lz4 compression
set(ARROW_WITH_LZ4 "OFF")
### Build with Snappy compression
set(ARROW_WITH_SNAPPY "OFF")
### Build with zlib compression
set(ARROW_WITH_ZLIB "OFF")
### Build with zstd compression
set(ARROW_WITH_ZSTD "OFF")
### Build with support for Unicode properties using the utf8proc library
set(ARROW_WITH_UTF8PROC "ON")

## Parquet options:
### Depend only on Thirdparty headers to build libparquet.
### Always OFF if building binaries
set(PARQUET_MINIMAL_DEPENDENCY "OFF")
### Build the Parquet executable CLI tools. Requires static libraries to be built.
set(PARQUET_BUILD_EXECUTABLES "OFF")
### Build the Parquet examples. Requires static libraries to be built.
set(PARQUET_BUILD_EXAMPLES "ON")
### Build support for encryption. Fail if OpenSSL is not found
set(PARQUET_REQUIRE_ENCRYPTION "OFF")

## Gandiva options:
### Build the Gandiva JNI wrappers
set(ARROW_GANDIVA_JAVA "OFF")
### Include -static-libstdc++ -static-libgcc when linking with
### Gandiva static libraries
set(ARROW_GANDIVA_STATIC_LIBSTDCPP "OFF")
### Compiler flags to append when pre-compiling Gandiva operations
set(ARROW_GANDIVA_PC_CXX_FLAGS "")

## Advanced developer options:
### Compile with extra error context (line numbers, code)
set(ARROW_EXTRA_ERROR_CONTEXT "OFF")
### If enabled install ONLY targets that have already been built. Please be
### advised that if this is enabled 'install' will fail silently on components
### that have not been built
set(ARROW_OPTIONAL_INSTALL "OFF")