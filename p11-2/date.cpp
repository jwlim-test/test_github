#include "date.h"
#include <string>
using namespace std;
void Date::NextDay(int n ){
    int temp=0;
    temp=ComputeDaysFromYearStart(year_,month_,day_)+n; //당해 1월1일부터 계산후 날짜까이의 일수를 저장하는 변수.
    while(temp<=0){
        temp+=GetDaysInYear(year_-1);
        year_-=1;
    }
    while(temp>=GetDaysInYear(year_+1)){
    if(GetDaysInYear(year_)==366){
        if(temp>365){
            year_+=1;
            temp-=366;
        }
    }
    else{
        if(temp>364){
            year_+=1;
            temp-=365;
        }
    }
    }
    int days_in_month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}; //배열에 각 월마다 일수를 저장
    
    for(int month=1;month<13;++month){
        if(GetDaysInYear(year_)==366){
            if(month!=2){
            if(temp-days_in_month[month]<0){
                day_=temp+1;
                month_=month;
                break;
            }
            }
            if(month==2){
                if(temp-(days_in_month[month]+1)<0){
                    day_=temp+1;
                    month_=month;
                    break;
                }
            }
            temp-=days_in_month[month];
            if(month==2){
                temp-=1;
            }
        }
        else{
            if(temp-days_in_month[month]<0){
                day_=temp+1;
                month_=month;
                break;
            }
            temp-=days_in_month[month];
        }
    }
}
bool Date::SetDate(int year, int month, int day){
    if(month>=13||((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day>31)||((month==4||month==6||month==9||month==11)&&day>=31)){
        return false;
    }
    if(month<=0||day<=0) return false;
    if(GetDaysInYear(year)==366){
        if(month==2&&day>29){
            return false;
        }
    }
    if(GetDaysInYear(year)==365){
        if(month==2&&day>28){
            return false;
        }
    }
    year_=year;
    month_=month;
    day_=day;
    return true;
}
int Date::GetDaysInYear(int year){
    if(year%4==0&&year%100!=0)  return 366;
    else if(year%400==0) return 366;
    else return 365;
}
int Date::ComputeDaysFromYearStart(int year, int month, int day){
    int d=0;
    int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=1;i<month;++i){
        d+=a[i];
        if(i==2&&GetDaysInYear(year)==366){
            d+=1;
        }
    }
    d+=day;
    return d-1;
}
ostream& operator<<(ostream& os, const Date& c){
    os<<c.year()<<"."<<c.month()<<"."<<c.day();
    return os;
}
istream& operator>>(istream& is, Date& c){
    int pos1=-1,pos2=-1,cnt=0; // 연.월.일 사이의 "."의 위치를 저장하는 변수 pos1,pos2. cnt-> 현재까지 "."이 몇개인지 저장
    bool negative=false; //음수판정하는 변수.
    string d;
    is>>d;
    if(d[0]=='-'){
        d.erase(0,1);
        negative=true;
    }
    for(int i=0;i<d.length();++i){
        if(d[i]=='.'&&cnt==0){
            pos1=i;
            cnt+=1;
        }
        if(d[i]=='.'&&cnt==1){
            pos2=i;
        }
    }
    int y=0,m=0,day=0;
    for(int i=0;i<pos1;++i){
        y=(10*y)+d[i]-'0';
    }
    for(int i=pos1+1;i<pos2;++i){
        m=(10*m)+d[i]-'0';
    }
    for(int i=pos2+1;i<d.length();++i){
        day=(10*day)+d[i]-'0';
    }
    if(m<=0||day<=0){
        throw InvalidDateException(d);
        return is;
    }
    if(!c.SetDate(y,m,day)){
        throw InvalidDateException(d);
        return is;
    }
    if((y%4==0&&y%100!=0)||(y%400==0&&y!=y%100!=0)){
        if(m==2&&day>29){
            throw InvalidDateException(d);
            return is;
        }
    }
    else{
        if(m==2&&day>28){
            throw InvalidDateException(d);
            return is;
        }
    }
    if(pos1==-1||pos2==-1){
        throw InvalidDateException(d);
        return is;
    }
    if(negative==true)c.SetDate(-y,m,day);
    else c.SetDate(y,m,day);
    return is;
}
