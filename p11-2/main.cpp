#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

using namespace std;

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
