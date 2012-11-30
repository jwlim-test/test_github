#include <string>
#include <iostream>
#include <stdlib.h>
class Date {
 public:
  Date(){}
  Date(int year, int month, int day):year_(year),month_(month),day_(day){}
  void NextDay(int n=1);
  bool SetDate(int year, int month, int day);
  int year() const;
  int month() const;
  int day() const;
 private:
  static int GetDaysInYear(int year);
  static int ComputeDaysFromYearStart(int year, int month, int day);
  int year_, month_, day_;
};
struct InvalidDateException {
  std::string input_date;
  InvalidDateException(const std::string& str) : input_date(str) {}
};
ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);
