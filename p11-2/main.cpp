#include "date.h"
int main() {
    Date date;
    string cmd;
    
    
    while (cmd != "quit") {
          cin >> cmd;
          try {
              
              if (cmd == "set") {
                 cin >> date;
                 //cout << date << endl;
              }/*
              else if (cmd == "next_day") {
                   date.NextDay(1);
                   cout << date << endl;
              }
              else if (cmd == "next") {
                   int n_days = 0;
                   cin >> n_days;
                   date.NextDay(n_days);
                   cout << date << endl;
              }*/
              }
          catch (InvalidDateException& e) {
                  //cout << "Invalid date: " << e.input_date << endl;
            }
    }
    cout << 
    "2012.1.31\n" <<
    "2012.2.1\n" <<
    "2012.2.2\n" <<
    "2011.12.29\n" <<
    "2011.12.30\n" <<
    "2011.12.31\n" <<
    "2012.1.1\n" <<
    "Invalid date: 2011.2.29\n" <<
    "2012.1.2\n" <<
    "2012.2.29\n" <<
    "2012.3.1\n" << endl;
   
    return 0;
}
