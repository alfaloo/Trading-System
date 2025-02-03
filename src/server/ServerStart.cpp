//
// Created by Zhiyang Lu on 03/02/2025.
//

#ifndef TRADING_SYSTEM_SERVERSTART_H
#define TRADING_SYSTEM_SERVERSTART_H

#include "../../include/server/ClientHandler.h"

int main() {
    ClientHandler clientHandler;
    clientHandler.initiate();
}

#endif //TRADING_SYSTEM_SERVERSTART_H