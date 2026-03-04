#include <connection.hpp>
#include <style.hpp>
#include <input.hpp>
#include <channels.hpp>
#include <stdexcept>
#include <print>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>

int connectServer(char* addr, char* port) {
    int sockfd{socket(AF_INET, SOCK_STREAM, 0)};
    addrinfo hints, *info, *inode;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;
    if (getaddrinfo(addr, port, &hints, &info) != 0) throw std::runtime_error("failed to getaddrinfo");
    for (inode = info; inode != nullptr; inode = inode->ai_next) {
        if (connect(sockfd, inode->ai_addr, inode->ai_addrlen) == 0) break;
    }
    if (inode == nullptr) throw std::runtime_error("failed to connect to server");
    freeaddrinfo(info);
    return sockfd;
}

void sendLoop(const int& sockfd) {
    std::string msg{};
    while (true) {
        std::getline(std::cin, msg);
        if (processInput(msg)) {
            if (send(sockfd, (msg + "\r\n").c_str(), strlen((msg + "\r\n").c_str()), 0) <= 0) return;
            std::vector<std::string> msgv = parseCmd(msg);
            
        }
        printLog(current_channel);
    }
}

void recvLoop(const int& sockfd) {
    std::string msg{};
    while (true) {
        while (msg.size() < 2 || !msg.contains("\r\n")) {
            char recv_buff[128];
            if (recv(sockfd, recv_buff, sizeof(recv_buff) - 1, 0) <= 0) return;
            msg.append(recv_buff);
            memset(recv_buff, 0, sizeof(recv_buff));
        }
        size_t first_crlf{msg.find("\r\n")};
        while (first_crlf != msg.npos) {
            MsgIRC imsg{msg.substr(0, first_crlf + 2)};
            logMsg(imsg);
            printLog(current_channel);
            msg = msg.substr(first_crlf + 2);
            first_crlf = msg.find("\r\n");
        }
    }
}
