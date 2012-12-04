#include <iostream>
#include <string>
#include "date.h"

using namespace std;

int main() {
  Date date;
  string cmd;
  while (cmd != "quit") {
    cin >> cmd;
    try {
    //set 날짜 입력받고  set시킴 
      if (cmd == "set") {
        cin >> date;
        cout << date << endl;
      } else if (cmd == "next_day") { //  다음날의 날짜를 출력하도록 명령 
        date.NextDay();
        cout << date << endl;
      } else if (cmd == "next") {// n일후의 날짜를 출력하도록 명령  
        int n_days = 0;
        cin >> n_days;
        date.NextDay(n_days);
        cout << date << endl;
      }
    } catch (InvalidDateException& e) {
        cout << "Invalid date: " << e.input_date << endl;
    }
  }
  return 0;
}

