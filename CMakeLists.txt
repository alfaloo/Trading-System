cmake_minimum_required(VERSION 3.30)
project(Trading_System)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE SERVER "src/server/*.cpp")
file(GLOB_RECURSE CLIENT "src/client/*.cpp")
file(GLOB_RECURSE COMMON "src/common/*.cpp")

add_executable(startServer ${SERVER} ${COMMON})
add_executable(startClient ${CLIENT} ${COMMON})
add_executable(test tests/test.cpp src/server/BoundedBuffer.cpp ${COMMON})
