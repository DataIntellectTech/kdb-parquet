#!/bin/sh

prefix=/home/james/CLionProjects/PQ/rawlibs/arrow-apache-arrow-2.0.0/cpp/jemalloc_ep-prefix/src/jemalloc_ep/dist
exec_prefix=/home/james/CLionProjects/PQ/rawlibs/arrow-apache-arrow-2.0.0/cpp/jemalloc_ep-prefix/src/jemalloc_ep/dist
libdir=${exec_prefix}/lib

LD_PRELOAD=${libdir}/libjemalloc.so.2
export LD_PRELOAD
exec "$@"
