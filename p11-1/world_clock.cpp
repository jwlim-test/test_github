#include "world_clock.h"

std::map<std::string, int> WorldClock::timezone_;

WorldClock::WorldClock(){
	hour_ = 0;
	minute_ = 0;
	second_ = 0;
	time_difference_ = 0;
}

WorldClock::WorldClock(int hour, int minute, int second){
	hour_ = hour;
	minute_ = minute;
	second_ = second;
}

void WorldClock::Tick(int seconds){
	//��, �д����� �ʴ����� ȯ��
	int mysec = 0;
	mysec += second_;
	mysec += minute_ * 60;
	mysec += hour_ * 60 * 60;
	mysec += seconds;

	//�ʰ� ������ ����� ��ȯ (-1�� -> 23��)
	while (mysec<0) mysec += 24 * 60 *60;

	second_ = mysec % 60;
	mysec /= 60;
	minute_ = mysec % 60;
	mysec /= 60;
	hour_ = mysec % 24;
}

bool WorldClock::SetTime(int hour, int minute, int second){
	if (hour >= 24 || hour < 0) return false;
	if (minute >= 60 || minute < 0) return false;
	if (second >= 60 || second < 0) return false;

	hour_ = hour;
	minute_ = minute;
	second_ = second;
	return true;
}

void WorldClock::AddTimezoneInfo(const std::string& city, int diff){
	timezone_[city] = diff;
}

bool WorldClock::SetTimezone(const std::string& timezone){
	if (timezone_.find(timezone) == timezone_.end()) return false;

	hour_ -= time_difference_;	//���� ������ (+0����)
	if (hour_ < 0) hour_ += 24;
	time_difference_ = timezone_[timezone];
	hour_ += time_difference_;	//���� ����
	hour_ %= 24;
	return true;
}

std::ostream& operator<<(std::ostream& os, const WorldClock& c){
	os << c.hour() << ":" << c.minute() << ":" << c.second();
	if (c.time_difference() != 0) 
		os << " (+" << c.time_difference() << ")";
	return os;
}

std::istream& operator>>(std::istream& is, WorldClock& c){
	//XX:YY:ZZ �� input1�� XX, input2�� YY:ZZ�� �и�
	std::string input1, input2;
	int hour, minute, second;
	
	is >> input1;
	//�� �и�
	int i = input1.find(':');
	hour = atoi(input1.substr(0,i).c_str());
	input2 = input1.substr(i+1,input1.length());
	//��, �� �и�
	i = input2.find(':');
	minute = atoi(input2.substr(0,i).c_str());
	second = atoi(input2.substr(i+1,input2.length()).c_str());

	if(!c.SetTime(hour,minute,second)) throw InvalidTimeException(input1);
	
	return is;
}
