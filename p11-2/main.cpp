#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

using namespace std;

ostream& operator<<(ostream& os, const Date& c){         // 달력날짜를 출력하는 부분!! 
    cout<<c.year()<<"."<<c.month()<<"."<<c.day();
    return os;
}

istream& operator>>(istream& is, Date& c){               // 11-1번과 마찬가지로 string을 한번에 받아서 해,달,월로 나눈다. 
    string dates, last1, last2;                          
    string year, month, day;
    bool okay;
    int Y,M,D;
    size_t check1, check2;
    cin>>dates;
    check1 = dates.find(".");                            // "."을 기준으로 해,달,월을 나눈다 
    year = dates.substr(0, check1);
    last1 = dates.substr(check1+1, dates.size());
    check2 = last1.find(".");
    month = last1.substr(0, check2);
    day = last1.substr(check2+1, last1.size());
    
    Y = atoi(year.c_str());
    M = atoi(month.c_str());
    D = atoi(day.c_str());
    Date DATE(Y,M,D);
    okay = DATE.SetDate(Y,M,D);
    if(okay == true)
        c = DATE;
    else{
        InvalidDateException IVDE(dates);
        throw IVDE;
    }    
    return is;
}

int main(void) {                                 
    Date date;
    string cmd;
    while (cmd != "quit") {
        cin >> cmd;
        try {
            if (cmd == "set") {             //set을 입력하면 date를 입력받는다 
                cin >> date;
                cout << date << endl;
            } 
            else if (cmd == "next_day") {  //next_day를 입력하면 하루다음날로 셋팅한 후 출력한다. 
                date.NextDay();
                cout << date << endl;
            } 
            else if (cmd == "next") {      //next를 입력하면 n을 입력해 n일뒤로 셋팅 한 후 출력한다. 
                int n_days = 0;
                cin >> n_days;
                date.NextDay(n_days);
                cout << date << endl;
            }
        } 
        catch (InvalidDateException& e) {   // invalid한 값이 입력될경우 error메세지 출력! 
            cout << "Invalid date: " << e.input_date << endl;
        }
    }
    return 0;
}
