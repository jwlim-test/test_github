#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
class WorldClock {
 public:
  WorldClock();
  WorldClock(int hour, int minute, int second);
  void Tick(int seconds = 1);
  bool SetTime(int hour, int minute, int second);
  static void AddTimezoneInfo(const std::string& city, int diff);
  bool SetTimezone(const std::string& timezone);
  int hour() const;
  int minute() const;
  int second() const;
  int time_difference() const { return time_difference_; }
 private:
	int time;
  int time_difference_;
  static std::map<std::string, int> timezone_;
};
struct InvalidTimeException {
  string input_time;
  InvalidTimeException(const std::string& str) : input_time(str) {}
};
ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);
