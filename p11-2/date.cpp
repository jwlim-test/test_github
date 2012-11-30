#include "date.h"
using namespace std;
  void Date::NextDay(int n)
  {
		int temp_year=0,temp_month=1,temp_day=1;

		int numDays = ComputeDaysFromYearStart(year_, month_, day_);
		numDays+=n;

		while (numDays >= GetDaysInYear(temp_year)){
			numDays-=GetDaysInYear(temp_year);
			++temp_year;
		}
		int numOfDay[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if(GetDaysInYear(temp_year)==366) numOfDay[1]=29;

		for (int i=0;i<12;i++) {
			if(numDays >= day_list[i]) numDays-=numOfDay[i];
			else break;
		}
		temp_month = i+1;

		temp_day = numDays+1;			
		year_ = temp_year;
		month_ = temp_month;
		day_ = temp_day;
	}
  bool Date::SetDate(int year, int month, int day)
  {
		int numOfDay[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if(GetDaysInYear(temp_year)==366) numOfDay[1]=29;
		if (month < 1 || month > 12) return false; // check exception
		if (day < 1 || numOfDay[month-1] < day) return false;

		year_ = year;
		month_ = month;
		day_ = day;
		return true;
	}
  int Date::year() const {
		return year_;
	}
  int Date::month() const{
		return month_;
	}
  int Date::day() const{
		return day_;
	}
  int Date::GetDaysInYear(int year)
  {
		if (year%400 == 0) return 366;
		if (year%100 == 0) return 365;
		if (year % 4 == 0) return 366;
		return 365;
	}
  int Date::ComputeDaysFromYearStart(int year, int month, int day)
  {
		int sum=0;

		int numOfDay[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if(GetDaysInYear(temp_year)==366) numOfDay[1]=29;

		for (int i=0;i<month-1;i++)	sum+=numOfDay[i];
		sum+=day-1;

		for (int i=0;i<year;i++) sum+=GetDaysInYear(i);
		return sum;
}
ostream& operator<<(ostream& os, const Date& c){
	os << c.year() << "." << c.month() << "." << c.day();
}
istream& operator>>(istream& is, Date& c)
{
	string input,temp;
	int p=0;
	int listInput[111],cntInput=0;
	is >> input;
	for (int i=0;i<input.length();i++){

		if (input[i] == '.'){
			temp = input.substr(p,i-p);
			p = i+1;
			listInput[cntInput++] = atoi(temp.c_str());
		}

	}
	temp = input.substr(p,i-p);
	listInput[cntInput++] = atoi(temp.c_str());

	if (c.SetDate(listInput[0],listInput[1],listInput[2]) == false)
		throw(InvalidDateException(input));
}
