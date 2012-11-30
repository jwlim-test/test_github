#include "world_clock.h"
#include <stdio.h>
#include <sstream>


map<string,int> WorldClock::timezone_;

void WorldClock::Tick(int seconds ){
    sec_+=seconds;
    //sec_변수가 음수일 경우 1일에 해당하는 초를 더한다.(날짜는 상관이 없으므로.)
    while(1){
        if(sec_<0){
            sec_+=24*3600;
        }
        else break;
    }
}
bool WorldClock::SetTime(int hour, int minute, int second){
    //인풋에러를 걸러냄.
    if(hour>=24||minute>=60||second>=60||hour<0||minute<0||second<0){
        throw InvalidTimeException(t);
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
    int h;
    h=sec_/3600;
    while(1){
        //h가 24보다 클경우 24보다 작아질때까지 하루의 시간을 뺀다(날짜는 상관 없으므로)
        if(h>=24){
            h-=24;
        }
        else break;
    }
    return h;
}
int WorldClock::minute() const{
    int m;
    m=sec_/60;
    while(1){
        //총 초수를 60으로 나눠 총 몇분인지 구하고, 60이 넘을경우
        //시간으로 넘어갈 것이므로 60보다 작아질때까지 60을 빼준다.
        if(m>=60){
            m-=60;
        }
        else break;
    }
    return m;
}
int WorldClock::second() const{
    return sec_%60;
}
ostream& operator<<(ostream& os, const WorldClock& c){
    string A,B,C;
    int a;
    a=c.time_difference()+c.hour();
    while(1){
        if(a>=24){
            a-=24;
        }
        else if(a<0){
            a+=24;
        }
        else break;
    }
        ostringstream oa,ob,oc;
        oa<<a;
        A=oa.str();
        ob<<c.minute();
        B=ob.str();
        oc<<c.second();
        C=oc.str();
    if(c.time_difference()==0){
        os<<A<<":"<<B<<":"<<C;
        return os;
    }
    else if(c.time_difference()>0){
        os<<A<<":"<<B<<":"<<C<<" (+"<<c.time_difference()<<")";
        return os;
    }
    else if(c.time_difference()<0){
        os<<A<<":"<<B<<":"<<C<<" ("<<c.time_difference()<<")";
        return os;
    }
    return os;
}
istream& operator>>(istream& is, WorldClock& c){
    string temp;
    is>>temp;
    c.t=temp;
    int pos1=-1,pos2=-1,cnt=0;
    for(int i=0;i<temp.length();++i){
        if(temp[i]==':'&&cnt==0){
            pos1=i;
            cnt+=1;
        }
        else if(temp[i]==':'&&cnt==1){
            pos2=i;
            break;
        }
    }
    int s=0,s2=0,s3=0;
    for(int i=0;i<pos1;++i){
        s=10*s+(temp[i]-'0');
    }

    for(int i=pos1+1;i<pos2;++i){
        s2=10*s2+(temp[i]-'0');
    }

    for(int i=pos2+1;i<temp.length();++i){
        s3=10*s3+(temp[i]-'0');
    }
    c.SetTime(s,s2,s3);
    return is;
}

