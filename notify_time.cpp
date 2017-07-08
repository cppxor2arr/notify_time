#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <regex>
#include <array>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>

#include "notify_time.hpp"
#include "event.hpp"
#include "event_size.hpp"

void load_conf(std::vector<event_t>& events, const std::string& path)
{
    std::ifstream times{path};
    if (!times) throw std::pair<std::string, std::string>{"Error", "No such file or directory."};
    std::stringstream file; file << times.rdbuf();
    const std::regex conf{"((All|Weekday|Weekend|Sunday|Monday|Tuesday|Wednesday|Thursday|Friday|Saturday)\\s+(((([0-1][0-9])|(2[0-3]))\\:([0-5][0-9]))\\s+){3}([[:graph:]]+\\s+){9}[[:graph:]]+\\n)*"};
    if (!std::regex_match(file.str(), conf)) throw std::pair<std::string, std::string>{"Error", "Config file in incorrect format."};
    std::string str;
    while (std::getline(file, str))
    {
        std::istringstream stream{str};
        std::array<std::string, event_constant::size> event;
        for (std::string& s : event) stream >> s;
        if (event[0] == "All")
        {
            for (const std::string& s : time_constant::days)
            {
                event[0] = s; events.push_back(event);
            }
            continue;
        }
        else if (event[0] == "Weekday")
        {
            for (decltype(time_constant::days)::const_iterator it{time_constant::days.cbegin() + 1}; it != time_constant::days.cend() - 1; ++it)
            {
                event[0] = *it; events.push_back(event);
            }
            continue;
        }
        else if (event[0] == "Weekend")
        {
            event[0] = time_constant::days.front(); events.push_back(event);
            event[0] = time_constant::days.back(); events.push_back(event);
            continue;
        }
        events.push_back(event);
    }
    std::sort(events.begin(), events.end());
}

void event_loop(const std::vector<event_t>& events, const bool loop)
{
    if (loop) send_notif("Event Loop", "Event loop has started.");
    bool active{false};
    do
    { 
        unsigned time{current_time()};
        bool found{false};

        for (unsigned short n{0}; n!= 2; ++n)
        {
            for (const event_t& event : events)
            {
                if (loop)
                {
                    if      (time == event.time(time_constant::warn_time))
                        send_notif(event, time_constant::warn_notif);
                    else if (time == event.time(time_constant::start_time))
                        send_notif(event, time_constant::start_notif);
                    else if (time == event.time(time_constant::end_time))
                        send_notif(event, time_constant::end_notif);
                }
                else
                {
                    if      (time >= event.time(time_constant::warn_time) && time < event.time(time_constant::start_time))
                    {
                        send_notif(event, time_constant::about_to_start_notif);
                        send_notif("Time Remaining", time_diff(event.time(time_constant::start_time), time) + " left.");
                        active = true;
                    }
                    else if (time >= event.time(time_constant::start_time) && time < event.time(time_constant::end_time))
                    {
                        send_notif(event, time_constant::in_progress_notif);
                        send_notif("Time Remaining", time_diff(event.time(time_constant::end_time), time) + " to go.");
                        active = true;
                    }
                    else if (event.time(time_constant::warn_time) > time && !active)
                    {
                        send_notif("No Active Events", "Nearest event is in " + time_diff(event.time(time_constant::warn_time), time) + "\nNearest event preview:");
                        send_notif(event, time_constant::warn_notif);
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
            time = 0;
        }
        if (loop) pause(1000);
    }
    while (loop);
}

unsigned current_time()
{
    std::time_t t{std::time(nullptr)};
    struct tm *now{std::localtime(&t)};
    return now->tm_wday * 86400 + now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec;
}

std::string time_diff(const unsigned time1, const unsigned time2)
{
    const unsigned diff{time1 - time2};
    std::string diff_str;
    if (diff / 86400             != 0) diff_str += std::to_string(diff / 86400)             + " day(s) ";
    if (diff % 86400 / 3600      != 0) diff_str += std::to_string(diff % 86400 / 3600)      + " hour(s) ";
    if (diff % 86400 % 3600 / 60 != 0) diff_str += std::to_string(diff % 86400 % 3600 / 60) + " minute(s) ";
    if (diff % 60                != 0) diff_str += std::to_string(diff % 60)                + " second(s)";
    return diff_str;
}

inline void pause(const unsigned milli)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}
