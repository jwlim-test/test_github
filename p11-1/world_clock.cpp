#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>
#include "world_clock.h"

using namespace std;

map<string, int> WorldClock::timezone_;

void WorldClock :: AddTimezoneInfo(const string& city, int diff){
    timezone_[city] = diff;
}

bool WorldClock :: SetTimezone(const string& timezone){
    if(timezone_.find(timezone) == timezone_.end()){
        return false;
    }
    else {
        set_HOUR = HOUR + timezone_[timezone];
        if(set_HOUR >= 24)
            set_HOUR -= 24;
        time_difference_ = timezone_[timezone];
        return true;
    }
}    
