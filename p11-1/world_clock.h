#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

class WorldClock {
    public:
        WorldClock () : hour_(0) , minute_(0), second_(0) {}
        WorldClock (int hour, int minute, int second) : hour_(hour), minute_(minute), second_(second) {}
        
        void Tick(int seconds =1);
        
        bool SetTime(int hour, int minute, int second);
        
        void AddTimezoneInfo(const string& city, int diff);
        
        static bool SetTimezone(const string& timezone);
        
        int hour() const {return hour_;}
        int minute () const { return minute_;}
        int second () const { return second_;}
        int time_difference() const { return time_difference_;}
        
    private:
        
        int hour_, minute_, second_;
        int time_difference_;
        static map<string, int> timezone_;
};

struct InvalidTimeException {
    string input_time;
    InvalidTimeException(const string& str) : input_time(str) {}
};

ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);
