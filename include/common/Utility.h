//
// Created by Zhiyang Lu on 05/02/2025.
//

#ifndef TRADING_SYSTEM_UTILITY_H
#define TRADING_SYSTEM_UTILITY_H

#include <iostream>
#include <mutex>

extern std::mutex coutMutex;
extern std::mutex cerrMutex;

template <typename... Args>
void print(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    (std::cout << ... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printServer(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "[SERVER] ";
    (std::cout << ... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printClient(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "[CLIENT] ";
    (std::cout << ... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printError(Args&&... args) {
    std::lock_guard<std::mutex> lock(cerrMutex);
    std::cerr << "[ERROR] ";
    (std::cerr << ... << args) << "\n";  // Fold expression (C++17+)
}

#endif //TRADING_SYSTEM_UTILITY_H
