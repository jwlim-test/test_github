#include "date.h"
#include <iostream>

using namespace std;

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
    if(GetDaysInYear(year) == 366){                    // �����ϰ�� 2���� 29�Ϸ� ����ϱ⶧���� ¦���� for�������ø� ����� �̸�-1���ش� 
        if(month > 8)                                  // 8�� ���ܷ� ¦���������� 31���̹Ƿ� +1���ش� 
            DATE+=1;
        if(month > 2)
            DATE-=1;
        for(int i=0;i<month/2;i++)                     //Ȧ���� +31 
            DATE += 31;
        if(month%2 ==0){                               //¦���� +30 �ε� �̶� 8���̸� ¦������ 4���̾ƴ� 3���̹Ƿ� -1���ְ� 3�������� 
            for(int i=0;i<(month/2)-1;i++)             
                DATE += 30;
        }
        else {
            for(int i=0;i<(month/2);i++)               //¦���� +30 2,4,6,8,10�� ���̾ƴ� ���̼��õ� ���̸� �׳� ��� 
                DATE += 30;
        }
        DATE += day-1;
        return DATE;
    }
    else {                                             // ������ �ƴѰ�� 2���� 28�� �̹Ƿ� -2���ְ� �����Ѵ�. ���������͵���! 
        if(month > 8)
            DATE+=1;
        if(month > 2)
            DATE-=2;
        for(int i=0;i<month/2;i++)
            DATE += 31;
        if(month%2 ==0){
            for(int i=0;i<(month/2)-1;i++)
                DATE += 30;
        }
        else {
            for(int i=0;i<(month/2);i++)
                DATE += 30;
        }
        DATE +=day-1;
        return DATE;
    }
}

bool Date :: SetDate(int year, int month, int day){       // �Էµ� ��,��,���� Ÿ���� ���̸� true return �ƴϸ� false return 
    if(GetDaysInYear(year) == 366){
        if(YM[month] < day)
            return false;
        if(day < 0 || month < 1 || month >12)
            return false;
        else 
           return true;
    }
    else {
        if(M[month] < day)
            return false;
        if(day < 0 || month < 1 || month >12)
            return false;
        else 
           return true;
    }
}
