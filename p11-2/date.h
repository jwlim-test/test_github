#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>

using namespace std; 

class Date 
{
    public:
        Date();
        Date(int year, int month, int day);
        void NextDay(int n);
        void NextDay();
        bool SetDate(int year, int month, int day);
        int year() const;
        int month() const;
        int day() const;
        int calendar[12];
        
    private:
        
        // ������ �Ǵ��Ͽ� �־��� ������ �ش��ϴ� ��¥ ��(365 �Ǵ� 366)�� ����.
        int GetDaysInYear(int year);
        // �ش� ��¥�� �ش� ������ ó��(1�� 1��)���� ��ĥ°������ ���.
        int ComputeDaysFromYearStart(int year, int month, int day);
        int year_, month_, day_;
};

struct InvalidDateException 
{
    string input_date;
    InvalidDateException(const string& str) : input_date(str) {}
};
// yyyy.mm.dd �������� �����.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);
