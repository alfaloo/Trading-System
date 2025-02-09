//
// Created by Zhiyang Lu on 09/02/2025.
//

#include "../../include/server/OrderBook.h"

bool OrderBook::processOrder() {
    std::shared_ptr<Order> order = boundedBuffer.consume();

    if (order->side == Side::Cancel) {
        if (catelog.count(order->uuid)) {
            catelog[order->uuid]->cancelled = true;
            catelog.erase(order->uuid);
            Trade trade(catelog[order->uuid], Status::Completed);
            replyClient(order->clientSocket, trade);
            return true;
        } else {
            order->cancelled = true;
            catelog[order->uuid] = order;
            return true;
        }
    } else {
        if (catelog.count(order->uuid) && catelog[order->uuid]->cancelled) {
            Trade trade(order, Status::Completed);
            catelog.erase(order->uuid);
            replyClient(order->clientSocket, trade);
            return true;
        }
    }

    if (order->side == Side::Buy) {
        std::map<double, std::deque<std::shared_ptr<Order>>>& sellOrders = sellSide[order->ticker];
        while (order->quantity && sellOrders.size()) {
            std::pair<const double, std::deque<std::shared_ptr<Order>>>& lowest = *(sellOrders.begin());
            if (lowest.first > order->price) {
                break;
            }

            while (order->quantity && lowest.second.size()) {
                if (!lowest.second.front()->cancelled) {
                    if (order->quantity >= lowest.second.front()->quantity) {
                        Trade sellTrade(lowest.second.front(), Status::Completed);
                        Trade buyTrade(order->uuid, order->ticker, Side::Buy, lowest.first, lowest.second.front()->quantity, Status::Completed);
                        order->quantity -= lowest.second.front()->quantity;
                        replyClient(lowest.second.front()->clientSocket, sellTrade);
                        replyClient(order->clientSocket, buyTrade);
                    } else {
                        Trade sellTrade(lowest.second.front()->uuid, order->ticker, Side::Sell, lowest.first, order->quantity, Status::Completed);
                        Trade buyTrade(order->uuid, order->ticker, Side::Buy, lowest.first, order->quantity, Status::Completed);
                        lowest.second.front()->quantity -= order->quantity;
                        order->quantity = 0;
                        replyClient(lowest.second.front()->clientSocket, sellTrade);
                        replyClient(order->clientSocket, buyTrade);
                    }
                }

                if (catelog.count(lowest.second.front()->uuid)) {
                    catelog.erase(lowest.second.front()->uuid);
                }

                lowest.second.pop_front();
            }

            if (!lowest.second.size()) {
                sellOrders.erase(lowest.first);
            }
        }

        if (order->quantity) {
            catelog[order->uuid] = order;
            buySide[order->ticker][order->price].push_back(order);
            Trade trade(order, Status::Pending);
            replyClient(order->clientSocket, trade);
        }
    } else if (order->side == Side::Sell) {
        std::map<double, std::deque<std::shared_ptr<Order>>>& buyOrders = buySide[order->ticker];
        while (order->quantity && buyOrders.size()) {
            std::pair<const double, std::deque<std::shared_ptr<Order>>>& highest = *(buyOrders.rbegin());
            if (highest.first < order->price) {
                break;
            }

            while (order->quantity && highest.second.size()) {
                if (!highest.second.front()->cancelled) {
                    if (order->quantity >= highest.second.front()->quantity) {
                        Trade buyTrade(highest.second.front(), Status::Completed);
                        Trade sellTrade(order->uuid, order->ticker, Side::Sell, highest.first, highest.second.front()->quantity, Status::Completed);
                        order->quantity -= highest.second.front()->quantity;
                        replyClient(highest.second.front()->clientSocket, buyTrade);
                        replyClient(order->clientSocket, sellTrade);
                    } else {
                        Trade buyTrade(highest.second.front()->uuid, order->ticker, Side::Buy, highest.first, order->quantity, Status::Completed);
                        Trade sellTrade(order->uuid, order->ticker, Side::Sell, highest.first, order->quantity, Status::Completed);
                        highest.second.front()->quantity -= order->quantity;
                        order->quantity = 0;
                        replyClient(highest.second.front()->clientSocket, buyTrade);
                        replyClient(order->clientSocket, sellTrade);
                    }
                }

                if (catelog.count(highest.second.front()->uuid)) {
                    catelog.erase(highest.second.front()->uuid);
                }

                highest.second.pop_front();
            }

            if (!highest.second.size()) {
                buyOrders.erase(highest.first);
            }
        }

        if (order->quantity) {
            catelog[order->uuid] = order;
            sellSide[order->ticker][order->price].push_back(order);
            Trade trade(order, Status::Pending);
            replyClient(order->clientSocket, trade);
        }
    }
}

bool OrderBook::replyClient(int clientSocket, Trade trade) {
    std::string response = "";
    response += trade.uuid + ",";
    response += trade.ticker + ",";
    response += std::to_string(static_cast<int>(trade.side)) + ",";
    response += std::to_string(trade.price) + ",";
    response += std::to_string(trade.quantity) + ",";
    response += std::to_string(static_cast<int>(trade.status)) + "\n";
    const char* responseCstr = response.c_str();
    send(clientSocket, responseCstr, strlen(responseCstr), 0);
}