#include <iostream>
#include <string>

using namespace std;

class Date{
  public:
    Date();
    Date(int year, int month, int day);

    void NextDay(int n=1);
    bool SetDate(int year, int month, int day);

    int year() const;
    int month() const;
    int day() const;

  private:
    int GetDaysInYear(int year);

    int ComputeDaysFromYearStart(int year, int month, int day);

    int year_, month_, day_;
};

struct InvalidDateException{
  string input_date;
  InvalidDateException(const string& str):input_date(str){}
};

ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);
