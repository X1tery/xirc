#pragma once

int connectServer(char* addr, char* port);
void sendLoop(const int& sockfd);
void recvLoop(const int& sockfd);
