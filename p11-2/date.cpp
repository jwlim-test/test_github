#include "date.h"
#include <iostream>

using namespace std;

int Date::YM[12];            //static 으로선언해서 class내에서 전역변수로 사용 
int Date::M[12];             //static function에서 사용하기위함 

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
    if(GetDaysInYear(year) == 366){                    // 윤년일경우 YM으로 매달 몇일인지를 더해준다 
        for(int i=1;i<month;i++)
            DATE+=YM[i];
    }
    else {                                             // 윤년이 아닌경우 M으로 매달 몇일인지를 더해준다 
        for(int i=1;i<month;i++)
            DATE+=M[i];
    }
     DATE += day-1;
     return DATE;
}

bool Date :: SetDate(int year, int month, int day){       // 입력된 해,달,월이 타당한 값이면 true return 아니면 false return 
    if(GetDaysInYear(year) == 366){
        if(YM[month] < day)
            return false;
    }
    else {
        if(M[month] < day)
            return false;
    }
    if(day < 0 || month < 1 || month >12)             // 공통부분은 한번만 써준다. 
        return false;
    else 
        return true;
}
