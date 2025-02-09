//
// Created by Zhiyang Lu on 09/02/2025.
//

#ifndef TRADING_SYSTEM_ORDERBOOK_H
#define TRADING_SYSTEM_ORDERBOOK_H

#include <arpa/inet.h>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "BoundedBuffer.h"
#include "../common/Order.h"
#include "../common/Trade.h"

class OrderBook {
private:
    std::unordered_map<std::string, std::map<double, std::deque<std::shared_ptr<Order>>>> buySide;
    std::unordered_map<std::string, std::map<double, std::deque<std::shared_ptr<Order>>>> sellSide;
    std::unordered_map<std::string, std::shared_ptr<Order>> catelog;
    BoundedBuffer<std::shared_ptr<Order>>& boundedBuffer;


public:
    OrderBook (BoundedBuffer<std::shared_ptr<Order>>& boundedBuffer) :
    buySide(),
    sellSide(),
    catelog(),
    boundedBuffer(boundedBuffer) {}

    bool processOrder();
    bool replyClient(int clientSocket, Trade trade);

};


#endif //TRADING_SYSTEM_ORDERBOOK_H
