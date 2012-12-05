#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "world_clock.h"

using namespace std;

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
