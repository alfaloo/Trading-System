//
// Created by Zhiyang Lu on 03/02/2025.
//

#ifndef TRADING_SYSTEM_CLIENTHANDLER_H
#define TRADING_SYSTEM_CLIENTHANDLER_H

#include <arpa/inet.h>
#include <sstream>
#include <thread>
#include <unistd.h>

#include "../common/Global.h"
#include "../common/Utility.h"

class ClientHandler {
private:
    static bool handleClient(int clientSocket, sockaddr_in clientAddress, int id);

public:
    bool initiate();

};


#endif //TRADING_SYSTEM_CLIENTHANDLER_H
