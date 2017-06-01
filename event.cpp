#include <string>
#include <algorithm>
#include <array>
#include <cstdlib>

#include "notify_time.hpp"
#include "event.hpp"
#include "event_size.hpp"

unsigned event_t::parse_time(const std::string& wday, const std::string& time) const // parse time in 24 hr format; e.g. 13:55, 07:08;
{
    std::string hr{time.substr(0, 2)}, min{time.substr(3, 2)}; // e.g. time: 14:35   hr == 14; min == 35;
    // get index of day and use in time calculation;
    return (std::find(time_constant::days.cbegin(), time_constant::days.cend(), wday) - time_constant::days.cbegin()) * 86400  + std::stoull(hr) * 3600 + std::stoull(min) * 60;
    // std::stoull ignores leading zero; e.g. time: 07:08   hr == 7; min == 8;
}

std::string event_t::unparse_notif(std::string title, std::string msg) const
{
    find_replace(title, "+", " ");
    find_replace(msg, "+", " ");
    return compose_notif(title, msg);
}

const std::string& event_t::find_replace(std::string& str, const std::string& search, const std::string& replace) const
{
    if (search == replace) return str;

    const std::string::size_type diff{replace.length() - search.length() + 1};

    for (std::string::size_type pos{0}; pos != std::string::npos; )
    {
        pos = str.find(search, pos);
        if (pos != std::string::npos)
        {
            str.replace(pos, search.length(), replace);
            pos += diff;
        }
    }
    return str;
}

std::string event_t::compose_notif(const std::string& title, const std::string& msg) const
{
    return "\"" + title + "\" \"" + msg + "\"";
}

std::string event_t::unparse_cmd(const std::string& notif) const
{
    return time_constant::cmd + " " + notif;
}

event_t::event_t(const std::array<std::string, event_constant::size>& event)
{
    load_event(event);
}

bool event_t::operator<(const event_t& event) const
{
    return warn_time < event.warn_time;
}

void event_t::load_event(const std::array<std::string, event_constant::size>& event)
{
    weekday              = event.front();

    warn_time            = parse_time(weekday, event[1]);
    start_time           = parse_time(weekday, event[2]);
    end_time             = parse_time(weekday, event[3]);

    warn_notif           = unparse_notif(event[4], event[5]);
    start_notif          = unparse_notif(event[6], event[7]);
    end_notif            = unparse_notif(event[8], event[9]);
    about_to_start_notif = unparse_notif(event[10], event[11]);
    in_progress_notif    = unparse_notif(event[12], event[13]);
}

void send_notif(const event_t& event, const unsigned short option)
{
    std::string notif;
    switch (option)
    {
        case time_constant::warn_notif:           notif = event.notif(time_constant::warn_notif);           break;
        case time_constant::start_notif:          notif = event.notif(time_constant::start_notif);          break;
        case time_constant::end_notif:            notif = event.notif(time_constant::end_notif);            break;
        case time_constant::about_to_start_notif: notif = event.notif(time_constant::about_to_start_notif); break;
        case time_constant::in_progress_notif:    notif = event.notif(time_constant::in_progress_notif);    break;
        default:                                  return;
    }
    std::system(event.unparse_cmd(notif).c_str());
}

void send_notif(const std::string& title, const std::string& msg)
{
    std::system(event_t().unparse_cmd("\"" + title + "\" \"" + msg + "\"").c_str());
}

void send_notif(const std::string &notif)
{
    std::system(event_t().unparse_cmd("\"" + notif + "\"").c_str());
}

unsigned event_t::time(const unsigned short option) const
{
    switch (option)
    {
        case time_constant::warn_time:  return warn_time;  break;
        case time_constant::start_time: return start_time; break;
        case time_constant::end_time:   return end_time;   break;
        default:                        return -1;
    }
}

std::string event_t::notif(const unsigned short option) const
{
    switch (option)
    {
        case time_constant::warn_notif:           return warn_notif;           break;
        case time_constant::start_notif:          return start_notif;          break;
        case time_constant::end_notif:            return end_notif;            break;
        case time_constant::about_to_start_notif: return about_to_start_notif; break;
        case time_constant::in_progress_notif:    return in_progress_notif;    break;
        default:                                  return "";
    }
}
