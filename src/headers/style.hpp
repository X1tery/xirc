#pragma once
#include <vector>
#include <string>
#include <unordered_set>

struct MsgIRC {
    std::vector<std::string> tags;
    std::vector<std::string> src;
    std::string cmd;
    std::vector<std::string> params;
    MsgIRC(std::string msg);
};

std::vector<std::string> parseMsg(std::string msg);
std::vector<std::string> parseUser(std::string src);