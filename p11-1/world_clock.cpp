#include "world_clock.h"
istream& operator>>(istream& is, WorldClock& c)
{
         //100길이를 갖는 char array 2개를 선언 
         char str[100];
         char str2[100];
         //char pointer 선언 
         char *p;
         //hour,second,minute에 대입시킬 세 int 형 변수 선언 
         int ho, sec, min;
         //char array 하나를 입력받고, 2에 copy
         is>>str;
         for(int i=0;i<100;i++)
                 str2[i]=str[i];
         //입력받은 str을 시간, 분, 초로 나누고 int 형으로 바꿔 위에서 선언한 변수에 넣는다. 
         p = strtok( str, ":" );
         ho=atoi(p);
          p = strtok( NULL, ":" ); 
         min=atoi(p);
          p = strtok( NULL, ":" ); 
         sec=atoi(p);
         //입력받은 시간이 조건에 맞지 않을경우 throw 
         if(ho>=24||min>=60||sec>=60)
         {
              InvalidTimeException k(str2);
              throw k;
         }
         //시간을 셋팅한다. 
         c.SetTime(ho, min, sec);
         return is;
}
ostream& operator<<(ostream& os, const WorldClock& c)
{
         int ho;
         int tof=0;
         for(int i=10000;0<i;i--)
         {
                 //시간이 24보다 클 경우 24*n(n은 자연수)를 빼 24이하의 숫자로 만든다. 
                 if(c.hour()+c.time_difference()>=24*i)
                 {
                              ho=c.hour()+c.time_difference()-24*i;
                              tof=1;
                              break;
                 }
                 //시간이 24보다 잡을경우 24*n(n은 자연수) 을 더해 0이상의 숫자로 만든다. 
                 else if(c.hour()+c.time_difference()<0-24*i)
                 {
                              ho=c.hour()+c.time_difference()+24*(i+1);
                              tof=1;
                              break;
                 }
         }
 
         if(tof==0)
             ho=c.hour()+c.time_difference();
         //시간,분,초를 출력한다.             
         os<<ho<<":"<<c.minute()<<":"<<c.second();
         if(c.time_difference()!=0)
              os<<" (+"<<c.time_difference()<<")";
         os<<endl;
         return os;
}
bool WorldClock::SetTimezone(const string& timezone){
     map<string, int>:: iterator it;
     //timezone_에서 주어진 지역을 찾아 그 시간값을 time_difference_에 넣는다. 
     for(it= timezone_.begin();it!= timezone_.end();it++)
             if(it->first==timezone)
                  break;
     if(it!=timezone_.end()){
           time_difference_=it->second;
     }
     else
         return false;
     return true;        
}
void WorldClock::AddTimezoneInfo(const string& city, int diff)
{
     //timezone_에 city,diff성분을 저장한다. 
     timezone_.insert(make_pair(city,diff));
}
bool WorldClock::SetTime(int hour, int minute, int second)
{
     //정해진 범위 밖의 시간이 들어올 경우 false를 return. 
            if(hour>=24||minute>=60||second>=60)
                 return false;
            else{     
                hour_=hour;
                minute_=minute;
                second_=second;
            }
            return true;
}
void WorldClock::Tick(int seconds)
{
     int sum;
     if(hour_==0)
                hour_=24000;
     sum=hour_*3600+minute_*60+second_;
     sum+=seconds;
     second_=sum% 60;
     minute_=(sum/60)% 60;
     hour_=sum/3600;
}
int WorldClock::hour() const
{
    return hour_;
}
int WorldClock::minute() const
{
    return minute_;
}
int WorldClock::second() const
{
    return second_;
}
