#include <style.hpp>
#include <vector>
#include <format>
#include <print>

MsgIRC::MsgIRC(std::string msg) {
    std::vector<std::string> msgv{parseMsg(msg)};
    size_t i{0};
    while (i < msgv.size() && msgv[i][0] == '@') tags.push_back(msgv[i++]);
    if (i != msgv.size() - 1 && msgv[i][0] == ':') for (std::string s : parseUser(msgv[i++])) src.push_back(s);
    if (i < msgv.size()) cmd = msgv[i++];
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