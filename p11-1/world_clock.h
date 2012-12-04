#include <iostream>
#include <string>
#include <map>

using namespace std;

class WorldClock{
  public:
    WorldClock() : second_(0), time_difference_(0){};
    WorldClock(int hour, int minute, int second) :second_(hour*3600+minute*60+second)
                                                , time_difference_(0){};

    void Tick(int seconds=1);
    bool SetTime(int hour, int minute, int second);

    void AddTimezoneInfo(const string& city, int diff);

    bool SetTimezone(const string& timezone);

    int hour() const;
    int minute() const;
    int second() const;
    int time_difference() const {return time_difference_;}

  private:
    int second_;

    int time_difference_;
    map<string, int> timezone_;
};

struct InvalidTimeException{
  string input_time;
  InvalidTimeException(const string& str) : input_time(str){}
};

ostream& operator<<(ostream& os, const WorldClock& c);

istream& operator>>(istream& is, WorldClock& c);
