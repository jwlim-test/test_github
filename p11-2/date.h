#include<iostream>
#include<string.h>
#include<string>
#include<stdlib.h>
using namespace std;
class Date {
public:
       Date():year_(0),month_(0),day_(0){}
       Date(int year, int month, int day):year_(year),month_(month),day_(day){}
       void NextDay(int n);
       bool SetDate(int year, int month, int day);
       int year() const{return year_;}
       int month() const{return month_;}
       int day() const{return day_;}
private:
// ������ �Ǵ��Ͽ� �־��� ������ �ش��ϴ� ��¥ ��(365 �Ǵ� 366)�� ����.
   static int GetDaysInYear(int year);
// �ش� ��¥�� �ش� ������ ó��(1�� 1��)���� ��ĥ°������ ���.
   static int ComputeDaysFromYearStart(int year, int month, int day);
   int year_, month_, day_;
};
struct InvalidDateException {
       string input_date;
       InvalidDateException(const string& str) : input_date(str) {}
};
// yyyy.mm.dd �������� �����.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);
