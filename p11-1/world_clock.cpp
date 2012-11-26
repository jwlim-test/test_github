  #include "world_clock.h"
map<string, int> WorldClock :: timezone_;
  WorldClock::WorldClock() : time(0),time_difference_(0)
  {
	}
  WorldClock::WorldClock(int hour, int minute, int second) :time_difference_(0)
  {
		time = hour*3600+minute*60+second; // convert to second 
	}
  void WorldClock:: Tick(int seconds)
  {
		time+=seconds;
		if (time < 0) // when seconds is negative, time can be negative
			time=time%(3600*24)+(3600*24); // so plus one day
	}
  // 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
  bool WorldClock::SetTime(int hour, int minute, int second)
  {
		if (hour < 0 || minute < 0 || second < 0 || hour >= 24 || minute >= 60 || second >= 60) // if out of range
			return 0;
		time = hour*3600+minute*60+second; // convert to second
		return 1;
	}
  //static bool LoadTimezoneFromFile(const string& file_path); 
  //채점서버 문제로 파일 입출력을 사용하지
  //않고 아래의 함수(AddTimezoneInfo)를 사용합니다.↓
 void WorldClock::AddTimezoneInfo(const string& city, int diff)
  {
		timezone_[city] = diff;
	}
  // 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
  bool WorldClock::SetTimezone(const string& timezone)
  {
		if (timezone_.find(timezone) == timezone_.end()) // can't find
			return 0;
		time_difference_ = timezone_[timezone];
		return 1;
	}
  int WorldClock::hour() const
  {
		return (time/3600)%24;
	}
  int WorldClock::minute() const
  {
		return (time%3600)/60;
	}
  int WorldClock::second() const
  {
		return time%60;
	}
// hh:mm:ss 형식으로 입출력. 표준시가 아닌 경우 (+xx) 형식으로 시차를 표시.
// 사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.
ostream& operator<<(ostream& os, const WorldClock& c)
{
	WorldClock temp = c;
	temp.Tick(temp.time_difference()*3600); // plus difference
	os << temp.hour() << ":" << temp.minute() << ":" << temp.second();
	if (temp.time_difference() > 0) // if not GMT -> difference != 0
		os << " (+" << temp.time_difference() << ")";
	if (temp.time_difference() < 0)
		os << " (" << temp.time_difference() << ")";
	return os;
}
istream& operator>>(istream& is, WorldClock& c)  // hh:mm:ss 로 입력받음.
{
	string temp,temp2;
	int i,last=0,num[10],num_cnt=0;
	is >> temp;
	for (i=0;i<temp.length();++i)
	{
		if (temp[i] == ':')
		{
			temp2 = temp.substr(last,i-last);
			num[num_cnt++] = atoi(temp2.c_str());
			last = i+1;
		}
	}
	temp2 = temp.substr(last,i-last);
	num[num_cnt++] = atoi(temp2.c_str());
	last = i+1;	
	if (c.SetTime(num[0],num[1],num[2]) == 0)
		throw InvalidTimeException(temp);
	return is;
}
