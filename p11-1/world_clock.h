#include <iostream>
#include <string.h>
#include <map>
#include <stdlib.h>
using namespace std;
class WorldClock {
public:
       WorldClock(){time_difference_=0;}
       WorldClock(int hour, int minute, int second): hour_(hour), minute_(minute), second_(second){time_difference_=0;}
       void Tick(int seconds);
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
       bool SetTime(int hour, int minute, int second);
//static bool LoadTimezoneFromFile(const string& file_path);
//ä������ ������ ���� ������� �������
//�ʰ� �Ʒ��� �Լ�(AddTimezoneInfo)�� ����մϴ�.��
       void AddTimezoneInfo(const string& city, int diff);
// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
       bool SetTimezone(const string& timezone);
       int hour() const;
       int minute() const;
       int second() const;
       int time_difference() const { return time_difference_; }
private:
// ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
// Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
        int minute_, second_, hour_;
        int time_difference_;
        map<string, int> timezone_;
};
struct InvalidTimeException {
       string input_time;
       InvalidTimeException(const string& str) : input_time(str) {}
};
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
ostream& operator<<(ostream& os, const WorldClock& c);
istream& operator>>(istream& is, WorldClock& c);
