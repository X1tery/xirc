#pragma once
#include <style.hpp>
#include <unordered_map>
#include <deque>
#include <string>

extern std::unordered_map<std::string, std::deque<MsgIRC>> msg_log;
extern std::string current_channel;
extern const unsigned int MAX_LOG_SIZE;
extern const unsigned int SRC_PADDING;
extern std::string NICK;

void printLog(std::string channel);
void logMsg(MsgIRC msg);