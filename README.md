This is just a personal project and is stored on GitHub (don't want to pay for private repo).
Contribution is unecessary, but you can if you wish.

Description:

* Notifies of events according to time (weekday, hour, minute)
* Events info (weekday, hour, minute, warn/start/end times, notification titles/msg) are stored in a config file
* Syntax checking of config file
* Event loop mode and "now" mode (check for active events; if there are none notify nearest event)

Event syntax: (Weekday) (Warn Time) (Start Time) (End Time) (Warn Title) (Warn Msg) (Start Title) (Start Msg) (End Title) (End Msg) ("now" mode about to start title) ("now" mode about to start msg) ("now" mode in progress title) ("now" mode in progress msg)

Each event is seperated by one newline.

Command line arguments syntax: <b>exec_file_name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mode ("loop" or "now")&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;config_file_path<b>

Example of config file (note: '+' is space All: All days, Weekday: All weekdays, Weekend: Only weekends; events can overlap):

All 10:10 10:20 11:00 Event+Warning Event+will+start+in+10+minutes. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
Weekday 13:25 13:30 14:45 Event+Warning Event+will+start+soon. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
Weekend 06:50 07:00 07:05 Event+Warning Event+will+start+soon. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
Monday 12:10 12:20 12:30 Event+Warning Event+will+start+soon. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
Saturday 19:10 19:25 20:00 Event+Warning Event+will+start+soon. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
Saturday 19:00 19:15 20:05 Event+Warning Event+will+start+soon. Event+Started Event+has+started. Event+Ended Event+has+ended Event+About+to+Start Event+will+start+shortly. Event+in+Progress Event+is+in+progress.
