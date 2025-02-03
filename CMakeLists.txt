cmake_minimum_required(VERSION 3.30)
project(Trading_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Trading_System src/server/ExchangeServer.cpp)
