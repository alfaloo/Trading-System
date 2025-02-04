//
// Created by Zhiyang Lu on 03/02/2025.
//

#include "../../include/server/ClientHandler.h"

bool ClientHandler::handleClient(int clientSocket, sockaddr_in clientAddress, int id) {
    printServer("Client ", id, " connected: ", inet_ntoa(clientAddress.sin_addr), ":", ntohs(clientAddress.sin_port));

    char buffer[BUFFER_SIZE];

    while(true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytesRecieved = recv(clientSocket, buffer, BUFFER_SIZE, 0);

        if (bytesRecieved == -1) {
            printServer("Error receiving data from client ", id);
            break;
        } else if (bytesRecieved == 0) {
            printServer("Client ", id, " disconnected");
            break;
        } else {
            std::istringstream iss(buffer, bytesRecieved);
            std::string message;
            while (std::getline(iss, message, '\n')) {
                printServer("Recieved from client ", id , ": ", message);
            }
        }
    }

    close(clientSocket);
    return true;
}

bool ClientHandler::initiate() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printError("ClientHandler failed to connect");
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        printError("ClientHandler failed to bind socket");
        close(serverSocket);
        return false;
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        printError("ClientHandler failed to listen on socket");
        close(serverSocket);
        return false;
    }

    printServer("ClientHandler is listening on port ", PORT, "...");

    std::vector<std::thread> threads;
    int id = 0;

    while (true) {
        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            printError("ClientHandler failed to accept connection");
            continue;
        }

        if (threads.size() >= MAX_CLIENTS) {
            printError("ClientHandler has reached maximum number of clients");
            close(clientSocket);
            continue;
        }

        threads.emplace_back(ClientHandler::handleClient, clientSocket, clientAddress, id++);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    close(serverSocket);

    return true;
}
