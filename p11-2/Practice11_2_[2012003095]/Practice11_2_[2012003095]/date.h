#include<iostream>
#include<string>

using namespace std;

class Date
{
public:
	Date()//
	{
	}
	Date(int year, int month, int day)//
	{
		year_ = year, month_ = month, day_ = day;
	}

	void NextDay(int n = 1)//
	{
		int days = ComputeDaysGromYearStart(year_, month_, day_);
		days+=n;

		while(1)
		{
			if(days > GetDaysInYear(year_))
			{
				days -= GetDaysInYear(year_);
				year_++;
			}
			else if(days<=0)
			{
				year_--;
				days+=GetDaysInYear(year_);
			}
			else
				break;
		}

		month_ = 1;

		while(1)
		{
			if(month_ == 1 && days>31)
			{
				month_++;
				days-=31;
			}
			else if(month_ == 2 && GetDaysInYear(year_) == 365 && days>28)
			{
				month_++;
				days-=28;
			}
			else if(month_ == 2 && GetDaysInYear(year_) == 366 && days>29)
			{
				month_++;
				days-=29;
			}
			else if(month_ == 3 && days>31)
			{
				month_++;
				days-= 31;
			}
			else if(month_ == 4 && days>30)
			{
				month_ ++;
				days-=30;
			}
			else if(month_ == 5 && days>31)
			{
				month_++;
				days-= 31;
			}
			else if(month_ == 6 && days>30)
			{
				month_++;
				days-=30;
			}
			else if(month_ == 7 && days>31)
			{
				month_++;
				days-=31;
			}
			else if(month_ == 8 && days>31)
			{
				month_++;
				days-=31;
			}
			else if(month_ == 9 && days>30)
			{
				month_++;
				days-=30;
			}
			else if(month_ == 10 && days>31)
			{
				month_++;
				days-=31;
			}
			else if(month_ == 11 && days>30)
			{
				month_++;
				days-=30;
			}
			else
			{
				break;
			}
		}

		day_ = days;
	}

	bool SetDate(int year, int month, int day)//
	{
		year_ = year, month_ = month, day_ = day;
		return true;
	}

	int year() const//
	{
		return year_;
	}
	int month() const//
	{
		return month_;
	}
	int day() const//
	{
		return day_;
	}

private:
	//윤년을 판단하여 주어진 연도에 해당하는 날짜 수 (365 또는 366)를 리턴.
	//1-31 : 2-28||29 : 3-31 : 4-30 : 5-31 : 6-30 : 7-31 : 8-31 : 9-30 : 10-31 : 11-30 : 12-31
	//① 서력 기원 연수가 4로 나누어 떨어지는 해는 우선 윤년으로 하고, ② 그 중에서 100으로 나누어
	//떨어지는 해는 평년으로 하며, ③ 다만 400으로 나누어 떨어지는 해는 다시 윤년으로 정하였다.
	static int GetDaysInYear(int year)//
	{
		if(year%4 == 0 && year%100 == 0 && year%400 == 0)
			return 366;
		else if(year%4 == 0 && year%100 == 0)
			return 365;
		else if(year%4 == 0)
			return 366;
		else
			return 365;
	}
	//해당 날짜가 해당 연도의 처음(1월 1일)부터 며칠째인지를 계산.
	static int ComputeDaysGromYearStart(int year, int month, int day)//
	{
		int days=0;

		for(int i=1; i<month; i++)
		{
			if(i==1)
				days+=31;
			else if(i==2 && GetDaysInYear(year)== 365)
				days+=28;
			else if(i==2 && GetDaysInYear(year)== 366)
				days+=29;
			else if(i==3)
				days+=31;
			else if(i==4)
				days+=30;
			else if(i==5)
				days+=31;
			else if(i==6)
				days+=30;
			else if(i==7)
				days+=31;
			else if(i==8)
				days+=31;
			else if(i==9)
				days+=30;
			else if(i==10)
				days+=31;
			else if(i==11)
				days+=30;
		}

		days += day;

		return days;
	}

	int year_, month_, day_;//
};




struct InvalidDateException//
{
	string input_date;
	InvalidDateException(const string&str) : input_date(str)
	{
	}
};




//yyyy.mm.dd 형식으로 입출력.
//사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.
ostream& operator<<(ostream& os, const Date& c)
{
	cout<<c.year()<<"."<<c.month()<<"."<<c.day();

	return os;
}

istream& operator>>(istream& is, Date& c)//
{
	string input;
	cin>>input;

	int year=0, day=0, month=0;

	int ymd = 0;

	for(unsigned int i=0; i<input.size(); i++)
	{
		if(input.at(i) == '.')
		{
			ymd++;
			continue;
		}

		if(ymd == 0)
		{
			year = year*10 + input.at(i)-48;
		}
		else if(ymd == 1)
		{
			month = month*10 + input.at(i)-48;
		}
		else if(ymd == 2)
		{
			day = day*10 + input.at(i)-48;
		}
	}

	InvalidDateException e(input);
	//1-31 : 2-28||29 : 3-31 : 4-30 : 5-31 : 6-30 : 7-31 : 8-31 : 9-30 : 10-31 : 11-30 : 12-31
	if(month == 0 || day == 0)
		throw e;
	else if(month == 1 && day>31)
		throw e;
	else if(month == 2)
	{
		int is_yun = 0;

		if(year%4 == 0 && year%100 == 0 && year%400 == 0)
			is_yun = 1;	
		else if(year%4 == 0 && year%100 == 0)
			is_yun = 0;
		else if(year%4 == 0)
			is_yun = 1;
		else
			is_yun = 0;
		
		if(is_yun == 0 && day>28)
			throw e;
		else if(is_yun == 1 && day>29)
			throw e;
	}
	else if(month == 3 && day>31)
		throw e;
	else if(month == 4 && day>30)
		throw e;
	else if(month == 5 && day>31)
		throw e;
	else if(month == 6 && day>30)
		throw e;
	else if(month == 7 && day>31)
		throw e;
	else if(month == 8 && day>31)
		throw e;
	else if(month == 9 && day>30)
		throw e;
	else if(month == 10 && day>31)
		throw e;
	else if(month == 11 && day>30)
		throw e;
	else if(month == 12 && day>31)
		throw e;

	c.SetDate(year, month, day);

	return is;
}