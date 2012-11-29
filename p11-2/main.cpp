#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

using namespace std;

ostream& operator<<(ostream& os, const Date& c){         // �޷³�¥�� ����ϴ� �κ�!! 
    cout<<c.year()<<"."<<c.month()<<"."<<c.day();
    return os;
}

istream& operator>>(istream& is, Date& c){               // 11-1���� ���������� string�� �ѹ��� �޾Ƽ� ��,��,���� ������. 
    string dates, last1, last2;                          
    string year, month, day;
    bool okay;
    int Y,M,D;
    size_t check1, check2;
    cin>>dates;
    check1 = dates.find(".");                            // "."�� �������� ��,��,���� ������ 
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
