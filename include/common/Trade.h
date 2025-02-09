//
// Created by Zhiyang Lu on 05/02/2025.
//

#ifndef TRADING_SYSTEM_TRADE_H
#define TRADING_SYSTEM_TRADE_H

#include <string>

#include "Order.h"

enum class Status {
    Completed,
    Pending,
};

struct Trade {
    const std::string uuid;
    const std::string ticker;
    const Side side;
    const double price;
    const double quantity;
    const Status status;

    Trade(const std::string& uuid,
          const std::string& ticker,
          const Side side,
          const double price,
          const double quantity,
          const Status status) :
            uuid(uuid),
            ticker(ticker),
            side(side),
            price(price),
            quantity(quantity),
            status(status) {}

    Trade(Order order, Status status) :
            uuid(order.uuid),
            ticker(order.ticker),
            side(order.side),
            price(order.price),
            quantity(order.quantity),
            status(status) {}

    Trade(std::shared_ptr<Order> order, Status status) :
            uuid(order->uuid),
            ticker(order->ticker),
            side(order->side),
            price(order->price),
            quantity(order->quantity),
            status(status) {}
};

#endif //TRADING_SYSTEM_TRADE_H
