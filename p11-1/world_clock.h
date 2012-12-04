#include <iostream>
#include <string>
#include <map>
using namespace std;

class WorldClock {
 public:
     //▒~]▒▒~R~K▒~[▒~]~@ ▒~J▒▒~J▒▒~A▒~]~D ▒| ~@▒~^▒. (▒~W~P▒~_▒▒~K~\ throw)
   string t;
     WorldClock() : sec_(0),time_difference_(0){}
     WorldClock(int hour, int minute, int second) : sec_((3600*hour)+(60*minute)+second),time_difference_(0){}
  void Tick(int seconds = 1);
  // ▒~^~X못▒~P~\ ▒~R ▒~^~E▒| ▒▒~K~\ false 리▒~D▒▒~U~X▒|  ▒~[~P▒~^~X ▒~K~\▒~D▒~]~@ ▒~T▒~@~L▒~@ ▒~U~J▒~]~L.
  bool SetTime(int hour, int minute, int second);
  //static bool LoadTimezoneFromFile(const string& file_path);
  //▒~D▒| ~P▒~D~\▒~D 문▒| ~\▒~\ ▒~L~L▒~]▒ ▒~^~E▒~\▒| ▒▒~]~D ▒~B▒▒~Z▒▒~U~X▒~@
  //▒~U~J▒|  ▒~U~D▒~^~X▒~]~X ▒~U▒▒~H~X(AddTimezoneInfo)를 ▒~B▒▒~Z▒▒~U▒▒~K~H▒~K▒.▒~F~S
  static void AddTimezoneInfo(const string& city, int diff);
  // ▒~^~X못▒~P~\ ▒~R ▒~^~E▒| ▒▒~K~\ false 리▒~D▒▒~U~X▒|  ▒~[~P▒~^~X ▒~K~\▒~D▒~]~@ ▒~T▒~@~L▒~@ ▒~U~J▒~]~L.
  bool SetTimezone(const string& timezone);
  int hour() const;
  int minute() const;
  int second() const;
  int time_difference() const { return time_difference_; }
 private:
     //▒| ~D체 ▒~K~\▒~D▒~]~D ▒~H▒~K▒▒~\~D▒~\ ▒~Q~\▒~X~D (Tick▒~W▒▒~B▒▒~]▒ ▒~D▒~N▒▒~U~X▒~K▒▒~J~T ▒~^▒▒| ~P▒~]▒ ▒~^~H▒~K▒.)
    int sec_;
  // ▒~W▒기▒~W~P ▒~K~\▒~A ▒~@▒| ▒ 멤▒~D ▒~@▒~H~X ▒| ~U▒~]~X. (GMT ▒~K~\▒~D▒~]~D ▒~B▒▒~Z▒)
  // Timezone ▒~@▒| ▒ ▒| ~U보▒~J~T ▒~U~D▒~^~X ▒~@▒~H~X▒~W~P ▒| ~@▒~^▒. ▒~K~\차▒~J~T ▒~K~\▒~D ▒~K▒▒~\~D▒~\▒~L ▒~D▒~B▒.
  int time_difference_;
  static map<string, int> timezone_;
};
struct InvalidTimeException {
  string input_time;
  InvalidTimeException(const string& str) : input_time(str) {}
};
// hh:mm:ss ▒~X~U▒~K~]▒~\▒▒~\ ▒~^~E▒~\▒| ▒. ▒~Q~\▒~@▒~K~\▒~@ ▒~U~D▒~K~L 경▒~Z▒ (+xx) ▒~X~U▒~K~]▒~\▒▒~\ ▒~K~\차를 ▒~Q~\▒~K~\.
// ▒~B▒▒~Z▒▒~^~P ▒~^~E▒| ▒ ▒~X▒▒~X▒~K~\ >> operator▒~J~T InvalidDateException▒~]~D ▒~\▒~C~]▒~U|  ▒~H~X ▒~^~H▒~]~L.
ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);  // hh:mm:ss ▒~\ ▒~^~E▒| ▒▒~[▒~]~L.

~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~

