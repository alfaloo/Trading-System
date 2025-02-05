//
// Created by Zhiyang Lu on 05/02/2025.
//

#ifndef TRADING_SYSTEM_TRADE_H
#define TRADING_SYSTEM_TRADE_H

#include <string>

enum class Status {
    Completed,
    Pending,
};

struct Trade {
    const std::string uuid;
    const std::string ticker;
    const Status status;
    const double price;
    const double quantity;

    Trade(const std::string& uuid,
          const std::string& ticker,
          const Status status,
          const double price,
          const double quantity) :
            uuid(uuid),
            ticker(ticker),
            status(status),
            price(price),
            quantity(quantity) {}
};

#endif //TRADING_SYSTEM_TRADE_H
