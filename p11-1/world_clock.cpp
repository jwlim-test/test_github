  #include "world_clock.h"
  using namespace std;
#define secondOfTime 3600
#define secondOfMinute 60
#define hourOfDay 24
map<string, int> WorldClock :: timezone_;
  WorldClock::WorldClock() : time(0),time_difference_(0){}
  WorldClock::WorldClock(int hour, int minute, int second) :time_difference_(0){
		time = hour*secondOfTime+minute*secondOfMinute+second;
  }
  void WorldClock:: Tick(int seconds)
  {
		time+=seconds;
		if (time < 0) time=time%(secondOfTime*hourOfDay)+(secondOfTime*hourOfDay);
	}
  bool WorldClock::SetTime(int hour, int minute, int second)
  {
		if (hour < 0 || minute < 0 || second < 0 || 
			hour >= 24 || minute >= 60 || second >= 60)	return false;
		time = hour*secondOfTime+minute*secondOfMinute+second;
		return true;
	}
 void WorldClock::AddTimezoneInfo(const string& city, int diff) {
		timezone_[city] = diff;
	}
  bool WorldClock::SetTimezone(const string& timezone)
  {
		if (timezone_.find(timezone) == timezone_.end()) return false;
		time_difference_ = timezone_[timezone];
		return true;
	}
  int WorldClock::hour() const{
		return (time/secondOfTime)%hourOfDay;
	}
  int WorldClock::minute() const{
		return (time%secondOfTime)/secondOfMinute;
	}
  int WorldClock::second() const {
		return time%secondOfMinute;
	}
ostream& operator<<(ostream& os, const WorldClock& c)
{
	WorldClock temp = c;
	temp.Tick(temp.time_difference()*secondOfTime);

	os << temp.hour() << ":" << temp.minute() << ":" << temp.second();
	if (temp.time_difference() >= 0)	os << " (+" << temp.time_difference() << ")";
	else os << " (" << temp.time_difference() << ")";
	return os;
}
istream& operator>>(istream& is, WorldClock& c)  // hh:mm:ss 로 입력받음.
{
	string input,temp;
	int p=0,num[10],cnt=0;
	is >> input;
	for (int i=0;i<input.length();i++){
		if (input[i] == ':'){
			temp = input.substr(p,i-p);
			p=i+1;
			num[cnt++] = atoi(temp.c_str());
		}
	}
	num[cnt++] = atoi(input.substr(last,i-last).c_str());
	return is;
}
