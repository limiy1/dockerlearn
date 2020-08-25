cmake_minimum_required ( VERSION 2.8)
project(helloworld)

set(CMAKE_CXX_STANDARD 11)
set(RdKafka_ROOT /usr)
set(RdKafka_LIBNAME librdkafka.a)

find_package (PkgConfig REQUIRED)
pkg_check_modules (RDKAFKA REQUIRED rdkafka)

find_path(RdKafka_INCLUDE_DIR
    NAMES librdkafka/rdkafka.h
    HINTS ${RdKafka_ROOT}/include
)

find_library(RdKafka_LIBRARY
    NAMES ${RdKafka_LIBNAME} rdkafka
    HINTS ${RdKafka_ROOT}/lib ${RdKafka_ROOT}/lib64
)

#find_path(RdKafka_PACKCONFIG_PATH
#    NAMES rdkafka.pc
#    HINTS /usr/lib/x86_64-linux-gnu/pkgconfig/
#)

message("RDKAFKA header path ${RdKafka_INCLUDE_DIR}")
message("RDKAFKA lib name ${RdKafka_LIBNAME}")
message("RDKAFKA lib: ${RdKafka_LIBRARY}")
#message("RDKAFKA packconfig path: ${RdKafka_PACKCONFIG_PATH}")

#set(ENV{PKG_CONFIG_PATH} "${RdKafka_PACKCONFIG_PATH}")

#pkg_search_module(PKG_RDKAFKA REQUIRED IMPORTED_TARGET rdkafka)
#pkg_check_modules (RDKAFKA REQUIRED rdkafka)
#message("RDKAFKA_LIBRARIES = ${RDKAFKA_LIBRARIES}")

include_directories(${RdKafka_INCLUDE_DIR})

add_executable(helloworld main.cpp)
target_link_libraries(
    helloworld
    pthread
    z
    ssl
    crypto
    sasl2
    zstd
    lz4
    ${CMAKE_DL_LIBS}
    ${RdKafka_LIBRARY}
)
