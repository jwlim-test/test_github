#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "world_clock.h"

using namespace std;

ostream& operator<<(ostream& os, const WorldClock& c){
    
    cout<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    return os;
}

istream& operator>>(istream& is, WorldClock& c) {
    string time, h, m, s, last1, last2;
    size_t check1, check2;
    int H,M,S;
    bool OKAY;
    cin>>time;
    check1 = time.find(":");
    h = time.substr(0,check1);
    last1 = time.substr(check1+1, time.size());
    check2 = last1.find(":");
    m = last1.substr(0, check2);
    last2 = last1.substr(check2+1, time.size());
    s = last2;
    H = atoi(h.c_str());
    M = atoi(m.c_str());
    S = atoi(s.c_str());
    OKAY = c.SetTime(H,M,S);
    if(OKAY == true){
        WorldClock WC(H,M,S);
        c = WC;
    }
    else {
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
        try {
            if (cmd == "set") {
                cin >> clock;
                cout << clock << endl;
            } 
            else if (cmd == "tick") {
                int tick = 1;
                cin >> tick;
                clock.Tick(tick);
                cout << clock << endl;
            } 
            else if (cmd == "set_timezone") {
                string name;
                cin >> name;
                clock.SetTimezone(name);
                WorldClock set;
                set = clock.SET();
                cout << set <<" ";
                if(clock.time_difference() == 0)
                    cout<<endl;
                else
                    cout<<"(+"<<clock.time_difference()<<")"<<endl;
            }
            else if (cmd == "add_timezone_info") {
                string name;
                int time_difference;
                cin >> name >> time_difference;
                WorldClock::AddTimezoneInfo(name, time_difference);
            }
        } 
        catch (InvalidTimeException& e) {
            cout << "Invalid time: " << e.input_time << endl;
        }
    }
    return 0;
}
