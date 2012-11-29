#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "world_clock.h"

using namespace std;

//clock�� ����� ������ �����ؼ� ����ϴ� ostream����! 
ostream& operator<<(ostream& os, const WorldClock& c){
    // ������ 0�̸� ��, set_timezone Seoul,NewYork �ƴҽ� ���! 
    if(c.time_difference() == 0)
        cout<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    // ������ 0�� �ƴϰ� set_timezone�� ������ 
    // tick�� �ϴ��� ���� <+19> �̷� ���� �������ϱ����� 
    // �׷��� ���� �ð��� �������ʰ� �ϱ����� ��¸� ������������ ���! 
    else {
        // ������ �������� hour�� �������µ� �� hour�� 24�� ������ ó��  
        if(c.hour()+c.time_difference() >= 24)
            cout<<c.hour()+c.time_difference()-24;
        else
            cout<<c.hour()+c.time_difference();
        cout<<":"<<c.minute()<<":"<<c.second();
        cout<<"  (+"<<c.time_difference()<<")";
    }
    return os;
}
//clock�� �Է½� �ϳ��� string�� �޾� �� ��,��,�ʷ� �����°���!
istream& operator>>(istream& is, WorldClock& c) {
    string time, h, m, s, last1, last2;
    size_t check1, check2;
    int H,M,S;
    bool OKAY;
    cin>>time;               // �ϳ��� string�� �޾Ƽ� ":"�� ���ö����� �ڸ��� 
    check1 = time.find(":");
    h = time.substr(0,check1);
    last1 = time.substr(check1+1, time.size());
    check2 = last1.find(":");
    m = last1.substr(0, check2);
    last2 = last1.substr(check2+1, time.size());
    s = last2;                     //�ڸ����� ������ atoi�� �̿��� ���ڷκ��� 
    H = atoi(h.c_str());
    M = atoi(m.c_str());
    S = atoi(s.c_str());
    OKAY = c.SetTime(H,M,S);
    if(OKAY == true){               //�� ��,��,�� �� �����Ѱ��̸� ������ �ְ� �ƴϸ� throw���Ѵ�. 
        WorldClock WC(H,M,S);
        c = WC;
    }
    else {                  // ������������ �ð����� ���ð�� error�޼��� ��� 
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
        try {    //error�� �߻��� �� �ִ� ���� 
            if (cmd == "set") {         // ó�� �ð��� �����ϴ� �κ� 
                cin >> clock;
                cout << clock << endl;
            } 
            else if (cmd == "tick") {  // �ð��� tick��� �Լ��� ���� n�ʸ�ŭ �̵���Ų�� 
                int tick = 1;
                cin >> tick;
                clock.Tick(tick);
                cout << clock << endl;
            } 
            else if (cmd == "set_timezone") {  // �ð��� timezone������ ����� ���� �޾ƺ��� 
                string name;
                cin >> name;
                clock.SetTimezone(name);
                cout << clock << endl;
            }
            else if (cmd == "add_timezone_info") {  // timezone�� �߰���Ų��. 
                string name;
                int time_difference;
                cin >> name >> time_difference;
                WorldClock::AddTimezoneInfo(name, time_difference);
            }
        } 
        catch (InvalidTimeException& e) {       //try �ٷιؿ� catch�� ������� throw�Ǹ� error�޼������ 
            cout << "Invalid time: " << e.input_time << endl;
        }
    }
    return 0;
}
