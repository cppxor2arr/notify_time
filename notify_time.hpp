#ifndef NOTIFY_TIME_HPP
#define NOTIFY_TIME_HPP

#include <array>
#include <string>
#include <set>

#include "event.hpp"

namespace time_constant
{
    const std::array<std::string, 7> days       { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    constexpr unsigned short         warn_time  {0}, start_time {1}, end_time {2};
    constexpr unsigned short         warn_notif {0}, start_notif{1}, end_notif{2}, about_to_start_notif{3}, in_progress_notif{4};
    const std::string                cmd        {"notify-send"};
}

void load_conf(std::vector<event_t>&, const std::string&);
void event_loop(const std::vector<event_t>&, const bool);
unsigned long long current_time();
std::string time_diff(const unsigned long long, const unsigned long long);
void pause(const unsigned);

#endif
