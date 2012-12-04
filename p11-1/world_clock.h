#include <map>
#include <string>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
class WorldClock 
{
    private:
        // ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
        // Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
        int time_difference_;
        //static map<string, int> timezone_;
        static map<string,int> ig;
        int time_h;
        int time_m;
        int time_s;
    
    public:
        WorldClock();
        WorldClock(int hour, int minute, int second);
        
        void Tick(int seconds);
        // �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
        bool SetTime(int hour, int minute, int second);
        static bool LoadTimezoneFromFile(const string& file_path);
        // �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
        static void AddTimezoneInfo(const string& city, int diff);
        
        bool SetTimezone(const string& timezone);
        int hour() const;
        int minute() const;
        int second() const;
        int time_difference() const { return time_difference_; }
};

struct InvalidTimeException 
{
    string input_time;
    InvalidTimeException(const string& str)
    {
        input_time= str;
    }
    
};
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
ostream& operator<<(ostream& os,  WorldClock& c);
istream& operator>>(istream& is, WorldClock& c); // hh:mm:ss �� �Է¹���.


