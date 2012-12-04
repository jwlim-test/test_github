#include <iostream>
#include <string>
#include <map>


class WorldClock {
  public:
    WorldClock() : time_difference_(0) {}
    WorldClock(int hour, int minute, int second) : hour_(hour), minute_(minute), second_(second) {}
    void Tick(int seconds = 1);
    bool SetTime(int hour, int minute, int second);
    static void AddTimezoneInfo(const std::string& city, int diff);
    bool SetTimezone(const std::string& timezone);
    int hour() const { return hour_; }
    int minute() const { return minute_; }
    int second() const { return second_; }
    int time_difference() const { return time_difference_; }
  private:
    int hour_;
    int minute_;
    int second_; 
    int time_difference_;
    static std::map<std::string, int> timezone_;
};
struct InvalidTimeException {
  std::string input_time;
  InvalidTimeException(const std::string& str) : input_time(str) {}
};
std::ostream& operator<<(std::ostream& os, const WorldClock& c);
std::istream& operator>>(std::istream& is, WorldClock& c);
