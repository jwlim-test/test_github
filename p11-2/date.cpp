#include "date.h"

Date::Date(){
	year_ = 0;
	month_ = 0;
	day_ = 0;
}

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {;}

void Date::NextDay(int n){
	int days;
	int month = 1;
	days = ComputeDaysFromYearStart(year_,month_,day_);
	days += n;
	
	while(true){
		if(days > GetDaysInYear(year_)){
			days -= GetDaysInYear(year_);
			year_++;
		}else if(days <= 0){
			year_--;
			days += GetDaysInYear(year_);
		}
		else
			break;
	}

	while(true){
		if(year_ % 4 ==0){
			if(year_ % 100 == 0){
				if(year_ % 400 == 0){
					if(month == 2){
						if(days > 29){
							month++;
							days -= 29;
						}else break;
					}else if(month == 1 || month == 3 || month == 5 || month == 7
							|| month == 8 || month == 10 || month == 12){
								if(days > 31){
									month++;
									days -= 31;
								}
								else break;
					}else{
						if(days > 30){
							month++;
							days -= 30;
						}else break;
					}
				}else{
					if(month == 2){
						if(days > 28){
							month++;
							days -= 28;
						}else break;
					}else if(month == 1 || month == 3 || month == 5 || month == 7
							|| month == 8 || month == 10 || month == 12){
								if(days > 31){
									month++;
									days -= 31;
								}else break;
					}else{
						if(days > 30){
							month++;
							days -= 30;
						}else break;
					}
				}
			}else{
				if(month == 2){
					if(days > 29){
						month++;
						days -= 29;
					}else break;
				}else if(month == 1 || month == 3 || month == 5 || month == 7
						|| month == 8 || month == 10 || month == 12){
							if(days > 31){
								month++;
								days -= 31;
							}else break;
				}else{
					if(days > 30){
						month++;
						days -= 30;
					}else break;
				}
			}
		}else{
			if(month == 2){
				if(days > 28){
					month++;
					days -= 28;
				}else break;
			}else if(month == 1 || month == 3 || month == 5 || month == 7
					|| month == 8 || month == 10 || month == 12){
						if(days > 31){
							month++;
							days -= 31;
						}else break;
			}else{
				if(days > 30){
					month++;
					days -= 30;
				}else break;
			}
		}
	}
	month_ = month;
	day_ = days;
	
}

bool Date::SetDate(int year, int month, int day){
	if(day <= 0) return false;
	if(month <=0 || month >12) return false;

	if(year % 4 ==0){
		if(year % 100 == 0){
			if(year % 400 == 0){
				if(month == 2){
					if(day > 29) return false;
				}else if(month == 1 || month == 3 || month == 5 || month == 7
						|| month == 8 || month == 10 || month == 12){
							if(day > 31) return false;
				}else{
					if(day > 30) return false;
				}
			}else{
				if(month == 2){
					if(day > 28) return false;
				}else if(month == 1 || month == 3 || month == 5 || month == 7
						|| month == 8 || month == 10 || month == 12){
							if(day > 31) return false;
				}else{
					if(day > 30) return false;
				}
			}
		}else{
			if(month == 2){
				if(day > 29) return false;
			}else if(month == 1 || month == 3 || month == 5 || month == 7
					|| month == 8 || month == 10 || month == 12){
						if(day > 31) return false;
			}else{
				if(day > 30) return false;
			}
		}
	}else{
		if(month == 2){
			if(day > 28) return false;
		}else if(month == 1 || month == 3 || month == 5 || month == 7
				|| month == 8 || month == 10 || month == 12){
					if(day > 31) return false;
		}else{
			if(day > 30) return false;
		}
	}

	year_ = year;
	month_ = month;
	day_ = day;
	return true;
}

int Date::GetDaysInYear(int year){
	if(year % 4 == 0){
		if(year % 100 == 0){
			if(year % 400 == 0){
				return 366;
			}
			return 365;
		}
		return 366;
	}
	else
		return 365;
}

int Date::ComputeDaysFromYearStart(int year, int month, int day){
	int num=0;
	for(int i = 1; i < month; ++i){
		if(year % 4 == 0){
			if(year % 100 == 0){
				if(year % 400 == 0){
					if(i == 2){
						num += 29;
					}else if(i == 1 || i == 3 || i == 5 || i == 7
						|| i == 8 || i == 10 || i == 12){
							num += 31;
					}else
						num += 30;
				}else{
					if(i == 2){
						num += 28;
					}else if(i == 1 || i == 3 || i == 5 || i == 7
						|| i == 8 || i == 10 || i == 12){
							num += 31;
					}else
						num += 30;
				}
			}else{
				if(i == 2){
					num += 29;
				}else if(i == 1 || i == 3 || i == 5 || i == 7
					|| i == 8 || i == 10 || i == 12){
						num += 31;
				}else
					num += 30;
			}
		}else{
			if(i == 2){
				num += 28;
			}else if(i == 1 || i == 3 || i == 5 || i == 7
				|| i == 8 || i == 10 || i == 12){
					num += 31;
			}else
				num += 30;
		}
	}

	num += day;

	return num;
}

ostream& operator<<(ostream& os, const Date& c){
	os << c.year() << "." << c.month() << "." << c.day();
	return os;
}

	
istream& operator>>(istream& is, Date& c){
	string input1,input2;
	int year,month,day;
	is >> input1;
	InvalidDateException e(input1);

	for(int i = 0; i < input1.length(); ++i){
		if(input1[i] == '.'){
			year = atoi(input1.substr(0,i).c_str());
			input2 = input1.substr(i+1,input1.length());
			break;
		}
	}
	for(int i = 0; i < input2.length(); ++i){
		if(input2[i] == '.'){
			month = atoi(input2.substr(0,i).c_str());
			day = atoi(input2.substr(i+1,input2.length()).c_str());
			break;
		}
	}
	if(!c.SetDate(year,month,day))
		throw e;

	return is;
}