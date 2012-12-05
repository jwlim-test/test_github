#include "date.h"
#include <iostream>

using namespace std;

int Date::YM[12];            //static ���μ����ؼ� class������ ���������� ��� 
int Date::M[12];             //static function���� ����ϱ����� 

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

int Date :: GetDaysInYear(int year){           // �������� �ƴ����� �˻��ϴ� �Լ� 
    if((year%4)==0 && (year%100)!=0)           // 4�� �������µ� 100���δ� �ȳ������°�� == �������� 
        return 366;
    else if((year%400)==0)                     // 400���� ���������� == �������� 
        return 366;
    else                                       // ������ǵ� �������� ���� ��� 365�� 
        return 365;
}

int Date :: ComputeDaysFromYearStart(int year, int month, int day){     // ���õ� ���� 1��1�� ���� ���õȳ������� �������!! 
    int DATE=0;
    if(GetDaysInYear(year) == 366){                    // �����ϰ�� YM���� �Ŵ� ���������� �����ش� 
        for(int i=1;i<month;i++)
            DATE+=YM[i];
    }
    else {                                             // ������ �ƴѰ�� M���� �Ŵ� ���������� �����ش� 
        for(int i=1;i<month;i++)
            DATE+=M[i];
    }
     DATE += day-1;
     return DATE;
}

bool Date :: SetDate(int year, int month, int day){       // �Էµ� ��,��,���� Ÿ���� ���̸� true return �ƴϸ� false return 
    if(GetDaysInYear(year) == 366){
        if(YM[month] < day)
            return false;
    }
    else {
        if(M[month] < day)
            return false;
    }
    if(day < 0 || month < 1 || month >12)             // ����κ��� �ѹ��� ���ش�. 
        return false;
    else 
        return true;
}
