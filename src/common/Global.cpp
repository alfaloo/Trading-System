//
// Created by Zhiyang Lu on 03/02/2025.
//

#include "../../include/common/Global.h"

template <typename... Args>
void print(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << (... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printServer(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "[SERVER] " << (... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printClient(Args&&... args) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "[CLIENT] " << (... << args) << "\n";  // Fold expression (C++17+)
}

template <typename... Args>
void printError(Args&&... args) {
    std::lock_guard<std::mutex> lock(cerrMutex);
    std::cerr << "[ERROR] " << (... << args) << "\n";  // Fold expression (C++17+)
}