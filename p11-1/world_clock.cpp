#include "world_clock.h"
using namespace std;
map<string, int> WorldClock :: timezone_;
WorldClock::WorldClock() : second_time_(0),time_difference_(0)
{
}
WorldClock::WorldClock(int hour, int minute, int second) :time_difference_(0)
{
	second_time_ = hour*3600+minute*60+second; // convert to second 
}
void WorldClock:: Tick(int seconds)
{
	second_time_+=seconds;
	while(time < 0)
		second_time_+=3600*24;
}
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
bool WorldClock::SetTime(int hour, int minute, int second)
{
	if (hour < 0 || minute < 0 || second < 0 || hour >= 24 || minute >= 60 || second >= 60) // if out of range
		return false;
	second_time_ = hour*3600+minute*60+second; // convert to second
	return true;
}
//static bool LoadTimezoneFromFile(const string& file_path); 
//ä������ ������ ���� ������� �������
//�ʰ� �Ʒ��� �Լ�(AddTimezoneInfo)�� ����մϴ�.��
void WorldClock::AddTimezoneInfo(const string& city, int diff)
{
	timezone_[city] = diff;
}
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
bool WorldClock::SetTimezone(const string& timezone)
{
	if (timezone_.find(timezone) == timezone_.end()) // can't find
		return false;
	time_difference_ = timezone_[timezone];
	return true;
}
int WorldClock::hour() const
{
	return (second_time_/3600)%24;
}
int WorldClock::minute() const
{
	return (second_time_%3600)/60;
}
int WorldClock::second() const
{
	return second_time_%60;
}
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
ostream& operator<<(ostream& os, const WorldClock& c)
{
	WorldClock difference_applied_time = c;
	difference_applied_time.Tick(difference_applied_time.time_difference()*3600); // plus difference
	os << difference_applied_time.hour() << ":" << difference_applied_time.minute() << ":" << difference_applied_time.second();
	if (difference_applied_time.time_difference() > 0) // if not GMT -> difference != 0
		os << " (+" << difference_applied_time.time_difference() << ")";
	if (difference_applied_time.time_difference() < 0)
		os << " (" << difference_applied_time.time_difference() << ")";
	return os;
}
istream& operator>>(istream& is, WorldClock& c)  // hh:mm:ss �� �Է¹���.
{
	string input_string,input_segment;
	int i,last=0;
	vector<int> num;
	is >> input_string;
	for (i=0;i<input_string.length();++i)
	{
		if (input_string[i] == ':')
		{
			input_segment = input_string.substr(last,i-last);
			num.push_back(atoi(input_segment.c_str()));
			last = i+1;
		}
	}
	input_segment = input_string.substr(last,i-last);
	num.push_back(atoi(input_segment.c_str()));
	last = i+1;	
	if (num.size() != 3 || c.SetTime(num[0],num[1],num[2]) == 0)
		throw InvalidTimeException(input_string);
	return is;
}
