//
// Created by Zhiyang Lu on 03/02/2025.
//

#ifndef TRADING_SYSTEM_TRADINGCLIENT_H
#define TRADING_SYSTEM_TRADINGCLIENT_H

#include <arpa/inet.h>
#include <thread>
#include <unistd.h>

#include "../common/Global.h"
#include "../common/Utility.h"

class TradingClient {
private:
    static bool tradingThread(int id);

public:
    bool initiate();
};


#endif //TRADING_SYSTEM_TRADINGCLIENT_H
