//
// Created by Zhiyang Lu on 05/02/2025.
//

#ifndef TRADING_SYSTEM_ORDER_H
#define TRADING_SYSTEM_ORDER_H

#include <string>

enum class Side {
    Buy,
    Sell,
    Cancel,
};

struct Order {
    const std::string uuid;
    const std::string ticker;
    const Side side;
    const double price;
    double quantity;
    const int clientSocket;
    bool cancelled;

    Order(const std::string& uuid,
          const std::string& ticker,
          const Side side,
          const double price,
          const double quantity,
          const int clientSocket) :
          uuid(uuid),
          ticker(ticker),
          side(side),
          price(price),
          quantity(quantity),
          clientSocket(clientSocket),
          cancelled(false) {}
};


#endif //TRADING_SYSTEM_ORDER_H
