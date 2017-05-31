all:
	g++ -Wall -Wextra -pedantic-errors -std=c++14 -O2 -Os -s main.cpp notify_time.cpp event.cpp -o notify_time
