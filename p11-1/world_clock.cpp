#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
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
    if(c.SetTime(H,M,S) == true){               //�� ��,��,�� �� �����Ѱ��̸� ������ �ְ� �ƴϸ� throw���Ѵ�. 
        WorldClock WC(H,M,S);
        c = WC;
    }
    else {                  // ������������ �ð����� ���ð�� error�޼��� ��� 
        InvalidTimeException ITE(time);
        throw ITE;
    }
    return is;
}

map<string, int> WorldClock::timezone_;         //static ������ ����ϱ����� ����Ѵٰ� �ѹ� ������ �־���Ѵ�. 

void WorldClock :: AddTimezoneInfo(const string& city, int diff){
    timezone_[city] = diff;                     //timezone_�̶�� map�� �� �߰��� ������ �̸��� key�� ���� value ����! 
}

bool WorldClock :: SetTimezone(const string& timezone){
    if(timezone_.find(timezone) == timezone_.end()){       //���� timezone_ �̶�� map�� �Է��ѵ����̸��� key���� ������� false return 
        return false;
    }
    else {
        time_difference_ = timezone_[timezone];            //���� ��� ������ value������ �������ش� ������ ���� ����� <+19> �̷����� �����ٴ´�. 
        return true;
    }
}    
