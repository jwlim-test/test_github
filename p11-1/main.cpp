#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
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
    bool OKAY;
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
    OKAY = c.SetTime(H,M,S);
    if(OKAY == true){               //그 시,분,초 가 적절한값이면 정상값을 넣고 아니면 throw를한다. 
        WorldClock WC(H,M,S);
        c = WC;
    }
    else {                  // 적절하지않은 시간값이 들어올경우 error메세지 출력 
        InvalidTimeException ITE(time);
        throw ITE;
    }
    return is;
}

int main(void) {
    WorldClock clock;
    string cmd;
    while (cmd != "quit") {
        cin >> cmd;
        try {    //error가 발생할 수 있는 지역 
            if (cmd == "set") {         // 처음 시각을 설정하는 부분 
                cin >> clock;
                cout << clock << endl;
            } 
            else if (cmd == "tick") {  // 시각을 tick라는 함수를 통해 n초만큼 이동시킨다 
                int tick = 1;
                cin >> tick;
                clock.Tick(tick);
                cout << clock << endl;
            } 
            else if (cmd == "set_timezone") {  // 시각을 timezone에따라 변경된 값을 받아본다 
                string name;
                cin >> name;
                clock.SetTimezone(name);
                cout << clock << endl;
            }
            else if (cmd == "add_timezone_info") {  // timezone을 추가시킨다. 
                string name;
                int time_difference;
                cin >> name >> time_difference;
                WorldClock::AddTimezoneInfo(name, time_difference);
            }
        } 
        catch (InvalidTimeException& e) {       //try 바로밑에 catch를 써줘야함 throw되면 error메세지출력 
            cout << "Invalid time: " << e.input_time << endl;
        }
    }
    return 0;
}
