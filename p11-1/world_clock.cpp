#include "world_clock.h"
istream& operator>>(istream& is, WorldClock& c)
{
         //100���̸� ���� char array 2���� ���� 
         char str[100];
         char str2[100];
         //char pointer ���� 
         char *p;
         //hour,second,minute�� ���Խ�ų �� int �� ���� ���� 
         int ho, sec, min;
         //char array �ϳ��� �Է¹ް�, 2�� copy
         is>>str;
         for(int i=0;i<100;i++)
                 str2[i]=str[i];
         //�Է¹��� str�� �ð�, ��, �ʷ� ������ int ������ �ٲ� ������ ������ ������ �ִ´�. 
         p = strtok( str, ":" );
         ho=atoi(p);
          p = strtok( NULL, ":" ); 
         min=atoi(p);
          p = strtok( NULL, ":" ); 
         sec=atoi(p);
         //�Է¹��� �ð��� ���ǿ� ���� ������� throw 
         if(ho>=24||min>=60||sec>=60)
         {
              InvalidTimeException k(str2);
              throw k;
         }
         //�ð��� �����Ѵ�. 
         c.SetTime(ho, min, sec);
         return is;
}
ostream& operator<<(ostream& os, const WorldClock& c)
{
         int ho;
         int tof=0;
         for(int i=10000;0<i;i--)
         {
                 //�ð��� 24���� Ŭ ��� 24*n(n�� �ڿ���)�� �� 24������ ���ڷ� �����. 
                 if(c.hour()+c.time_difference()>=24*i)
                 {
                              ho=c.hour()+c.time_difference()-24*i;
                              tof=1;
                              break;
                 }
                 //�ð��� 24���� ������� 24*n(n�� �ڿ���) �� ���� 0�̻��� ���ڷ� �����. 
                 else if(c.hour()+c.time_difference()<0-24*i)
                 {
                              ho=c.hour()+c.time_difference()+24*(i+1);
                              tof=1;
                              break;
                 }
         }
 
         if(tof==0)
             ho=c.hour()+c.time_difference();
         //�ð�,��,�ʸ� ����Ѵ�.             
         os<<ho<<":"<<c.minute()<<":"<<c.second();
         if(c.time_difference()!=0)
              os<<" (+"<<c.time_difference()<<")";
         os<<endl;
         return os;
}
bool WorldClock::SetTimezone(const string& timezone){
     map<string, int>:: iterator it;
     //timezone_���� �־��� ������ ã�� �� �ð����� time_difference_�� �ִ´�. 
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
     //timezone_�� city,diff������ �����Ѵ�. 
     timezone_.insert(make_pair(city,diff));
}
bool WorldClock::SetTime(int hour, int minute, int second)
{
     //������ ���� ���� �ð��� ���� ��� false�� return. 
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
