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
		// 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
		bool SetTime(int hour, int minute, int second);
		//static bool LoadTimezoneFromFile(const string& file_path); 
		//채점서버 문제로 파일 입출력을 사용하지
		//않고 아래의 함수(AddTimezoneInfo)를 사용합니다.↓
		static void AddTimezoneInfo(const std::string& city, int diff);
		// 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
		bool SetTimezone(const std::string& timezone);
		int hour() const;
		int minute() const;
		int second() const;
		int time_difference() const { return time_difference_; }
	private:
		int second_time_;
		// 여기에 시각 관련 멤버 변수 정의. (GMT 시간을 사용)
		// Timezone 관련 정보는 아래 변수에 저장. 시차는 시간 단위로만 계산.
		int time_difference_;
		static std:: map<std::string, int> timezone_;
};
struct InvalidTimeException {
	std::string input_time;
	InvalidTimeException(const std::string& str) : input_time(str) {}
};
// hh:mm:ss 형식으로 입출력. 표준시가 아닌 경우 (+xx) 형식으로 시차를 표시.
// 사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.
std::ostream& operator<<(std::ostream& os, const WorldClock& c);
std::istream& operator>>(std::istream& is, WorldClock& c);  // hh:mm:ss 로 입력받음.
