#include "date.h"
#include <stdlib.h>

Date:: Date(){};

Date:: Date(int year, int month, int day){
  year_=year;
  month_=month;
  day_=day;
}

int Date::year() const{ return year_;}

int Date::month() const{return month_;}

int Date::day() const{return day_;}

void Date::NextDay(int n){
  for (int i=0;i<n;i++){
  if (month_<8 && month_%2==1){
    if (day_<31)
      day_++;
    else{
      month_++;
      day_=1;
    }
  }

  else if (month_==2){
    if (GetDaysInYear(year_)==366){
      if (day_<29)
        day_++;
      else{
        month_++;
        day_=1;
      }
    }
    else if (GetDaysInYear(year_)==365){
      if (day_<28)
        day_++;
      else{
        month_++;
        day_=1;
      }
    }
  }

  else if (month_<8 && month_%2==0){
    if (day_<30)
      day_++;
    else{
      month_++;
      day_=1;
    }
  }

  else if (month_>=8 && month_%2==0){
    if (day_<31)
      day_++;
    else{
      month_++;
      day_=1;
    }
  }

  else if (month_>=8 && month_%2==1){
    if (day_<30)
      day_++;
    else{
      month_++;
      day_=1;
    }
  }

  if (month_==13){
    month_=1;
    year_++;
  }
  }
  
  for (int i=0;i>n;i--){
    if (day_!=1)
      day_--;
    else{
      if (month_==2 || month_==4 || month_==6 || month_==8 || month_==9 || month_==11){
        day_=31;
        month_--;
      }

      else if (month_==1){
        day_=31;
        month_=12;
        year_--;
      }

      else if (month_==3){
        if (GetDaysInYear(year_)==366)
          day_=29;
        else
          day_=28;

        month_=2;
      }

      else if (month_==5 || month_==7 || month_==10 || month_==12){
        day_=30;
        month_--;
      }
    }
  }

}

bool Date::SetDate(int year, int month, int day){
  if (day<=0)
    return false;

  if (month>12 || month<=0)
    return false;

  if (month<8 && month%2==1 && day>31)
    return false;

  if (month<8 && month%2==0 && month!=2 && day>30)
    return false;

  if (month==2 && GetDaysInYear(year)==366 && day>29)
    return false;

  if (month==2 && GetDaysInYear(year)==365 && day>28)
    return false;

  if (month>8 && month%2==0 && day>31)
    return false;

  if (month>8 && month%2==1 && day>30)
    return false;

  year_=year;
  month_=month;
  day_=day;

  return true;
}

int Date::GetDaysInYear(int year){
  if (year%400==0)
    return 366;
  else if (year%100==0)
    return 365;

  else if (year%4==0)
    return 366;

  else
    return 365;
}

int Date::ComputeDaysFromYearStart(int year, int month, int day){
  int n=0;
  if(month==2)
    n+=31;
  else if (month>2){
    n+=59;
    for (int i=3;i<month;i++){
      if (i<8){
        if (i%2==1)
          n+=31;
        else if (i%2==0)
          n+=30;
      }
      else if (i>=8){
        if (i%2==0)
          n+=31;
        else if (i%2==1)
          n+=30;
      }
    }
  }
  n+=day;
  if (GetDaysInYear(year)==366 && month>2)
    n+=1;

  return n;
}

istream& operator>>(istream& is, Date& c){
  int year, month, day;
  string a;
  is>>a;
  int i, j, k;
  for (i=0;i<a.size();i++)
    if (a[i]=='.'){
      j=i;
      break;
    }

  for (i=j+1;i<a.size();i++)
    if (a[i]=='.'){
      k=i;
      break;
    }

  year=atoi((a.substr(0,j)).c_str());
  month=atoi((a.substr(j+1,k)).c_str());
  day=atoi((a.substr(k+1,a.size())).c_str());

  if (!c.SetDate(year, month, day))
    throw InvalidDateException(a);

  return is;
}

ostream& operator<<(ostream& os, const Date& c){
  os<<c.year()<<'.'<<c.month()<<'.'<<c.day();

  return os;
}
