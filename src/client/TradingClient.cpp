//
// Created by Zhiyang Lu on 03/02/2025.
//

#include "../../include/client/TradingClient.h"

bool TradingClient::tradingThread(int id) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        printClient("Client ", id, ": failed to create socket");
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddress.sin_addr) <= 0) {
        printError("Client ", id, ": Invalid server address");
        close(clientSocket);
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        printError("Client ", id, ": Failed to connect to server");
        close(clientSocket);
        return false;
    }

    printClient("Client ", id, ": Connected to server");

    char buffer[BUFFER_SIZE];

    for (int i = 0; i < 100; i++) {
        memset(buffer, 0, BUFFER_SIZE);
        snprintf(buffer, BUFFER_SIZE, "Message %d\n", i);

        ssize_t bytesSent = send(clientSocket, buffer, strlen(buffer), 0);

        if (bytesSent <= 0) {
            printClient("Client: ", id, ": Failed to send data");
            break;
        } else {
            printClient("Client: ", id, ": Sent ", buffer);
        }
    }

    close(clientSocket);
    printClient("Client ", id, ": Disconnected from server");

    return true;
}

bool TradingClient::initiate() {
    std::vector<std::thread> threads;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        threads.emplace_back(TradingClient::tradingThread, i);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return true;
}