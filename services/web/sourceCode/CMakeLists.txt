cmake_minimum_required ( VERSION 2.8)
project(helloworld)

set(CMAKE_CXX_STANDARD 11)
set(RdKafka_ROOT /usr)
set(RdKafka_LIBNAME librdkafka)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

find_path(RdKafka_INCLUDE_DIR
    NAMES librdkafka/rdkafka.h
    HINTS ${RdKafka_ROOT}/include
)

find_library(RdKafka_LIBRARY
    NAMES ${RdKafka_LIBNAME} rdkafka
    HINTS ${RdKafka_ROOT}/lib ${RdKafka_ROOT}/lib64
)

message("RDKAFKA header path ${RdKafka_INCLUDE_DIR}")
message("RDKAFKA lib name ${RdKafka_LIBNAME}")
message("RDKAFKA lib: ${RdKafka_LIBRARY}")

include_directories(${RdKafka_INCLUDE_DIR})

# static linkage results in ~1Mb executable :)
add_executable(helloworld main.cpp)
target_link_libraries(
    helloworld
    ${RdKafka_LIBRARY}
)
