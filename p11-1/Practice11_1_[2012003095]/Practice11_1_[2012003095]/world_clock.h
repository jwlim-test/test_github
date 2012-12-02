#include<iostream>
#include<string>
#include<map>

using namespace std;

class WorldClock
{
public:
	WorldClock()//
	{
		invalid_input = 0;
		timezone_["GMT"] = 0;
		time_difference_=0;
	}
	WorldClock(int hour, int minute, int second)//
	{
		hours = hour;
		minutes = minute;
		seconds = second;
		invalid_input = 0;
		timezone_["GMT"] = 0;
		time_difference_=0;
	}

	void Tick(int input_seconds = 1)//
	{
		hours += input_seconds/3600;
		input_seconds = input_seconds%3600;

		minutes += input_seconds/60;
		input_seconds = input_seconds%60;

		seconds += input_seconds;

		minutes += seconds/60;
		seconds = seconds%60;

		hours += minutes/60;
		minutes = minutes%60;
	}
	//잘못된 값 입력시 false리턴, 원래의 시간은 바뀌지 않는다.
	bool SetTime(int hour, int minute, int second)//
	{
		if(hour>24 || minute>=60 || second>=60 || (hour == 24 && (minute =! 0 || second != 0)))
		{
			invalid[0] = hour;
			invalid[1] = minute;
			invalid[2] = second;
			invalid_input = 1;

			return false;
		}

		hours = hour;
		minutes = minute;
		seconds = second;
		invalid_input = 0;

		return true;
	}

	int get_invalid()//-
	{
		return invalid_input;
	}
	int get_invalid_hour()//-
	{
		return invalid[0];
	}
	int get_invalid_minute()//-
	{
		return invalid[1];
	}
	int get_invalid_second()//-
	{
		return invalid[2];
	}

	void AddTimezoneInfo(string city, int diff)//const string&
	{
		timezone_[city] = diff;
	}
	//잘못된 값 입력시 false리턴, 원래의 시간은 바뀌지 않는다.
	bool SetTimezone(string timezone) //const string&k
	{
		if(timezone_.find(timezone) == timezone_.end())
		{
			//cout<<"오류"<<endl;//지울것
			return false;
		}
		else
		{
			time_difference_ = timezone_[timezone];
			//cout<<">>"<<time_difference_<<"<<"<<endl;
			return true;
		}
	}

	int hour() const//
	{
		return hours;
	}
	int minute() const//
	{
		return minutes;
	}
	int second() const//
	{
		return seconds;
	}
	int time_difference() const//
	{
		return time_difference_;
	}
	void save_input(string str)//-
	{
		last_input = str;
	}
	string return_last_input()//-
	{
		return last_input;
	}
	void save_zone(string str)
	{
		zone = str;
	}
	

private:
	//여기에 시간 관련 멤버변수 정의, (GMT 시간을 사용)
	int hours, minutes, seconds;
	int invalid[3], invalid_input;
	string last_input, zone;
	
	//Timezone 관련 정보는 아래 변수에 저장,시차는 시간 단위로만 계산.
	int time_difference_;
	map<string, int> timezone_;
};







struct InvalidTimeException
{
	string input_time;
	InvalidTimeException(const string& str) : input_time(str)
	{
	}
};




//hh:mm:ss: 형식으로 입출력, 표준시가 아닌 경우 (+XX) 형식으로 시차를 ㅠㅛ기
//사용자 입력 오휴기 >> operator는 InvalidDateException을 발생할 수 있음.
ostream& operator<<(ostream& os, WorldClock& c) //(+XX)처리- clear
{
	if(c.get_invalid() == 1)
	{
		InvalidTimeException e(c.return_last_input());
		throw e;
	}
	if(c.get_invalid() == 0)
	{
		if(c.time_difference() == 0)
		{
			cout<<c.hour()%24<<":"<<c.minute()<<":"<<c.second();
		}
		else
		{
			cout<<(c.hour()+c.time_difference())%24<<":"<<c.minute()<<":"<<c.second()<<" (+"<<c.time_difference()<<")";
		}
	}

	return os;
}


istream& operator>>(istream& is, WorldClock& c)//hh:mm:ss로 입력받음.
{
	string input;

	cin>>input;

	c.save_zone("GMT");
	c.save_input(input);

	int hms = 0, h_val=0, m_val = 0, s_val = 0;

	for(unsigned int i=0; i<input.size(); i++)
	{
		if(input.at(i) == ':')
		{
			hms++;
		}
		else
		{
			if(hms == 0)
				h_val = h_val*10 + input.at(i) - 48;
			else if(hms == 1)
				m_val = m_val*10 + input.at(i) - 48;
			else if(hms == 2)
				s_val = s_val*10 + input.at(i) - 48;
		}
	}

	c.SetTime(h_val, m_val, s_val);

	return is;
}