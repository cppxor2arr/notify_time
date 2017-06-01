#include "pstream.hpp"
#include <string>
#include <vector>
#include <utility>

#include "notify_time.hpp"
#include "event.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3) return -1;
    {
        redi::ipstream proc{"pgrep -c " + static_cast<std::string>(argv[0]), redi::pstreams::pstdout};
        std::string output; std::getline(proc.out(), output);
        if (std::stoi(output) > 1 && static_cast<std::string>(argv[1]) == "loop") return 0;
    }
    std::string mode{argv[1]}, path{argv[2]};
    bool loop{false};
    {
        if (mode == "loop") loop = true;
        else if (mode == "now") loop = false;
        else return -1;
    }

    std::vector<event_t> events;
    try { load_conf(events, path); }
    catch (const std::pair<std::string, std::string> notif)
    {
        send_notif(notif.first, notif.second);
        return -1;
    }

    event_loop(events, loop);

    return 0;
}
