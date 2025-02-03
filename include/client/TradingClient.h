//
// Created by Zhiyang Lu on 03/02/2025.
//

#ifndef TRADING_SYSTEM_TRADINGCLIENT_H
#define TRADING_SYSTEM_TRADINGCLIENT_H

#include "../common/Global.h"

class TradingClient {
private:
    static bool tradingThread(int id);

public:
    bool initiate();
};


#endif //TRADING_SYSTEM_TRADINGCLIENT_H
