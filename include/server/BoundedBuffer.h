//
// Created by Zhiyang Lu on 04/02/2025.
//

#ifndef TRADING_SYSTEM_BOUNDEDBUFFER_H
#define TRADING_SYSTEM_BOUNDEDBUFFER_H

#include "../common/Global.h"

template <typename Item>
class BoundedBuffer {
private:
    Item buffer[BUFFER_SIZE];
    int start = 0;
    int size = 0;
    std::mutex mtx;
    std::condition_variable canProduce;
    std::condition_variable canConsume;

public:
    bool produce(const Item& item) {
        std::unique_lock<std::mutex> lock(mtx);
        canProduce.wait(lock, [&size = size] {
            return size < BUFFER_SIZE;
        });

        int index = (start + size) % BUFFER_SIZE;
        buffer[index] = std::move(item);
        size++;

        lock.unlock();
        canConsume.notify_one();

        return true;
    }

    Item consume() {
        std::unique_lock<std::mutex> lock(mtx);
        canConsume.wait(lock, [&size = size] {
            return size > 0;
        });

        Item result = std::move(buffer[start]);
        start = (start + 1) % BUFFER_SIZE;
        size--;

        lock.unlock();
        canProduce.notify_one();

        return result;
    }

    void printBuffer() {
        std::cout << "Size: " << size << "\n";
        std::cout << "Start: " << start << "\n";
        std::cout << "[";
        for (Item& item : buffer) {
            std::cout << item << ", ";
        }
        std::cout << "]";
    }

};

#endif //TRADING_SYSTEM_BOUNDEDBUFFER_H
