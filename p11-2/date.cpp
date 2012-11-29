#include "date.h"
#include <iostream>

using namespace std;

int Date :: GetDaysInYear(int year){           // 윤년인지 아닌지를 검사하는 함수 
    if((year%4)==0 && (year%100)!=0)           // 4로 나눠지는데 100으로는 안나눠지는경우 == 윤년조건 
        return 366;
    else if((year%400)==0)                     // 400으로 나누어질때 == 윤년조건 
        return 366;
    else                                       // 어느조건도 만족하지 않을 경우 365일 
        return 365;
}

int Date :: ComputeDaysFromYearStart(int year, int month, int day){     // 셋팅된 해의 1월1일 부터 셋팅된날까지의 날수계산!! 
    int DATE=0;
    if(GetDaysInYear(year) == 366){                    // 윤년일경우 2월은 29일로 계산하기때문에 짝수달 for문돌릴시를 대비해 미리-1해준다 
        if(month > 8)                                  // 8은 예외로 짝수달이지만 31일이므로 +1해준다 
            DATE+=1;
        if(month > 2)
            DATE-=1;
        for(int i=0;i<month/2;i++)                     //홀수달 +31 
            DATE += 31;
        if(month%2 ==0){                               //짝수달 +30 인데 이때 8월이면 짝수달이 4번이아닌 3번이므로 -1해주고 3번돌린다 
            for(int i=0;i<(month/2)-1;i++)             
                DATE += 30;
        }
        else {
            for(int i=0;i<(month/2);i++)               //짝수달 +30 2,4,6,8,10월 등이아닌 달이셋팅된 달이면 그냥 계산 
                DATE += 30;
        }
        DATE += day-1;
        return DATE;
    }
    else {                                             // 윤년이 아닌경우 2월은 28일 이므로 -2해주고 시작한다. 나머지위와동일! 
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

bool Date :: SetDate(int year, int month, int day){       // 입력된 해,달,월이 타당한 값이면 true return 아니면 false return 
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
