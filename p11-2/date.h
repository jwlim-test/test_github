#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>

class Date {
public:
	Date();
	Date(int year, int month, int day);
	void NextDay(int n = 1);
	bool SetDate(int year, int month, int day);
	int year() const { return year_; }
	int month() const { return month_; }
	int day() const { return day_; }
private:
	// ������ �Ǵ��Ͽ� �־��� ������ �ش��ϴ� ��¥ ��(365 �Ǵ� 366)�� ����.
	static int GetDaysInYear(int year);
	// �ش� ��¥�� �ش� ������ ó��(1�� 1��)���� ��ĥ°������ ���.
	static int ComputeDaysFromYearStart(int year, int month, int day);
	int year_, month_, day_;
};

struct InvalidDateException {
	std::string input_date;
	InvalidDateException(const std::string& str) : input_date(str) {}
};

// yyyy.mm.dd �������� �����.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
std::ostream& operator<<(std::ostream& os, const Date& c);
std::istream& operator>>(std::istream& is, Date& c);
