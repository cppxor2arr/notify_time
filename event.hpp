#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <array>
#include "event_size.hpp"

class event_t
{
    private:

        std::string weekday;
        unsigned warn_time{0}, start_time{0}, end_time{0};
        std::string warn_notif, start_notif, end_notif, about_to_start_notif, in_progress_notif;

        unsigned parse_time(const std::string&, const std::string&) const;
        std::string unparse_notif(std::string, std::string) const;
        const std::string& find_replace(std::string&, const std::string&,  const std::string&) const;
        std::string compose_notif(const std::string&, const std::string&) const;
        std::string unparse_cmd(const std::string&) const;

    public:

        event_t() = default;
        event_t(const std::array<std::string, event_constant::size>&);

        bool operator<(const event_t& event) const;

        void load_event(const std::array<std::string, event_constant::size>&);
        friend void send_notif(const event_t&, const unsigned short);
        friend void send_notif(const std::string&, const std::string&);
        friend void send_notif(const std::string&);

        unsigned time(const unsigned short) const;
        std::string notif(const unsigned short) const;
};

void send_notif(const event_t&, const unsigned short);
void send_notif(const std::string&, const std::string&);
void send_notif(const std::string&);

#endif
