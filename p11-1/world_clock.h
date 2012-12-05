#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>

using namespace std;

class WorldClock {
    public:
        WorldClock() : HOUR(0), MINUTE(0), SECOND(0) { time_difference_ = 0; }     //�⺻ constructor == ��,��,��,������ ��� 0���� ���� 
        WorldClock(int hour, int minute, int second) {                     
            HOUR = hour;
            MINUTE = minute;                    // parametor�� ���� hour,minute,second�� ��,��,�� ����, ������ 0���� ���� 
            SECOND = second;
            time_difference_ = 0;
        }
        void Tick(int seconds = 1){             // dafalut������ 1�� �����س��� parametor�� ���������� ��� 1�� �޾Ƶ鿩 ����Ѵ�. 
            if(seconds == 1){
                SECOND += 1;
                if(SECOND < 0){
                    MINUTE -= 1;
                    SECOND += 60;
                }
                if(MINUTE < 0){
                    HOUR -=1;
                    MINUTE += 60;               //1�� ������ �ʿ��ٰ� 1�� �߰���Ų��. 
                }                               //if�� ������ second -> minute -> hour������ �ؾ��Ѵ� ������ 
                while(HOUR < 0){                //second�� �ø��� �ʰ�60�� ������ minute�� �ø��� ����60�� ������ hour�� �ø��� ������ �Ͽ�����! 
                    HOUR += 24;                 //-���϶��� ������ �������� second�� ������ minute���� -1�ϰ� second +60���ִ� ������� �ؾ��Ѵ�. 
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
            else {                              // tick 1�̾ƴ� �ٸ� ���� ���ð�� hour, minute, second �߰����� �� �������־���Ѵ�. 
                int Plus_h, Plus_m, Plus_s, last1, last2;
                Plus_h = seconds / 3600;        // ���� seconds�� 3600���� ������ hour�̵ǰ� 
                last1 = seconds % 3600;         // 3600���� ���� �������� 
                Plus_m = last1 / 60;            // 60���� ������ minute�̴� 
                last2 = last1 % 60;             // 60���� ���� �������� 
                Plus_s = last2;                 // minute�� �ȴ�. 
            
                HOUR += Plus_h;                 
                MINUTE += Plus_m;               // ���� seconds�� hour,minute,second�� �з��Ѱ��� �������̹Ƿ� 
                SECOND += Plus_s;               // ���� �ð��� ���� �÷������ش�. 
                if(SECOND < 0){
                    MINUTE -= 1;
                    SECOND += 60;               // �̰� ���� ������ second -> minute -> hour���ؼ�  
                }                               // second �����̸� minute���� �ϳ����� second 60�ø���  
                if(MINUTE < 0){
                    HOUR -=1;                   // minute �����̸� hour���� �ϳ����� minute 60�ø���. 
                    MINUTE += 60;
                }
                while(HOUR < 0){
                    HOUR += 24;                 // hour�� �����̸� ����ü���� +24 
                }
                if(SECOND >= 60){
                    MINUTE += 1;                // seocnd�� 60 �̳����� minute �ϳ��߰��ϰ� second -60 
                    SECOND -=60;                // ����������� minute, hour ó�� 
                }
                if(MINUTE >= 60){
                    HOUR += 1;
                    MINUTE -= 60;
                }
                if(HOUR >= 24)
                    HOUR -= 24;
            }    
        }
        bool SetTime(int hour, int minute, int second){   //  hour, minute, second�� �ùٸ� ������ Ȯ�� 
            if(hour >= 24  || minute >= 60 || second >= 60 || hour <0 || minute < 0 ||second < 0)
                return false;
            else {
                HOUR = hour;
                MINUTE = minute;                    // �ùٸ��� �ʴٸ� false return  
                SECOND = second;                    // �ùٸ��ٸ� �װ��� private ������ ����. 
                return true;
            }
        }
        static void AddTimezoneInfo(const string& city, int diff);
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.

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
ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);

