cmake_minimum_required(VERSION 3.30)
project(Trading_System)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SERVER "src/server/*.cpp")
file(GLOB_RECURSE CLIENT "src/client/*.cpp")
file(GLOB_RECURSE COMMON "src/common/*.cpp")

add_executable(startServer src/server/ServerStart.cpp ${SERVER} ${COMMON})
add_executable(startClient src/client/ClientStart.cpp ${CLIENT} ${COMMON})
