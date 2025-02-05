//
// Created by Zhiyang Lu on 05/02/2025.
//

#ifndef TRADING_SYSTEM_ORDER_H
#define TRADING_SYSTEM_ORDER_H

#include <string>

enum class Side {
    Buy,
    Sell,
};

struct Order {
    const std::string uuid;
    const std::string ticker;
    const Side side;
    const double price;
    const double quantity;

    Order(const std::string& uuid,
          const std::string& ticker,
          const Side side,
          const double price,
          const double quantity) :
          uuid(uuid),
          ticker(ticker),
          side(side),
          price(price),
          quantity(quantity) {}
};


#endif //TRADING_SYSTEM_ORDER_H
