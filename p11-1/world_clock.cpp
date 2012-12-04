#include "world_clock.h"
#include <stdio.h>
#include <sstream>
#include <cstdlib>

map<string,int> WorldClock::timezone_;

void WorldClock::Tick(int seconds ){
    sec_+=seconds;
    //sec_▒▒▒▒▒▒ ▒▒▒▒▒▒ ▒▒▒ 1▒Ͽ▒ ▒ش▒▒ϴ▒ ▒ʸ▒ ▒▒▒Ѵ▒.(▒▒¥▒▒ ▒▒▒▒▒ ▒▒▒▒▒Ƿ▒.)
    while(sec_<0) sec_+=24*3600;
}

bool WorldClock::SetTime(int hour, int minute, int second){
    //▒▒ǲ▒▒▒▒▒▒ ▒ɷ▒▒▒.
    if(hour>=24||minute>=60||second>=60||hour<0||minute<0||second<0){
        return false;
    }
    else{
        sec_=(3600*hour)+(60*minute)+second;
        return true;
    }
}

void WorldClock::AddTimezoneInfo(const string& city, int diff){
    timezone_[city]=diff;
}

bool WorldClock::SetTimezone(const string& timezone){
    if(timezone_.find(timezone)!=timezone_.end()){
        time_difference_=timezone_[timezone];
        return true;
    }
    else{
        return false;
    }
}

int WorldClock::hour() const{
  return (sec_/3600)%24;
}

int WorldClock::minute() const{
    int m;
    m=sec_/60;
    while(1){
        //▒▒ ▒ʼ▒▒▒ 60▒▒▒▒ ▒▒▒▒ ▒▒ ▒▒▒▒▒▒▒ ▒▒▒ϰ▒, 60▒▒ ▒▒▒▒▒▒▒
        //▒ð▒▒▒▒▒ ▒Ѿ ▒▒▒̹Ƿ▒ 60▒▒▒▒ ▒۾▒▒▒▒▒▒▒▒▒ 60▒▒ ▒▒▒ش▒.
        if(m>=60){
            m-=60;
        }
        else break;
    }
    return m;
}


