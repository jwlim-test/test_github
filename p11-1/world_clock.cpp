#include "world_clock.h"

void WorldClock::Tick(int second){
    
    int NowTimeSecond_=hour_*3600+minute_*60+second_; //현재 설정된 시간을 전부 초로 환산 
    
    NowTimeSecond_+=second; 

    while(NowTimeSecond_<0) //계산된 시간이 음수인 경우 하루 전으로 시간을 추가해준다 
        NowTimeSecond_+=24*3600;
    
    while(NowTimeSecond_>24*3600) //계산된 시간이 하루가 넘는 경우 하루의 시간을 빼준다 
        NowTimeSecond_-=24*3600;
        
    hour_=(NowTimeSecond_/3600)%24; //시간은 3600초로 나눈 몫을 24시간으로 다시 나누어 나머지가 된다 
    NowTimeSecond_%=3600;
    minute_=NowTimeSecond_/60; //분은 60으로 나눈 몫이다 
    second_=NowTimeSecond_%60; //초는 60으로 나눈 나머지이다 

    
}

bool WorldClock::SetTime(int hour, int minute, int second){
    
    //시간이 잘못 들어올 경우에 false 를 리턴시켜서 InvalidTimeException을 발생시킨다 
    if(hour>=24 || hour<0) return false; 
    else if(minute>=60 || minute<0) return false;
    else if(second>=60 || second<0) return false;
    
    time_difference_=0;
    hour_=hour;
    minute_=minute;
    second_=second;
    
    return true;
}


void WorldClock::AddTimezoneInfo(const string& city, int diff){     
            //시간차가 생기는 지역과 그 시차를 timezone_라는  map에 저장 
            timezone_[city]=diff;
        
        
        }
        
bool WorldClock::SetTimezone(const string& timezone){
    
    (*this).Tick(-time_difference_*3600); //시차가 0이었던 초기시간으로 설정 
    if(timezone!="GMT" && timezone_[timezone]==0) //timezone이 이전에 입력되었는지 확인 
        return false;
        
    time_difference_=timezone_[timezone]; //시차를 그 지역의 시차로 설정 
    
    
    
    (*this).Tick(time_difference_*3600); //그 시차만큼 Tick 함수 호출 
    return true;

}

ostream& operator<<(ostream& os, const WorldClock& c){
    if(c.time_difference()==0) //시차가 0일 경우 그냥 출력하지만 0이 아닐경우 (+ )로 시차를 표시 
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    else
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second()
        <<" (+"<<c.time_difference()<<")";
        
    return os;
}

istream& operator >>(istream& is, WorldClock& c){
    //입력받을 char형 배열을 생성 
    char time[1000];
    
    is>>time;
    //입력받아서 제대로 입력되었는지 확인하고 입력이 안됬을 경우  InvalidTimeException를 실행하기위한 문자열 생성 
    string time_;
    for(int i=0; time[i]!='\0'; i++) time_.push_back(time[i]);
    
    //시,분,초를 각각 잘라서 제대로 맞는지 확인 
    char* ptr;
    ptr = strtok( time, ":");
    int hour = atoi(ptr);
    ptr = strtok( NULL,":");
    int minute = atoi(ptr);
    ptr = strtok( NULL,":");
    int second = atoi(ptr);
    
    //맞지 않을경우 InvalidTimeException를 실행 
    if(!c.SetTime(hour,minute,second)) throw InvalidTimeException(time_);
    
    return is;
}
