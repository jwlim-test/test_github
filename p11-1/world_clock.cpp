#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include "world_clock.h"
using namespace std;
map<string,int> WorldClock::timezone_;

WorldClock::WorldClock(){
  hour_=0;
  minute_=0;
  second_=0;
  time_difference_=0;
}

WorldClock::WorldClock(int hour, int minute, int second){
               hour_=hour;
               minute_=minute;
               second_=second;
               time_difference_=0;
}
void WorldClock::Tick(int seconds){
     int hour,minute,second;
     hour=seconds/3600;
     seconds=seconds%3600;
     minute=seconds/60;
     second=seconds%60;
     //60초 이상 
     if (second_+second>=60){
        second_+=second-60;
        minute_++;
     }
     //0초 이하 
     else if (second_+second<0){
          second_+=second+60;
          minute_--;
     }
     //0~60초 사이     
     else second_+=second;
     //60분 이상 
     if (minute_+minute>=60){
        minute_+=minute-60;
        hour_++;
     }
     //0분 이하 
     else if (minute_+minute<0) {
          minute_+=minute+60;
          hour_--;
     }
     //0~60분 사이 
     else minute_+=minute;
     //24시 이상 
     if (hour_+hour>=24){
        hour_+=hour;
        while (1){
              hour_+=-24;
              if (hour_>=0&&hour_<24) break;
        }
     }
     //0시 이하 
     else if (hour_+hour<0){
          hour_+=hour;
          while (1){
                hour_+=24;
                if (hour_>=0&&hour_<24) break;
          }
     }
     //0~24시 사이 
     else hour_+=hour;
}
bool WorldClock::SetTime(int hour, int minute, int second){
        hour_=hour;
        minute_=minute;
        second_=second;
        return true;
}

bool WorldClock::SetTimezone(const string& timezone){
     int pre_timezone=time_difference_;
     time_difference_=timezone_[timezone];
     //변환한 시간이 0~24시 이내로 들어오도록 
     if ((hour_-pre_timezone+time_difference_)%24<0)
         hour_=(hour_-pre_timezone+time_difference_)%24+24;
     else hour_=(hour_-pre_timezone+time_difference_)%24;
     return true;
}
void WorldClock::AddTimezoneInfo(const string& city, int diff){
     timezone_[city]=diff;
}
int WorldClock::hour() const{
    return hour_;
}
int WorldClock::minute() const{
    return minute_;
}
int WorldClock::second() const{
    return second_;
}

ostream& operator<<(ostream& os, const WorldClock& c){
         cout << c.hour() << ":" << c.minute() << ":" << c.second();
         if (c.time_difference()!=0) cout << " (+" << c.time_difference() << ")";
         return os;
}
istream& operator>>(istream& is, WorldClock& c){
         int hour_,minute_,second_;
         string time, c_time;
         cin >> time;
         c_time=time;
         //string name을 int hour,minute,second로 고침 
         size_t iter=c_time.find(':');
         hour_=atoi((c_time.substr(0,iter)).c_str());
         c_time=c_time.substr(iter+1);
         iter=c_time.find(':');
         minute_=atoi((c_time.substr(0,iter)).c_str());
         second_=atoi((c_time.substr(iter+1)).c_str());
         //예외처리 
         if (hour_>=0&&hour_<24&&minute_>=0&&minute_<60&&second_>=0&&second_<60){
            c.SetTime(hour_,minute_,second_);
         }
         else {
              throw InvalidTimeException(time);
         }
              
            
         
         return is;
}

