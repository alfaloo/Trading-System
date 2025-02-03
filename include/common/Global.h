//
// Created by Zhiyang Lu on 03/02/2025.
//

#ifndef TRADING_SYSTEM_GLOBALVARIABLES_H
#define TRADING_SYSTEM_GLOBALVARIABLES_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;
constexpr int MAX_CLIENTS = 4;

std::mutex coutMutex;
std::mutex cerrMutex;

template <typename... Args>
void print(Args&&... args);

template <typename... Args>
void printServer(Args&&... args);

template <typename... Args>
void printServer(Args&&... args);

template <typename... Args>
void printError(Args&&... args);

#endif //TRADING_SYSTEM_GLOBALVARIABLES_H
