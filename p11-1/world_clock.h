#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

class WorldClock {
public:
	WorldClock();
	WorldClock(int hour, int minute, int second);
	void Tick(int seconds = 1);
	// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
	bool SetTime(int hour, int minute, int second);
	static void AddTimezoneInfo(const std::string& city, int diff);
	// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
	bool SetTimezone(const std::string& timezone);
	int hour() const { return hour_; }
	int minute() const { return minute_; }
	int second() const { return second_; }
	int time_difference() const { return time_difference_; }
private:
	// ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
	// Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
	int time_difference_;
	static std::map<std::string, int> timezone_;
	int hour_, minute_, second_;
};

struct InvalidTimeException {
	std::string input_time;
	InvalidTimeException(const std::string& str) : input_time(str) {}
};
// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx) �������� ������ ǥ��.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
std::ostream& operator<<(std::ostream& os, const WorldClock& c);
std::istream& operator>>(std::istream& is, WorldClock& c);  // hh:mm:ss �� �Է¹���.
