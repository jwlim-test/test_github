#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>
#include "world_clock.h"

using namespace std;

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
