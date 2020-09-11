cmake_minimum_required ( VERSION 2.8)
project(helloworld)

set(CMAKE_CXX_STANDARD 11)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Use as a standalone executable
add_executable(helloworld main.cpp)
target_link_libraries(
    helloworld
    rdkafka++
)

# Use as a shared library
add_library(testlib 
    SHARED
    testlib.cpp
)


# Use as a shared library
add_library(testkafka 
    SHARED
    kafkaproxy.cpp
)

LINK_DIRECTORIES(/usr/lib/)

target_link_libraries(
    testkafka
    rdkafka++
)

set(MYLIB_VERSION_MAJOR 0)
set(MYLIB_VERSION_MINOR 1)
set(MYLIB_VERSION_PATCH 1)
set(MYLIB_BUILD_NUMBER 1)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set_target_properties(testkafka
                      PROPERTIES VERSION ${MYLIB_VERSION_STRING}
                      SOVERSION ${MYLIB_VERSION_STRING})

