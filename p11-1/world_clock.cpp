#include "world_clock.h"
#include <stdlib.h>

void WorldClock:: Tick(int seconds){
  if (seconds>=0)
    second_+=seconds;
  else{
    while(seconds<0)
      seconds+=3600*24;
    second_+=seconds;
  }
}

bool WorldClock::SetTime(int hour, int minute, int second){
  if (hour>=60 || minute>=60 || second>=60 || hour<0 || minute<0 || second<0)
    return false;
  second_=hour*3600+minute*60+second;
  return true;
}

void WorldClock::AddTimezoneInfo(const string& city, int diff){
  timezone_.insert(make_pair(city, diff));
}

bool WorldClock::SetTimezone(const string& timezone){
  map<string, int>::const_iterator it=timezone_.find(timezone);
  time_difference_=it->second;
}

int WorldClock::hour() const{
  return second_/3600;
}

int WorldClock::minute() const{
  return (second_-hour()*3600)/60;
}

int WorldClock::second() const{
  return second_%60;
}

ostream& operator<<(ostream& os, const WorldClock& c){
  if (c.time_difference()==0)
    os<<c.hour()%24<<':'<<c.minute()<<':'<<c.second();
  else
    os<<(c.hour()+c.time_difference())%24<<':'<<c.minute()<<':'<<c.second()<<' '
      <<"(+"<<c.time_difference()<<')';

  return os;
}

istream& operator>>(istream& is, WorldClock& c){
  string a;
  int hour, minute, second;
  is>>a;
  int i, j, k;
  for (i=0;i<a.size();i++)
    if (a[i]==':'){
      j=i;
      break;
    }

  for (i=j+1;i<a.size();i++)
    if (a[i]==':'){
      k=i;
      break;
    }

  hour=atoi((a.substr(0,j)).c_str());
  minute=atoi((a.substr(j+1,k)).c_str());
  second=atoi((a.substr(k+1,a.size())).c_str());

  if (hour>=24 || minute>=60 || second>=60 || hour<0 || minute<0 || second<0)
    throw InvalidTimeException(a); 

  c.SetTime(hour, minute, second);
  return is;
}
