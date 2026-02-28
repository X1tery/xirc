#include <style.hpp>
#include <vector>
#include <format>
#include <print>

MsgIRC::MsgIRC(std::string msg) {
    std::vector<std::string> msgv{parseMsg(msg)};
    size_t i{0};
    while (i < msgv.size() && msgv[i][0] == '@') tags.push_back(msgv[i++]);
    if (i < msgv.size() - 1 && msgv[i][0] == ':') for (std::string s : parseUser(msgv[i++])) src.push_back(s);
    else src.push_back("");
    if (i < msgv.size()) cmd = msgv[i++];
    else cmd = "";
    while (i < msgv.size()) params.push_back(msgv[i++]);
}

std::vector<std::string> parseMsg(std::string msg) {
    std::vector<std::string> result{};
    std::string temp{};
    for (size_t i = 0; i < msg.size() - 2; i++) {
        if (i != 0 && msg[i] == ':')
            while (i < msg.size() - 3) temp.push_back(msg[++i]);
        else {
            while (i < msg.size() - 2 && msg[i] != ' ') {
                temp.push_back(msg[i++]);
            }
        }
        result.push_back(temp);
        temp.clear();
    }
    return result;
}

std::vector<std::string> parseUser(std::string src) {
    src.erase(src.begin());
    if (!src.contains("!") || !src.contains("@")) return {src};
    std::vector<std::string> result{{}, {}, {}};
    size_t i = 0;
    while (src[i] != '!') result[0].push_back(src[i++]);
    while (src[i] != '@') result[1].push_back(src[i++]);
    while (i < src.size()) result[2].push_back(src[i++]);
    return result;
}

std::string addPadding(std::string s, size_t n) {
    long d = n - s.size();
    if (d > 0)
        return s.insert(0, d, ' ');
    else
        return s.substr(0, n);
}

void printMsg(MsgIRC msg) {
    if (msg.cmd == "PRIVMSG") {
        std::println("{} | {}", addPadding(msg.src[0], 24), msg.params[1]);
    } else if (msg.src.size() != 1) {
        std::print("\033[2m[CMD]{} | {} ", addPadding(msg.src[0], 19), msg.cmd);
        for (std::string s : msg.params) std::print("{} ", s);
        std::println("\033[22m");
    } else {
        std::print("\033[2m{} | ", addPadding(msg.src[0], 24));
        for (std::string s : msg.params) std::print("{} ", s);
        std::println("\033[22m");
    }
}