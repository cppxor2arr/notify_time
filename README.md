This is just a personal project and is stored on GitHub (don't want to pay for private repo).
Contribution is unecessary, but you can if you wish. If you want to use this project, then the package `ruby-notify` is required (Linux).

Description:

* Notifies of events according to time (weekday, hour, minute)
* Events info (weekday, hour, minute, warn/start/end times, notification titles/msg) are stored in a config file
* Syntax checking of config file
* Event loop mode and "now" mode (check for active events; if there are none notify nearest event)

Event syntax: `(Weekday)   (Warn Time)   (Start Time)   (End Time)   (Warn Title)   (Warn Msg)   (Start Title)   (Start Msg)   (End Title)   (End Msg)   ("now" mode about to start title)   ("now" mode about to start msg)   ("now" mode in progress title)   ("now" mode in progress msg)`

Each event is seperated by one newline.

Command line arguments syntax: `notify_time     mode("loop" or "now")     config_file_path`

Config file rules:

* '+' represents a space
* "All" means all days, "Weekday" means weekdays only, "weekends" means weekends only
* Each event must be seperated by newline
* Config file must have newline at the end
* The beginning of the file must start with an event (can't start with whitespace)

Example of config file: [Config file](http://s000.tinyupload.com/index.php?file_id=06137321611538773501)