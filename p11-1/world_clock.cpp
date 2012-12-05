#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>
#include "world_clock.h"

using namespace std;

//clock의 출력이 나오면 구별해서 출력하는 ostream구성! 
ostream& operator<<(ostream& os, const WorldClock& c){
    // 시차가 0이면 즉, set_timezone Seoul,NewYork 아닐시 출력! 
    if(c.time_difference() == 0)
        cout<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    // 시차가 0이 아니고 set_timezone을 했을시 
    // tick을 하더라도 옆에 <+19> 이런 수가 나오게하기위해 
    // 그러나 실제 시간은 변하지않게 하기위해 출력만 더해진값으로 출력! 
    else {
        // 시차를 더했을시 hour만 더해지는데 그 hour가 24를 넘을시 처리  
        if(c.hour()+c.time_difference() >= 24)
            cout<<c.hour()+c.time_difference()-24;
        else
            cout<<c.hour()+c.time_difference();
        cout<<":"<<c.minute()<<":"<<c.second();
        cout<<"  (+"<<c.time_difference()<<")";
    }
    return os;
}
//clock의 입력시 하나의 string을 받아 각 시,분,초로 나누는과정!
istream& operator>>(istream& is, WorldClock& c) {
    string time, h, m, s, last1, last2;
    size_t check1, check2;
    int H,M,S;
    cin>>time;               // 하나의 string을 받아서 ":"가 나올때마다 자른다 
    check1 = time.find(":");
    h = time.substr(0,check1);
    last1 = time.substr(check1+1, time.size());
    check2 = last1.find(":");
    m = last1.substr(0, check2);
    last2 = last1.substr(check2+1, time.size());
    s = last2;                     //자르고난후 각각을 atoi를 이용해 숫자로변경 
    H = atoi(h.c_str());
    M = atoi(m.c_str());
    S = atoi(s.c_str());
    if(c.SetTime(H,M,S) == true){               //그 시,분,초 가 적절한값이면 정상값을 넣고 아니면 throw를한다. 
        WorldClock WC(H,M,S);
        c = WC;
    }
    else {                  // 적절하지않은 시간값이 들어올경우 error메세지 출력 
        InvalidTimeException ITE(time);
        throw ITE;
    }
    return is;
}

map<string, int> WorldClock::timezone_;         //static 변수는 사용하기전에 사용한다고 한번 선언해 주어야한다. 

void WorldClock :: AddTimezoneInfo(const string& city, int diff){
    timezone_[city] = diff;                     //timezone_이라는 map에 그 추가할 도시의 이름의 key에 시차 value 저장! 
}

bool WorldClock :: SetTimezone(const string& timezone){
    if(timezone_.find(timezone) == timezone_.end()){       //만약 timezone_ 이라는 map에 입려한도시이름의 key값이 없을경우 false return 
        return false;
    }
    else {
        time_difference_ = timezone_[timezone];            //있을 경우 시차를 value값으로 변경해준다 변경한 후의 출력은 <+19> 이런것이 옆에붙는다. 
        return true;
    }
}    
