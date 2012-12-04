#include "world_clock.h"
#include <cstdlib>

using namespace std;

map<string,int> WorldClock::timezone_;

//시간이 잘못되었는지 체크하고 잘되었으면 SET하고  잘못되면  false를  return 
bool WorldClock::SetTime(int hour, int minute, int second){ 
  if(hour>=0 && hour<24 && minute >=0 && minute <60 && second >=0 && second <60){
    hour_ = hour;
    minute_ = minute;
    second_ = second;
    return true;
  }
  else
    return false;
}

//원래 시간을 초로 바꾼후 seconds를 더해서 hour_,minute, second 계산 
void WorldClock::Tick(int seconds){
  int sec=(3600*hour_)+(60*minute_)+second_;
  sec+=seconds;
  while(sec<0){//sec가 0보다작을경우 하루의 초를 더해서 양수로만듬 
      sec+=3600*24;
  }
  hour_=(sec/3600)%24; // hour은 3600초로 나눈 몫
  minute_=(sec%3600)/60;//minute은 60초로 나눈 몫
  second_=sec%60;//second는 60초로 나눈 나머지
}

//도시이름과 시차를 map에 저장한다 
void WorldClock::AddTimezoneInfo(const string& city, int diff){
    timezone_[city] = diff;
}

istream& operator>>(istream& is, WorldClock& c){
  string time,str1,str2,str3;
  int length, index[2],count=0, hour, min, sec;

  is>>time;
  length = time.length();

  for(int i=0; i<length; i++){
     if(time[i] == ':'){
       index[count] = i;
       count++;
     }
  }
 //string으로 받은 time을 .으로 구분해서 int 로 변환 
  str1 = time[0];
  for(int i=1; i<index[0]; i++){
    str1 += time[i];
  }
  str2 = time[index[0]+1];
  for(int i=index[0]+2; i<index[1]; i++){
    str2 += time[i];
  }
  str3 = time[index[1]+1];
  for(int i=index[1]+2; i<length; i++){
     str3 += time[i];
  }

  hour = atoi(str1.c_str());
  min = atoi(str2.c_str());
  sec = atoi(str3.c_str());

  bool jud = c.SetTime(hour, min, sec);
 //SetTime에서 false를 리턴받으면 예외처리 
  if(jud == false){
    throw InvalidTimeException(time);
  }
  return is;
}

ostream& operator<<(ostream& os, const WorldClock& c){
  int hour;
  if(c.time_difference() == 0){
    os<<c.hour()<<":"<<c.minute()<<":"<<c.second();
  }
  else{
    hour=(c.hour()+c.time_difference())%24;
    os<<hour<<":"<<c.minute()<<":"<<c.second()<<" (+"<<c.time_difference()<<")";
  }
  return os;
  
}

//timezone이 있는지 확인하고 없으면 false리턴 
bool WorldClock::SetTimezone(const string& timezone){
    if(timezone_.find(timezone) != timezone_.end()){
      time_difference_ = timezone_[timezone];
    }
    else
      false;
}

