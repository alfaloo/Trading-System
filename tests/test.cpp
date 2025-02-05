//
// Created by Zhiyang Lu on 04/02/2025.
//

#include <chrono>
#include <thread>

#include "../include/server/BoundedBuffer.h"

void produceTest(BoundedBuffer<int>& boundedBuffer, int val, int count) {
    for (int i = 0; i < count; i++) {
        boundedBuffer.produce(val);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
};

void consumeTest(BoundedBuffer<int>& boundedBuffer, int count) {
    for (int i = 0; i < count; i++) {
        boundedBuffer.consume();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
};

int main() {
    BoundedBuffer<int> boundedBuffer;

    std::thread t1(produceTest, std::ref(boundedBuffer), 1, 700);
    std::thread t2(produceTest, std::ref(boundedBuffer), 2, 700);
    std::thread t3(consumeTest, std::ref(boundedBuffer), 200);
    std::thread t4(consumeTest, std::ref(boundedBuffer), 200);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    boundedBuffer.printBuffer();

    return 0;
}