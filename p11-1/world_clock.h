#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>

using namespace std;

class WorldClock {
    public:
        WorldClock() : HOUR(0), MINUTE(0), SECOND(0) { time_difference_ = 0; }     //기본 constructor == 시,분,초,시차를 모두 0으로 셋팅 
        WorldClock(int hour, int minute, int second) {                     
            HOUR = hour;
            MINUTE = minute;                    // parametor로 받은 hour,minute,second로 시,분,초 셋팅, 시차는 0으로 셋팅 
            SECOND = second;
            time_difference_ = 0;
        }
        void Tick(int seconds = 1){             // dafalut값으로 1을 설정해놓고 parametor가 들어오지않을 경우 1로 받아들여 계산한다. 
            if(seconds == 1){
                SECOND += 1;
                if(SECOND < 0){
                    MINUTE -= 1;
                    SECOND += 60;
                }
                if(MINUTE < 0){
                    HOUR -=1;
                    MINUTE += 60;               //1이 들어오면 초에다가 1을 추가시킨다. 
                }                               //if문 순서가 second -> minute -> hour순으로 해야한다 이유는 
                while(HOUR < 0){                //second를 올리고 초가60이 넘으면 minute를 올리고 분이60이 넘으면 hour를 올리는 식으로 하여야함! 
                    HOUR += 24;                 //-값일때도 순서는 같은것이 second가 음수면 minute에서 -1하고 second +60해주는 방식으로 해야한다. 
                }                                
                if(SECOND >= 60){
                    MINUTE += 1;
                    SECOND -=60;
                }
                if(MINUTE >= 60){
                    HOUR += 1;
                    MINUTE -= 60;
                }
                if(HOUR >= 24)
                    HOUR -= 24;
            }
            else {                              // tick 1이아닌 다른 값이 들어올경우 hour, minute, second 추가값을 다 나누어주어야한다. 
                int Plus_h, Plus_m, Plus_s, last1, last2;
                Plus_h = seconds / 3600;        // 받은 seconds를 3600으로 나누면 hour이되고 
                last1 = seconds % 3600;         // 3600으로 나눈 나머지를 
                Plus_m = last1 / 60;            // 60으로 나누면 minute이다 
                last2 = last1 % 60;             // 60으로 나눈 나머지가 
                Plus_s = last2;                 // minute가 된다. 
            
                HOUR += Plus_h;                 
                MINUTE += Plus_m;               // 들어온 seconds를 hour,minute,second로 분류한것은 증가값이므로 
                SECOND += Plus_s;               // 원래 시간에 각각 플러스해준다. 
                if(SECOND < 0){
                    MINUTE -= 1;
                    SECOND += 60;               // 이것 또한 순서를 second -> minute -> hour로해서  
                }                               // second 음수이면 minute에서 하나빼고 second 60올리고  
                if(MINUTE < 0){
                    HOUR -=1;                   // minute 음수이면 hour에서 하나빼고 minute 60올린다. 
                    MINUTE += 60;
                }
                while(HOUR < 0){
                    HOUR += 24;                 // hour가 음수이면 그자체에서 +24 
                }
                if(SECOND >= 60){
                    MINUTE += 1;                // seocnd가 60 이넘으면 minute 하나추가하고 second -60 
                    SECOND -=60;                // 같은방식으로 minute, hour 처리 
                }
                if(MINUTE >= 60){
                    HOUR += 1;
                    MINUTE -= 60;
                }
                if(HOUR >= 24)
                    HOUR -= 24;
            }    
        }
        bool SetTime(int hour, int minute, int second){   //  hour, minute, second가 올바른 값인지 확인 
            if(hour >= 24  || minute >= 60 || second >= 60 || hour <0 || minute < 0 ||second < 0)
                return false;
            else {
                HOUR = hour;
                MINUTE = minute;                    // 올바르지 않다면 false return  
                SECOND = second;                    // 올바르다면 그값을 private 변수에 저장. 
                return true;
            }
        }
        static void AddTimezoneInfo(const string& city, int diff);
// 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.

        bool SetTimezone(const string& timezone);   
        int hour() const { return HOUR; }
        int minute() const { return MINUTE; }
        int second() const { return SECOND; }
        int time_difference() const { return time_difference_; }
    private:
        int SECOND, MINUTE, HOUR;
        int set_HOUR;
// 여기에 시각 관련 멤버 변수 정의. (GMT 시간을 사용)
// Timezone 관련 정보는 아래 변수에 저장. 시차는 시간 단위로만 계산.
        int time_difference_;
        static map<string, int> timezone_;
};

struct InvalidTimeException {
    string input_time;
    InvalidTimeException(const string& str) : input_time(str) {}
};
// hh:mm:ss 형식으로 입출력. 표준시가 아닌 경우 (+xx) 형식으로 시차를 표시.
ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);

