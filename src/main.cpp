#include <connection.hpp>
#include <channels.hpp>
#include <print>
#include <thread>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::println("{} [ADDRESS] [PORT]", argv[0]);
        return 0;
    }
    current_channel = "system";
    int sockfd{connectServer(argv[1], argv[2])};
    std::thread sl(sendLoop, sockfd);
    std::thread rl(recvLoop, sockfd);
    rl.join();
    close(sockfd);
    sl.join();
    return 0;
}