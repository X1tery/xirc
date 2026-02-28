#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

extern const std::unordered_map<std::string, std::string> COMMANDS;
extern const std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> CLIENT_CMDS;

std::vector<std::string> parseCmd(std::string cmd);
bool processInput(std::string& cmd);
void cdCmd(std::vector<std::string> cmd);