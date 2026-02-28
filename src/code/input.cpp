#include <input.hpp>
#include <channels.hpp>
#include <unordered_map>
#include <cwctype>

const std::unordered_map<std::string, std::string> COMMANDS {
    {"/cd", "CD"},
    {"/admin", "ADMIN"},
    {"/away", "AWAY"},
    {"/cnotice", "CNOTICE"},
    {"/cmsg", "CPRIVMSG"},
    {"/connect", "CONNECT"},
    {"/die", "DIE"},
    {"/encap", "ENCAP"},
    {"/error", "ERROR"},
    {"/help", "HELP"},
    {"/info", "INFO"},
    {"/invite", "INVITE"},
    {"/ison", "ISON"},
    {"/join", "JOIN"},
    {"/kick", "KICK"},
    {"/kill", "KILL"},
    {"/knock", "KNOCK"},
    {"/links", "LINKS"},
    {"/list", "LIST"},
    {"/lusers", "LUSERS"},
    {"/mode", "MODE"},
    {"/motd", "MOTD"},
    {"/names", "NAMES"},
    {"/nick", "NICK"},
    {"/notice", "NOTICE"},
    {"/oper", "OPER"},
    {"/part", "PART"},
    {"/pass", "PASS"},
    {"/ping", "PING"},
    {"/pong", "PONG"},
    {"/msg", "PRIVMSG"},
    {"/quit", "QUIT"},
    {"/rehash", "REHASH"},
    {"/rules", "RULES"},
    {"/server", "SERVER"},
    {"/service", "SERVICE"},
    {"/servlist", "SERVLIST"},
    {"/squery", "SQUERY"},
    {"/squit", "SQUIT"},
    {"/setname", "SETNAME"},
    {"/silence", "SILENCE"},
    {"/stats", "STATS"},
    {"/summon", "SUMMON"},
    {"/time", "TIME"},
    {"/topic", "TOPIC"},
    {"/trace", "TRACE"},
    {"/user", "USER"},
    {"/userhost", "USERHOST"},
    {"/userip", "USERIP"},
    {"/users", "USERS"},
    {"/version", "VERSION"},
    {"/wallops", "WALLOPS"},
    {"/watch", "WATCH"},
    {"/who", "WHO"},
    {"/whois", "WHOIS"},
    {"/whowas", "WHOWAS"},
};

const std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> CLIENT_CMDS {
    {"CD", cdCmd}
};

std::vector<std::string> parseCmd(std::string cmd) {
    std::vector<std::string> cmdv{};
    std::string temp{};
    for (char c : cmd) {
        if (std::iswspace(c)) {
            cmdv.push_back(temp);
            temp.erase();
        }
        else
            temp.push_back(c);
    }
    if (temp.empty()) return cmdv;
    cmdv.push_back(temp);
    return cmdv;
}

bool processInput(std::string& cmd) {
    std::vector<std::string> cmdv = parseCmd(cmd);
    if (cmdv.size() < 1) return false;
    if (COMMANDS.contains(cmdv[0])) {
        if (cmd.size() > cmdv[0].size() + 1)
            cmd = COMMANDS.at(cmdv[0]) + cmd.substr(cmdv[0].size());
        else
            cmd = COMMANDS.at(cmdv[0]);
        if (CLIENT_CMDS.contains(COMMANDS.at(cmdv[0]))) {
            CLIENT_CMDS.at(COMMANDS.at(cmdv[0]))(cmdv);
            return false;
        }
    }
    return true;
}

void cdCmd(std::vector<std::string> cmd) {
    if (cmd.size() != 2) return;
    current_channel = cmd[1];
}