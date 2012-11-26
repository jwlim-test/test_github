#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>

using namespace std;

class WorldClock {
    public:
        WorldClock() : HOUR(0), MINUTE(0), SECOND(0) { }
        WorldClock(int hour, int minute, int second) {
            HOUR = hour;
            MINUTE = minute;
            SECOND = second;
        }
        void Tick(int seconds = 1){
            if(seconds == 1){
                SECOND += 1;
            }
            else {
                int Plus_h, Plus_m, Plus_s, last1, last2;
                Plus_h = seconds / 3600;
                last1 = seconds % 3600;
                Plus_m = last1 / 60;
                last2 = last1 % 60;
                Plus_s = last2;
            
                HOUR += Plus_h;
                MINUTE += Plus_m;
                SECOND += Plus_s;
                
                if(SECOND < 0){
                    MINUTE -= 1;
                    SECOND += 60;
                }
                if(MINUTE < 0){
                    HOUR -=1;
                    MINUTE += 60;
                }
                if(HOUR < 0){
                    HOUR += 24; 
                }
                if(HOUR >= 24)
                    HOUR -= 24;
                if(MINUTE >= 60){
                    HOUR += 1;
                    MINUTE -= 60;
                }
                if(SECOND >= 60){
                    MINUTE += 1;
                    SECOND -=60;
                }
            }    
        }
        bool SetTime(int hour, int minute, int second){
            if(hour >= 24  || minute >= 60 || second >= 60)
                return false;
            else {
                HOUR = hour;
                MINUTE = minute;
                SECOND = second;
                return true;
            }
        }
        static void AddTimezoneInfo(const string& city, int diff);
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
        WorldClock SET(){
            WorldClock WC(set_HOUR, MINUTE, SECOND);
            return WC;
        }
        bool SetTimezone(const string& timezone);   
        int hour() const { return HOUR; }
        int minute() const { return MINUTE; }
        int second() const { return SECOND; }
        int time_difference() const { return time_difference_; }
    private:
        int SECOND, MINUTE, HOUR;
        int set_HOUR;
// ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
// Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
        int time_difference_;
        static map<string, int> timezone_;
};

struct InvalidTimeException {
    string input_time;
    InvalidTimeException(const string& str) : input_time(str) {}
};
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.


