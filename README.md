This is just a personal project and is stored on GitHub (don't want to pay for private repo).
Contribution is unecessary, but you can if you wish.

Description:

* Notifies of events according to time (weekday, hour, minute)
* Events info (weekday, hour, minute, warn/start/end times, notification titles/msg) are stored in a config file
* Syntax checking of config file
* Event loop mode and "now" mode (check for active events; if there are none notify nearest event)

Event syntax: (Weekday) (Warn Time) (Start Time) (End Time) (Warn Title) (Warn Msg) (Start Title) (Start Msg) (End Title) (End Msg) ("now" mode about to start title) ("now" mode about to start msg) ("now" mode in progress title) ("now" mode in progress msg)

Each event is seperated by one newline.

Command line arguments syntax: exec_file_name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mode ("loop" or "now")&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;config_file_path
