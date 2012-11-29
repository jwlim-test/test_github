#include "date.h"

Date::Date(){
	year_ = 0;
	month_ = 0;
	day_ = 0;
}

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

void Date::NextDay(int n){
	int days;
	int month = 1;
	days = ComputeDaysFromYearStart(year_,month_,day_);
	days += n;
	
	while (true) {
		if (days > GetDaysInYear(year_)){
			days -= GetDaysInYear(year_);
			year_++;
		} else if (days <= 0){
			year_--;
			days += GetDaysInYear(year_);
		} else
			break;
	}

	while(true){
		if (month == 2) {
			if ((year_ % 4 == 0 && year_ % 100 != 0) || year_ % 400 == 0) {
				if (days > 29) {
					month++;
					days -= 29;
				} else break;
			}else {
				if (days > 28) {
					month++;
					days -= 28;
				} else break;
			}
		} else if (month == 1 || month == 3 || month == 5 || month == 7
			|| month == 8 || month == 10 || month == 12){
				if ( days > 31) {
					month++;
					days -= 31;
				} else break;
		} else {
			if (days > 30) {
				month++;
				days -= 30;
			} else break;
		}
	}

	month_ = month;
	day_ = days;
}

bool Date::SetDate(int year, int month, int day){
	if (day <= 0) return false;
	if (month <=0 || month >12) return false;

	if (month == 2){
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
			if (day > 29) return false;
		} else {
			if (day > 28) return false;
		}
	} else if (month == 1 || month == 3 || month == 5 || month == 7
		|| month == 8 || month == 10 || month == 12){
			if (day > 31) return false;
	} else {
		if (day > 30) return false;
	}

	year_ = year;
	month_ = month;
	day_ = day;
	return true;
}

int Date::GetDaysInYear(int year){
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 366 : 365;
}

int Date::ComputeDaysFromYearStart(int year, int month, int day){
	int num = 0;
	for (int i = 1; i < month; ++i){
		if (i == 2){
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){ 
				num += 29;
			} else { num += 28; }
		} else if (i == 1 || i == 3 || i == 5 || i == 7
			|| i == 8 || i == 10 || i == 12){ 
				num += 31; 
		} else { num += 30; }
	}

	num += day;
	return num;
}

std::ostream& operator<<(std::ostream& os, const Date& c){
	os << c.year() << "." << c.month() << "." << c.day();
	return os;
}

	
std::istream& operator>>(std::istream& is, Date& c){
	std::string input1,input2;
	int year,month,day;
	is >> input1;
	//년도 분리
	int i = input1.find('.');
	year = atoi(input1.substr(0,i).c_str());
	input2 = input1.substr(i+1,input1.length());
	//월, 일 분리
	i = input2.find('.');
	month = atoi(input2.substr(0,i).c_str());
	day = atoi(input2.substr(i+1,input2.length()).c_str());

	if(!c.SetDate(year,month,day))
		throw InvalidDateException(input1);

	return is;
}
