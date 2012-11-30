#include "date.h"
bool Date:: SetDate(int year, int month, int day)
{
    
     year_=year;
     month_=month;
     day_=day;
     return true;
}
int Date::GetDaysInYear(int year){
    //받은 년도가 며칠로 구성되어있는지 계산 
          if(year%4==0&&year%100==0&&year%400==0)
          {
              return 366;
          }
          else if(year%4==0&&year%100==0)
          {
               return 365;
          }
          else if(year%4==0)
          {
               return 366;
          }
          else
              return 365;
}
int Date::ComputeDaysFromYearStart(int year, int month, int day){
          //년월일이 정상이 아닌 경우 fail 
          int days=0;
          if(month>12||day>31||1>month||1>day||(month==2&&day>29)||(GetDaysInYear(year)==365&&month==2&&day>28)||(month==4&&day>30)||(month==6&&day>30)||(month==9&&day>30)||(month==11&&day>30))
         {
              return 0;
         }
         //윤년일 경우에 대한 날짜계산 
          if(GetDaysInYear(year)==366){
                     if(month==1)
                          days+=0;
                     else if(month==2)
                          days+=31;
                     else if(month==3)
                          days+=60;
                     else if(month==4)
                          days+=91;
                     else if(month==5)
                          days+=121;
                     else if(month==6)
                          days+=152;
                     else if(month==7)
                          days+=182;
                     else if(month==8)
                          days+=213;
                     else if(month==9)
                          days+=244;
                     else if(month==10)
                          days+=274;
                     else if(month==11)
                          days+=305;
                     else if(month==12)
                          days+=335;
                     days+=day;
                     return days-1;
                     
          }
          //윤년이 아닐때에 대한 윤년계산 
          else if(GetDaysInYear(year)==365){
                     if(month==1)
                          days+=0;
                     else if(month==2)
                          days+=31;
                     else if(month==3)
                          days+=59;
                     else if(month==4)
                          days+=90;
                     else if(month==5)
                          days+=120;
                     else if(month==6)
                          days+=151;
                     else if(month==7)
                          days+=181;
                     else if(month==8)
                          days+=212;
                     else if(month==9)
                          days+=243;
                     else if(month==10)
                          days+=273;
                     else if(month==11)
                          days+=304;
                     else if(month==12)
                          days+=334;
                     days+=day;
                     return days-1;
          }
          return 0;
}
//변화된 날짜계산 
void Date:: NextDay(int n){
     int tof;
     
     if(ComputeDaysFromYearStart(year_, month_, day_)+n<0)
     {
            for(int j=1;j<=12;j++){
                 for(int k=1;k<=31;k++)
                        if(ComputeDaysFromYearStart(year_-1,j,k)==GetDaysInYear(year_-1)+(ComputeDaysFromYearStart(year_, month_, day_)+n)){
                                       year_=year_-1;
                                       month_=j;
                                       day_=k;
                                       tof=100;
                                       break;
                             }
                 if(tof==100)
                             break;
            }
     }
     else if(GetDaysInYear(year_)<=ComputeDaysFromYearStart(year_, month_, day_)+n)
     {
          int sum= ComputeDaysFromYearStart(year_, month_, day_)+n;
          for(int i=0;i<100;i++)
          {
              if(GetDaysInYear(year_+i)<=sum)
                   sum-=GetDaysInYear(year_+i);
              else
                  for(int j=1;j<=12;j++)
                  {
                      for(int k=1;k<=31;k++)
                        if(ComputeDaysFromYearStart(year_+i,j,k)==sum){
                                       year_=year_+i;
                                       month_=j;
                                       day_=k;
                                       tof=100;
                                       break;
                             }
                      if(tof==100)
                                  break;
                  }
              if(tof==100)
                          break;
          }
     }
     else
     {
         for(int j=1;j<=12;j++)
         {
            for(int k=1;k<=31;k++)
                        if(ComputeDaysFromYearStart(year_,j,k)==ComputeDaysFromYearStart(year_, month_, day_)+n){
                                       month_=j;
                                       day_=k;
                                       tof=100;
                                       break;
                             }
            if(tof==100)
                        break;
         }  
     } 
}
ostream& operator<<(ostream& os, const Date& c)
{
          os<<c.year()<<"."<<c.month()<<"."<<c.day();

          return os;
}
istream& operator>>(istream& is, Date& c)
{

         char str[100];
         char str2[100];
         char *p;
         int ye, mo, da;
         int tof;
         is>>str;
         for(int i=0;i<100;i++)
         {
                 str2[i]=str[i];
         }
         p = strtok( str, "." );
         ye=atoi(p);
          p = strtok( NULL, "." ); 
         mo=atoi(p);
          p = strtok( NULL, "." ); 
         da=atoi(p);
         if(ye%4==0&&ye%100==0&&ye%400==0)
              tof= 366;
          else if(ye%4==0&&ye%100==0)
              tof= 365;
          else if(ye%4==0)
               tof= 366;
          else
              tof= 365;
         if(mo>12||da>31||1>mo||1>da||(mo==2&&da>29)||(tof==365&&mo==2&&da>28)||(mo==4&&da>30)||(mo==6&&da>30)||(mo==9&&da>30)||(mo==11&&da>30))
         {
              InvalidDateException k(str2);
              throw k;
         }
         c.SetDate(ye,mo,da);
         return is;
}
