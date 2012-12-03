#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
class WorldClock {
	public:
		WorldClock();
		WorldClock(int hour, int minute, int second);
		void Tick(int seconds = 1);
		// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
		bool SetTime(int hour, int minute, int second);
		//static bool LoadTimezoneFromFile(const string& file_path); 
		//ä������ ������ ���� ������� �������
		//�ʰ� �Ʒ��� �Լ�(AddTimezoneInfo)�� ����մϴ�.��
		static void AddTimezoneInfo(const std::string& city, int diff);
		// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
		bool SetTimezone(const std::string& timezone);
		int hour() const;
		int minute() const;
		int second() const;
		int time_difference() const { return time_difference_; }
	private:
		int second_time_;
		// ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
		// Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
		int time_difference_;
		static std:: map<std::string, int> timezone_;
};
struct InvalidTimeException {
	std::string input_time;
	InvalidTimeException(const std::string& str) : input_time(str) {}
};
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
std::ostream& operator<<(std::ostream& os, const WorldClock& c);
std::istream& operator>>(std::istream& is, WorldClock& c);  // hh:mm:ss �� �Է¹���.
