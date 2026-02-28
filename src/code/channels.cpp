#include <channels.hpp>
#include <style.hpp>
#include <print>

std::unordered_map<std::string, std::deque<MsgIRC>> msg_log{};
std::string current_channel{};
const unsigned int MAX_LOG_SIZE{55};
const unsigned int SRC_PADDING{25};

void printLog(std::string channel) {
    std::print("\r\033[1J");
    for (MsgIRC msg : msg_log[current_channel]) {
        std::print("\033[1F");
        if (msg.cmd == "PRIVMSG" || msg.cmd == "CPRIVMSG") {
            std::print("{} | ", addPadding(msg.src[0], SRC_PADDING));
            for (size_t i = 1; i < msg.params.size(); i++) {
                std::print("{} ", msg.params[i]);
            }
        } else {
            std::print("[CMD]{} | [{}] ", addPadding(msg.src[0], SRC_PADDING - 5), msg.cmd);
            for (size_t i = 1; i < msg.params.size(); i++) {
                std::print("{} ", msg.params[i]);
            }
        }
    }
    std::println("\033[{}E", msg_log[current_channel].size() - 1);
}

void logMsg(MsgIRC msg) {
    std::string channel{msg.src.size() == 1 ? "system" : msg.params[0]};
    msg_log[channel].push_front(msg);
    if (msg_log[channel].size() > MAX_LOG_SIZE)
        msg_log[channel].pop_back();
}