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
            if (cmd == "set") {             //set�� �Է��ϸ� date�� �Է¹޴´� 
                cin >> date;
                cout << date << endl;
            } 
            else if (cmd == "next_day") {  //next_day�� �Է��ϸ� �Ϸ�������� ������ �� ����Ѵ�. 
                date.NextDay();
                cout << date << endl;
            } 
            else if (cmd == "next") {      //next�� �Է��ϸ� n�� �Է��� n�ϵڷ� ���� �� �� ����Ѵ�. 
                int n_days = 0;
                cin >> n_days;
                date.NextDay(n_days);
                cout << date << endl;
            }
        } 
        catch (InvalidDateException& e) {   // invalid�� ���� �Էµɰ�� error�޼��� ���! 
            cout << "Invalid date: " << e.input_date << endl;
        }
    }
    return 0;
}
