#pragma once
#include <vector>
#include <string>

struct MsgIRC {
    std::vector<std::string> tags;
    std::vector<std::string> src;
    std::string cmd;
    std::vector<std::string> params;
    MsgIRC(std::string msg);
};

std::vector<std::string> parseMsg(std::string msg);
std::vector<std::string> parseUser(std::string src);
std::string addPadding(std::string s, size_t n);
void printMsg(MsgIRC msg);