#include "date.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
Date::Date(){
  year_=0;
  month_=0;
  day_=0;
}
Date::Date(int year, int month, int day){
  year_=year;
  month_=month;
  day_=day;
}
void Date::NextDay(int n){
     int month=1;
     int day=1;
     int total_days=ComputeDaysFromYearStart(year_,month_,day_);
     total_days+=n;
     //총 일수가 양수 
     if (total_days>0){
        while (total_days-GetDaysInYear(year_)>0){
              total_days-=GetDaysInYear(year_);
              year_++;
        }
     }
     //총 일수가 음수 
     else{
          while (total_days<=0){
                total_days+=GetDaysInYear(year_-1);
                year_--;
          }
     }

     while (1){
           //1월 
           if (total_days>31){
                        day=total_days;
                        break;
           if (total_days>31){
              month++;
              total_days-=31;
           }
           else {
                day=total_days;
                break;
           } 
        
           //4월 
           if (total_days>30){
              month++;
              total_days-=30;
           }
           else {
                day=total_days;
                break;
           }
        
           //5월
           if (total_days>31){
              month++;
              total_days-=31;
           }
           else {
                day=total_days;
                break;
           } 
        
           //6월 
           if (total_days>30){
                day=total_days;
                break;
           if (total_days>30){
              month++;
              total_days-=30;
           }
           else {
                day=total_days;
                break;
           } 
        
           //10월 
           if (total_days>31){
              month++;
              total_days-=31;
           }
           else {
                day=total_days;
                break;
           } 
        
           //11월 
           if (total_days>30){
              month++;
              total_days-=30;
           }
           else {
                day=total_days;
                break;
           } 
        
           //12월 
           if (total_days>31){
              month++;
              total_days-=31;
           }
           else {
                day=total_days;
                break;
           }
     } 
     month_=month;
     day_=day;   
}

bool Date::SetDate(int year, int month, int day){
     if (year<0||month<0||month>12||day<0) return false;
     else {
          if (month==1||month==3||month==5||month==7||month==8||month==10||month==12){
             if (day>31) return false;
          }
          else if (month==4||month==6||month==9||month==11){
               if (day>30) return false;
          }
          else if (month==2){
               if (GetDaysInYear(year)==366){
                  if (day>29) return false;
               }
               else{
                    if (day>28) return false;
               }
          }
     }
     year_=year;
     month_=month;
     day_=day;
     return true;              
}

int Date::year() const{
    return year_;
}
int Date::month() const{
    return month_;

}
int Date::day() const{
    return day_;

}
int Date::GetDaysInYear(int year){
    if (year%400==0) return 366;
    if (year%100==0) return 365;
    if (year%4==0) return 366;
    else return 365;
}

int Date::ComputeDaysFromYearStart(int year, int month, int day){
    int total_days=day;
    //1월부터 12월까지 각 달의 일 수를 더함 
    if (month>=2) total_days+=31;
    else return total_days;
    if (month>=3){
       if (GetDaysInYear(year)==366) total_days+=29;
       else total_days+=28;
    }
    else return total_days;
    if (month>=4) total_days+=31;
    else return total_days;
    if (month>=5) total_days+=30;
    else return total_days;
    if (month>=6) total_days+=31;
    else return total_days;
    if (month>=7) total_days+=30;
    else return total_days;
    if (month>=8) total_days+=31;
    else return total_days;
    if (month>=9) total_days+=31;
    else return total_days;
    if (month>=10) total_days+=30;
    else return total_days;
    if (month>=11) total_days+=31;
    else return total_days;
    if (month>=12) total_days+=30;
    return total_days;
}
ostream& operator<<(ostream& os, const Date& c){
         cout << c.year() << "." << c.month() << "." << c.day();
         return os;
}
istream& operator>>(istream& is, Date& c){
         string date,c_date;
         int year,month,day;
         cin >> date;
         c_date=date;
         size_t iter=c_date.find(".");
         year=atoi((c_date.substr(0,iter)).c_str());
         c_date=c_date.substr(iter+1);
         iter=c_date.find(".");
         month=atoi((c_date.substr(0,iter)).c_str());
         day=atoi((c_date.substr(iter+1)).c_str());
         //예외처리 
         if (!c.SetDate(year,month,day)){
            throw InvalidDateException(date);
         }
         
         return is;
}
           } 
        
           //9월 
              total_days-=31;
           }
           else {
              month++;
              total_days-=30;
           }
           //8월 
           if (total_days>31){
              month++;
           else {
                day=total_days;
        
                break;
                break;
           } 
           }
           else {
                day=total_days;
           } 
        
           //7월 
           if (total_days>31){
              month++;
              total_days-=31;
                   } 
           }
           //3월 
              month++;
              total_days-=31;
                      month++;
                      total_days-=29;
                   }
                   else {
           }
           else if (GetDaysInYear(year_)==366){
                   if (total_days>28){
           else {
              }
           }
                day=total_days;
                break;
           }
              else {
                   day=total_days;
                   break;
           //2월 
                 total_days-=28;
              }
           if (GetDaysInYear(year_)==365){        
              if (total_days>28){
                 month++;

