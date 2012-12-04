#include "date.h"

using namespace std;

ostream& operator<<(ostream& os, const Date& c){
  os<<c.year()<<"."<<c.month()<<"."<<c.day();
  return os;
}

istream& operator>>(istream& is, Date& c){
  string date,year,month,day;
  int leng,index[2],count= 0,y,m,d;
  is>>date;
  leng = date.length();
  for(int i=0; i<leng; i++){
    if(date[i] == '.'){
      index[count] = i;
      count++;
    }
  }
 //year month day를 .을 기준으로 string으로 나누고 int 로 변환해서 set할수있는지 판단후 set시킴 
  year = date[0];
  for(int i=1; i<index[0]; i++){
     year += date[i];
  }
  month = date[index[0]+1];
  for(int i=index[0]+2; i<index[1]; i++){
     month += date[i];
  }
  day = date[index[1]+1];
  for(int i=index[1]+2; i<leng; i++){
     day +=date[i];
  }
  y = atoi(year.c_str());
  m = atoi(month.c_str());
  d = atoi(day.c_str());

  bool jud = c.SetDate(y,m,d);
  //setdate에서 false를 리턴받으면 예외처리 
  if(jud == false){
    throw InvalidDateException(date);
  }
  return is;
}

bool Date::SetDate(int year, int month, int day){
  int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 1월에서 12월의 날짜를 배열로 저장 
  //윤년일경우 2월달의 날짜를 29일로 변환시킴 
  if(year%4==0 && year%100!=0 || year%400 == 0){
    days_in_month[2] = 29;
  }
  //옳은 날짜인지 판단하고 set 시킨다 
  if(month >=1 && month<13 && day<=days_in_month[month] && day >=1){
    year_ = year;
    month_ = month;
    day_ = day;
    return true;
  }
  else
    return false;
}

void Date::NextDay(int n){
   int days = 0;
  //현재 날짜가 지금년도에서 몇일째인지 계산후 n을더해  days를 구함 
   days = ComputeDaysFromYearStart(year_, month_, day_)+n;
   while(days<=0){//day가 음수인경우 양수가 될떄까지 연도를 감소하고 해당년도의 날짜수를 days에 더한다 
       year_ = year_ -1;
       days += GetDaysInYear(year_);
   }
            
   while(days>GetDaysInYear(year_)){//days값이 해당년도의 날짜수보다 클경우 해당년도의 날짜수를 빼고 연도를 증가 
       days -= GetDaysInYear(year_);
       year_ = year_ + 1;
   }
              
   int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   if(GetDaysInYear(year_) == 366)
     days_in_month[2] = 29;
   
   month_ = 1;
   for(int i=1; i<13; i++){ // 해당년도에서 1월부터 그달의 날짜수를 빼면서 월을 증가 
     if(days_in_month[i]<days){
       days -= days_in_month[i];
       month_++;
     }
     else//나머지는 일에  set 
       day_ = days;
   }
}

// 받은 날짜가 현재년도에서 몇일째인지 리턴하는함수 
int Date::ComputeDaysFromYearStart(int year, int month, int day){
    int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year%4==0 && year%100!=0 || year%400==0){
      days_in_month[2] = 29;
    }
    
    int totalday=0;
    for(int i=1; i<month; i++){ //month 전달 까지의 일수를 다 더함 
      totalday +=days_in_month[i];
    }
    totalday+= day;//마지막으로 현재 day를 더함 
    return totalday;
}

//윤년인지 아닌지판단해서 365일인지 366일인지 리턴시키는함수 
int Date::GetDaysInYear(int year){
   if(year%4==0 && year%100!=0){
     return 366;
            }
   if(year%400==0){
     return 366;
   }
   else
     return 365;
}


