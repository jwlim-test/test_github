#include <map>
#include <string>
#include <iostream>

using namespace std;
class WorldClock {
  public:
  WorldClock();
  WorldClock(int hour, int minute, int second);
  void Tick(int seconds = 1);
  // 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
  bool SetTime(int hour, int minute, int second);
  void AddTimezoneInfo(const string& city, int diff);
  bool SetTimezone(const string& timezone);
  int hour() const;
  int minute() const;
  int second() const;
  int time_difference() const { return time_difference_; }
  
  private:
  // 여기에 시각 관련 멤버 변수 정의. (GMT 시간을 사용)
  int hour_,minute_,second_;
  int time_difference_;
  static map<string, int> timezone_;
};

struct InvalidTimeException {
  string input_time;
  InvalidTimeException(const string& str) : input_time(str) {}
};

ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c); // hh:mm:ss 로 입력받음.

