#include <iostream>
#include <string>

using namespace std;

class Date {
    public:
        Date() {        // 윤년의 달은 YM배열에 각 개월의 날짜수를 저장시켜놓고
                        // 윤년이 아닌 해의 달은 M배열에 각 개월의 날짜수를 저장 
            YM[1]=YM[3]=YM[5]=YM[7]=YM[8]=YM[10]=YM[12]=31;
            YM[4]=YM[6]=YM[9]=YM[11]=30;
            YM[2]=29;
            M[1]=M[3]=M[5]=M[7]=M[8]=M[10]=M[12]=31;
            M[4]=M[6]=M[9]=M[11]=30;
            M[2]=28;       
        }
        Date(int year, int month, int day){   // constructor가 실행시 parametor로 받은 년,월,일을 변수에 저장 
            year_ = year;
            month_ = month;
            day_ = day;
            YM[1]=YM[3]=YM[5]=YM[7]=YM[8]=YM[10]=YM[12]=31;
            YM[4]=YM[6]=YM[9]=YM[11]=30;
            YM[2]=29;
            M[1]=M[3]=M[5]=M[7]=M[8]=M[10]=M[12]=31;
            M[4]=M[6]=M[9]=M[11]=30;
            M[2]=28;  
        }
        void NextDay(int n = 1){             // defalut값으로 1을 설정했기 때문에 parametor들어오지 않을경우 n=1로 취급되어 실행  
            if(n ==1){
                if(GetDaysInYear(year_) == 366){
                    day_++;
                    if(day_ > YM[month_]){              //여기서 윤년인지 아닌지 두분류로 분류해서 계산하는것이 point!!! 
                        day_ -= YM[month_];             // 윤년일시 day_++한후 그 달의 날짜수를 day_가 넘으면 그 달의 날짜수만큼빼고 month_++한다.   
                        month_++;
                    }
                    if(month_ > 12){                            //month_가 12를 넘으면 month_-12한후 year_ ++ 
                        month_ -=12;
                        year_ ++;
                    }
                }
                else {                                          //윤년이 아닌경우 M으로 계산하는것말고는 위와동일!  
                    day_++;
                    if(day_ > M[month_]){
                        day_ -= M[month_];
                        month_++;
                    }
                    if(month_ > 12){
                        month_ -=12;
                        year_ ++;
                    }
                }       
            }
            else {                                    // n=1이 아니고 다른값이 들어올경우 계산하는 방법 !! 
                int days=0;
                days = ComputeDaysFromYearStart(year_,month_,day_) + n;    // days라는 변수에 지금 설정된 년,월,일 까지의 날수와 n을더해 저장 
                // 한해 늘어나는 범위 
                if( days > GetDaysInYear(year_)){                    // 1. days가 year의 날수보다 클경우 
                    while( days > GetDaysInYear(year_)){
                        days -= GetDaysInYear(year_);                // <point> while문이 중요한데 while문으로 매해의 날수를 뺀다. 
                        year_++;                                     // 빼줄때 막연히 365를 빼는것이아닌 year를 증가시킨 해의 날수를 계산해 빼준다. 
                    }                                                // 빼주고나면 남은 days가 나올것이므로 그것으로 그해의 날짜를 계산!!! 
                    if(GetDaysInYear(year_) == 366){                 
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){                    // 1월로 기준을 정하고 윤년일시 YM을 이용해 매월 날수를 빼가며 month 더한다 
                                days -= YM[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;                         // 더하기 할때는 1월1일에서 더하는것이므로 1일을 더해준다!! 
                                break;
                            }
                        }     
                    }
                    else {                                           //윤년이 아닐시에는 M을 이용하는 것이외 위와동일! 
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    }
                }
                // 한해 줄어드는 범위 
                else if( days <= 0){
                    while( days <= 0){                     //한해줄어드는 범위도 포인트는 while문을 써서 각 줄어든 해의 날수를 빼주는것이포인트!! 
                        year_--;
                        days += GetDaysInYear(year_);
                    }
                    if(GetDaysInYear(year_) == 366){
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){           // 마찬가지로 한해증가하는 범위와 같이 남은 days가 나오면  
                                days -= YM[MONTH];          // 거기서부터 윤년,윤년이 아닌해 파악해 매달 YM,M을이용해 빼줘서 구한다. 
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }     
                    }
                    else {
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    } 
                }
                // 일년 안의범위  
                else {
                    if(GetDaysInYear(year_) == 366){                //일년 이내의 범위일시에는 while사용해 그해의 날수를 빼줄필요 없으므로 바로실행 
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){
                                days -= YM[MONTH];
                                MONTH++;                           //윤년인지 아닌지만 판단해 위와같은 방식으로 날짜계산해준다! 
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }     
                    }
                    else {
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    }   
                }
            }
        }
        bool SetDate(int year, int month, int day);              //올바른 날짜가 들어올경우 true return 아닐경우 false return 
        int year() const { return year_; }                       // year return
        int month() const { return month_; }                     // month return
        int day() const { return day_; }                         // day return
    private:
// 윤년을 판단하여 주어진 연도에 해당하는 날짜 수(365 또는 366)를 리턴.
        static int GetDaysInYear(int year);
// 해당 날짜가 해당 연도의 처음(1월 1일)부터 며칠째인지를 계산.
        static int ComputeDaysFromYearStart(int year, int month, int day);
        int year_, month_, day_;
        int M[12], YM[12];                                        // 매월 날짜수를 넣는 array  
};

struct InvalidDateException {
    string input_date;
    InvalidDateException(const string& str) : input_date(str) {}
};
