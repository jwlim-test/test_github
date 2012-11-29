#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>
#include "world_clock.h"

using namespace std;

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
