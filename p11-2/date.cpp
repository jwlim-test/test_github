#include "date.h"
Date::Date()
{
}
Date::Date(int year, int month, int day):year_(year),month_(month),day_(day)
{
}
  void Date::NextDay(int n)
  {
		int date_num = ComputeDaysFromYearStart(year_, month_, day_),yyear=0,mmonth=1,dday=1;
		date_num+=n;
		if (date_num > 0) // 0.1.1 < date
		{
			while (date_num >= GetDaysInYear(yyear)) // year compute
			{
				date_num-=GetDaysInYear(yyear);
				++yyear;
			}
			int day_list[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // max day
			if (GetDaysInYear(yyear) == 366) // 4 100 400 year compute
				++day_list[1]; // feb
			int i;
			for (i=0;i<12;++i) // month compute
			{
				if (date_num >= day_list[i])
					date_num-=day_list[i];
				else
					break;
			}
			mmonth = i+1;
			dday = date_num+1;			
		}
		if (date_num < 0) // 0.1.1 > date
		{
			while (date_num < GetDaysInYear(yyear-1)*(-1))
			{
				date_num+=GetDaysInYear(yyear-1);
				--yyear;
			}
			date_num+=GetDaysInYear(yyear-1);
			--yyear;
			int day_list[12]={31,28,31,30,31,30,31,31,30,31,30,31};
			if (GetDaysInYear(yyear) == 366)
				++day_list[1];
			int i;
			for (i=0;i<12;++i)
			{
				if (date_num >= day_list[i])
					date_num-=day_list[i];
				else
					break;
			}
			mmonth = i+1;
			dday = date_num+1;				
		}
		year_ = yyear;
		month_ = mmonth;
		day_ = dday;
	}
  bool Date::SetDate(int year, int month, int day)
  {
		int day_list[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if (GetDaysInYear(year) == 366)
			++day_list[1];
		if (month < 1 || month > 12) // out of range
			return 0;
		if (day < 1 || day_list[month-1] < day) // out of range
			return 0;
		year_ = year;
		month_ = month;
		day_ = day;
		return 1;
	}
  int Date::year() const
  {
		return year_;
	}
  int Date::month() const
  {
		return month_;
	}
  int Date::day() const
  {
		return day_;
	}
  int Date::GetDaysInYear(int year)
  {
		if (year%400 == 0)
			return 366;
		if (year%100 == 0)
			return 365;
		if (year % 4 == 0)
			return 366;
		return 365;
	}
  // 해당 날짜가 해당 연도의 처음(1월 1일)부터 며칠째인지를 계산.
  int Date::ComputeDaysFromYearStart(int year, int month, int day)
  {
		int i,sum=0;
		int day_list[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if (GetDaysInYear(year) == 366) // 4 100 400 year 
			++day_list[1];
		for (i=0;i<month-1;++i) // month convert
			sum+=day_list[i];
		sum+=day-1;
		if (year > 0) // year convert	> 0
		{
			for (i=0;i<year;++i)
				sum+=GetDaysInYear(i);
		}
		if (year < 0) // < 0
		{
			++sum;
			for (i=0;i>year;--i)
				sum-=GetDaysInYear(i);
		}
		return sum;
}
ostream& operator<<(ostream& os, const Date& c)
{
	os << c.year() << "." << c.month() << "." << c.day();
}
istream& operator>>(istream& is, Date& c)
{
	string temp,temp2;
	int i,last_point = 0,num_list[10],num_cnt=0;
	is >> temp;
	for (i=0;i<temp.length();++i)
	{
		if (temp[i] == '.')
		{
			temp2 = temp.substr(last_point,i-last_point);
			last_point = i+1;
			num_list[num_cnt++] = atoi(temp2.c_str());
		}
	}
	temp2 = temp.substr(last_point,i-last_point);
	last_point = i+1;
	num_list[num_cnt++] = atoi(temp2.c_str());
	if (c.SetDate(num_list[0],num_list[1],num_list[2]) == 0)
		throw(InvalidDateException(temp));
}
